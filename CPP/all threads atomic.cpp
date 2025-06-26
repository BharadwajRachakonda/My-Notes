#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <sstream>

using namespace std;

atomic<bool> ready(false);
atomic_flag winner = ATOMIC_FLAG_INIT; // to ensure only one thread prints the message

void count1m(int id)
{
    while (!ready)
    {
        this_thread::yield(); // wait until main() signals ready
    }
    for (volatile int i = 0; i < 1000000; ++i)
    {
        // Simulate work
    }
    if (!winner.test_and_set())
    { // if this thread is the first to set the flag
        ostringstream ss;
        ss << "Thread " << id << " finished counting to 1 million.\n";
        cout << ss.str();
    }
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(thread(count1m, i));
    }

    ready = true; // signal all threads to start counting

    for (auto &th : threads)
    {
        th.join(); // wait for all threads to finish
    }

    return 0;
}
