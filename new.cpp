#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<int> counter = 0;

void work()
{
    for (int i = 0; i < 100000; i++)
    {
        counter++;
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(work);
    std::thread t2(work);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end - start);

    std::cout
        << "Atomic Time:"
        << duration.count()
        << "ms \n";

    return 0;
}
