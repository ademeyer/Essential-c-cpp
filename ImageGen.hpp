#pragma once

#include "ImageGen.hpp"
#include <chrono>
#include <thread>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

namespace pmImage
{
  std::vector<float> generateImage(int frameNum)
  {
    std::vector<float> image(512 * 512, float(frameNum) / 100.f);
    return image;
  }

  int frameid;

  void registerImageCallback(std::function<void(std::vector<float> &image, int frameNumber)> callback)
  {
    auto thread = std::jthread([callback]()
                               {
                                      std::this_thread::sleep_for(std::chrono::seconds(5));
                                        auto end = std::chrono::system_clock::now() + std::chrono::milliseconds(0);
                                        for(int i=0; i<100; ++i)
                                        {
                                            std::this_thread::sleep_until(end);
                                            end = std::chrono::system_clock::now() + std::chrono::milliseconds(1000/32);
                                            auto img = generateImage(i);
                                            callback(img,i);
                                        } });
    frameid = 0;
    thread.detach();
  }

  std::vector<float> processImage(std::vector<float> image)
  {
    if (image.size() < 10)
    {
      return image;
    }
    auto time = int(std::reduce(image.begin(), image.begin() + 10));
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    return image;
  }

  void displayImage(const std::vector<float> &image, const int frameNumber)
  {
    if (frameNumber < frameid)
    {
      std::cout << "Diplaying old frame." << std::endl;
    }
    else
    {
      frameid = frameNumber;
    }
  }

} // pmImage
