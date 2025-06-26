#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;
mutex mtx;
void square(int n, int *total)
{
    int temp = n * n;
    mtx.lock();
    *total += temp;
    mtx.unlock();
}

int main()
{
    int *total = new int(0);
    // try_lock, try_lock_for, try_lock_until
    vector<thread> threads;
    for (int i = 1; i <= 10; i++)
    {
        threads.emplace_back(thread(square, i, total));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    cout << "Total: " << *total << endl;
    delete total;
    return 0;
}