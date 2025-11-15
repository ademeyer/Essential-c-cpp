// #include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <memory>
#include <queue>
#include <chrono>

// Include the provided ImageGen header
#include "ImageGen.hpp"

/*
In the concept of produce and consumer running concurrently
a cirular buffer help to avoid lost frames
*/
template <typename T>
class CircularBuffer
{
private:
  // Using a priority queue to help organize frame with frame number ordering
  std::priority_queue<T, std::vector<T>, std::greater<T>> buffer;
  size_t capacity;
  mutable std::mutex mutex;
  std::condition_variable not_empty;
  std::condition_variable not_full;
  std::atomic<bool> stop_flag{false};

public:
  explicit CircularBuffer(size_t size) : capacity(size) {}

  bool push(T &&item)
  {
    std::unique_lock<std::mutex> lock(mutex);
    if (stop_flag)
      return false;

    not_full.wait(lock, [this]()
                  { return buffer.size() < capacity || stop_flag; });
    if (stop_flag)
      return false;

    buffer.push(std::move(item));

    lock.unlock();
    not_empty.notify_one();
    return true;
  }

  bool pop(T &item)
  {
    std::unique_lock<std::mutex> lock(mutex);
    if (stop_flag && buffer.empty())
      return false;

    not_empty.wait(lock, [this]()
                   { return !buffer.empty() || stop_flag; });
    if (stop_flag && buffer.empty())
      return false;

    item = std::move(const_cast<T &>(buffer.top()));
    buffer.pop();

    lock.unlock();
    not_full.notify_one();
    return true;
  }

  size_t size() const
  {
    std::lock_guard<std::mutex> lock(mutex);
    return buffer.size();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(mutex);
    return buffer.empty();
  }

  void stop()
  {
    stop_flag = true;
    not_empty.notify_all();
    not_full.notify_all();
  }
};

// our image would be structured as a task moving forward
using ImageTask = std::pair<int, std::vector<float>>;

/*
ImageWorker class is used to call image callbacks and processor
*/
class ImageWorker
{
private:
  CircularBuffer<ImageTask> &input_buffer;
  CircularBuffer<ImageTask> &output_buffer;
  std::thread worker_thread;
  std::atomic<bool> stop_flag{false};

public:
  ImageWorker(CircularBuffer<ImageTask> &input, CircularBuffer<ImageTask> &output)
      : input_buffer(input), output_buffer(output)
  {
    worker_thread = std::thread(&ImageWorker::process_loop, this);
  }

  ~ImageWorker()
  {
    stop();
    if (worker_thread.joinable())
    {
      worker_thread.join();
    }
  }

  void stop()
  {
    stop_flag = true;
    input_buffer.stop();
  }

private:
  void process_loop()
  {
    while (!stop_flag)
    {
      ImageTask task;

      if (input_buffer.pop(task))
      {
        if (task.first >= 0)
        {
          // Process the image
          auto processed_image = pmImage::processImage(std::move(task.second));

          // Push to output buffer
          ImageTask processed_task{task.first, std::move(processed_image)};

          // Keep trying to push until successful or stopped
          while (!stop_flag && !output_buffer.push(std::move(processed_task)))
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
          }
        }
      }
      else if (stop_flag)
      {
        break;
      }
    }
  }
};

class ImageProcessor
{
private:
  // Buffers
  CircularBuffer<ImageTask> input_buffer;
  CircularBuffer<ImageTask> output_buffer;

  // Workers
  std::vector<std::unique_ptr<ImageWorker>> workers;

  // Thread control
  std::atomic<bool> stop_flag{false};
  std::thread display_thread;
  std::thread killer_thread;

public:
  ImageProcessor(size_t buffer_size = 32)
      // using a limited buffer, this can be ajusted to improve flow but at the expense of memory usage
      : input_buffer(buffer_size), output_buffer(buffer_size)
  {

    // Create just image worker threads
    const int num_workers = 2;
    for (int i = 0; i < num_workers; ++i)
    {
      workers.push_back(std::make_unique<ImageWorker>(input_buffer, output_buffer));
    }

    // Register image callback
    pmImage::registerImageCallback(
        [this](std::vector<float> &image, int frameNumber)
        {
          this->on_image_received(image, frameNumber);
        });
  }

  ~ImageProcessor()
  {
    stop_flag = true;

    // Stop workers first
    for (auto &worker : workers)
    {
      worker->stop();
    }

    // Stop buffers
    input_buffer.stop();
    output_buffer.stop();

    // Join threads
    if (display_thread.joinable())
    {
      display_thread.join();
    }
  }

private:
  void on_image_received(std::vector<float> &image, int frame_number)
  {
    // Create a copy since we can't move from the reference
    std::vector<float> image_copy = image;
    auto data = std::pair<int, std::vector<float>>({frame_number, image_copy});
    if (!input_buffer.push(std::move(data)))
    {
      /* I am monitoring the ciruclare buffer is there is need to increase it*/
      std::cerr << "Warning: Dropped frame " << frame_number << " - input buffer full" << std::endl;
    }
  }

  void display_loop()
  {
    while (!stop_flag)
    {
      ImageTask task;
      if (output_buffer.pop(task))
      {
        std::cout << "Displaying frame: " << task.first << std::endl;
        pmImage::displayImage(task.second, task.first);
      }
    }
    std::cout << "End Displaying\n";
  }

  //! Even I am not fully convinced a killer thread is the best strategy,
  //! I am running out of time and ideas, this is a quick fix
  void killer_loop()
  {
    auto last_activity = std::chrono::steady_clock::now();

    while (!stop_flag)
    {
      // Check if output buffer has any activity
      size_t current_size = output_buffer.size();

      // If buffer is not empty, reset the timer
      if (current_size > 0)
      {
        last_activity = std::chrono::steady_clock::now();
      }

      // Check if 1 second has passed with no activity
      auto now = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_activity);

      if (elapsed.count() > 1000)
      {
        std::cout << "Killer: No activity for 1 second - terminating display thread\n";
        stop_flag = true;
        input_buffer.stop();
        output_buffer.stop();
        break;
      }

      // Sleep for a short time before checking again
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Killer thread exiting\n";
  }

public:
  void run()
  {
    std::cout << "Image Processor started with 2 worker threads" << std::endl;

    display_thread = std::thread(&ImageProcessor::display_loop, this);
    /*
    Like I have said earlier, this is a bit quacky, we need to wait for Imageprocessor to
    start working before the killer guy shows up.
    */
    std::this_thread::sleep_for(std::chrono::seconds(8));
    killer_thread = std::thread(&ImageProcessor::killer_loop, this);
    // Wait for display thread to complete
    if (display_thread.joinable())
    {
      display_thread.join();
    }
    if (killer_thread.joinable())
    {
      killer_thread.join();
    }
  }
};

int main()
{
  try
  {
    ImageProcessor processor;
    processor.run();
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  std::cout << "Processing complete." << std::endl;
  return 0;
}