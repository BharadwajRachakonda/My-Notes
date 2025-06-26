// A condition variable is an object able to block the calling thread until notified to resume
// • It uses a unique lock (over a mutex) to lock the thread when one of its wait functions
// is called
// • The thread remains blocked until woken up by another thread that calls a notification
// function on the same condition variable object
// • Objects of type condition variable always use unique lock<mutex>

#include <iostream>
#include <thread>
#include <condition_variable>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;
mutex mtx;
condition_variable cv;
bool ready = false;
atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id)
{
    unique_lock<mutex> lock(mtx);
    while (!ready)
    {
        cv.wait(lock); // Wait until ready is true
    }
    for (volatile int i = 0; i < 1000000; ++i)
    {
        // Simulate work
    }

    if (!winner.test_and_set()) // Only one thread can print this message
    {
        cout << "Thread " << id << " is the winner!\n";
    }
}

void go()
{
    ready = true;
    cv.notify_all();
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(count1m, i);
    }

    cout << "5 threads ready to count to 1 million.\n";
    go();
    for (auto &th : threads)
    {
        th.join();
    }

    return 0;
}