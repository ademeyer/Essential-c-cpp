#include <bits/stdc++.h>
#include <atomic>

#define IMAGE_SIZE 512 * 512 * sizeof(float)
using ImageTask = std::pair<int, std::vector<float>>;

class OrderedBuffer
{
  size_t capacity;
  size_t count;
  std::unique_ptr<bool> slot;
  std::unique_ptr<uint8_t> buffer;

  mutable std::mutex mtx;

public:
  explicit OrderedBuffer(const size_t &N)
      : capacity(N), count(0), slot(std::make_unique<bool>(N)),
        buffer(std::make_unique<uint8_t>(N * IMAGE_SIZE))
  {
    for (size_t i = 0; i < capacity; ++i)
      slot.get()[i] = false;
  }

  bool push(const ImageTask &img)
  {
    if (img.first < 0 || (size_t)img.first >= capacity)
      return false;

    const std::lock_guard<std::mutex> lock(mtx);
    new (&(buffer.get()[img.first * IMAGE_SIZE]))
        std::vector<float>(std::move(img.second));
    slot.get()[img.first] = true;

    ++count;

    return true;
  }

  bool pop(ImageTask &img)
  {
    if (img.first < 0 || (size_t)img.first >= capacity)
      return false;

    const std::lock_guard<std::mutex> lock(mtx);
    std::vector<float> *data = std::launder(
        reinterpret_cast<std::vector<float> *>(&(buffer.get()[img.first * IMAGE_SIZE])));

    img.second = *data;

    slot.get()[img.first] = false;
    --count;
    return true;
  }

  bool isFilled(int pos) const
  {
    if (pos < 0 || (size_t)pos >= capacity)
      return true;

    const std::lock_guard<std::mutex> lock(mtx);
    return slot.get()[pos];
  }

  size_t size() const
  {
    const std::lock_guard<std::mutex> lock(mtx);
    return count;
  }
};

int main()
{
  ImageTask img;
  img.first = 0;
  img.second.resize(512 * 512);
  for (size_t i = 0; i < (512 * 512); ++i)
    img.second[i] = static_cast<float>(float(i) / 100.0f);
  OrderedBuffer o_buf(10);
  if (o_buf.push(std::move(img)))
    std::cout << "pushed successfully\n";

  if (o_buf.isFilled(img.first))
    std::cout << "position is filled\n";

  if (!o_buf.isFilled(1))
    std::cout << "position is not filled\n";

  ImageTask img1;
  img1.first = 0;
  if (o_buf.pop(img1))
    std::cout << "pop successfully\n";

  if (img == img1)
    std::cout << "test successfully\n";

  return 0;
}