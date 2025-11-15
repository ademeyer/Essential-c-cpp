#include <bits/stdc++.h>
#include <atomic>

// std::atomic<bool> kill;
void reorder(std::binary_semaphore &start, 
              std::counting_semaphore<2>&end,
              int& write, int& read, int& reg)
{
  // Keep going forever
  while(true)
  {
    // Wait for signal to start
    start.acquire();

    // Write to v2
    write = 1;

    // Read v1
    reg = read;

    // Say we're done for this iteration
    end.release();
  }
}

int main (int argc, char *argv[]) 
{
  // Create semaphores for signaling threads
  std::binary_semaphore start_t0(0);
  std::binary_semaphore start_t1(0);
  std::counting_semaphore<2> done(0);

  // Variable for memory re-ordering
  int x = 0, y = 0, r1 = 0, r2 = 0;
  
  // Start threads
  std::thread t1( [&]{ reorder(start_t0, done, x, y, r1); });
  std::thread t2( [&]{ reorder(start_t1, done, y, x, r2); } );

  for(int i = 0;; ++i)
  {
    // Zero x/y each iteration
    x = 0, y = 0;
    
    // Allow threads to counting_semaphore
    start_t0.release();
    start_t1.release();

    // Wait for both threads to finish
    done.acquire();
    done.acquire();

    // Check memory re-ordering
    auto reordering = (r1 == 0 && r2 == 0);
    if(reordering)
    {
      std::cout << "Error! r1 = " << r1 << ", r2 = " 
                << r2 << ", iteration: " << i << std::endl;
      assert(false);
    }
    else 
    {
      std::cout << "All is Good! r1 = " << r1 << ", r2 = " <<
                  r2 << ", iteration: " << i << std::endl;
    }
  }

  return 0;
}
