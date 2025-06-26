// Mutex needs to be unlocked explicitly so instead of using mutex.lock and mutex.unlock we use unique_lock
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>

using namespace std;

mutex mtx;

void square(int n, int &total)
{
    int temp = n * n;
    unique_lock<mutex> lock(mtx);
    total += temp;
}

// To aquire multiple locks while avoiding deadlocks, you can use std::lock
// void f()
// {                                                           // ...
//     std::unique_lock<std::mutex> lck1(m1, std::defer_lock); // make locks but
//     std::unique_lock<std::mutex> lck2(m2, std::defer_lock); // do not yet try to
//     std::unique_lock<std::mutex> lck3(m3, std::defer_lock); // acquire the mutexes
//     std::lock(lck1, lck2, lck3);
//     // manipulate shared data:
// }

int main()
{
    int total = 0;
    vector<thread> threads;
    for (int i = 1; i <= 10; ++i)
    {
        threads.emplace_back(thread(square, i, ref(total)));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    cout << "Sum of squares from 1 to 10: " << total << endl;
    return 0;
}