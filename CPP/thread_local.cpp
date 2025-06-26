// thread_local is a storage class specifier. Thread local data will be created for each thread as needed
// thread local data exclusively belongs to the thread and behaves like static data
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
thread_local int i = 0;

#include <sstream>

void f(int newval)
{
    i = newval;
}

void g()
{
    ostringstream oss;
    oss << "Thread ID: " << this_thread::get_id() << ", i: " << i << endl;
    cout << oss.str();
}

void threadfunc(int id)
{
    f(id);
    this_thread::sleep_for(chrono::milliseconds(1000));
    g();
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back(thread(threadfunc, i));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    cout << "Main thread ID: " << this_thread::get_id() << ", i: " << i << endl;

    return 0;
}