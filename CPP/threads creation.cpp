#include <iostream>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

using namespace std;

int thread1()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "Count: " << i << " from thread:" << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    return 0;
}

void thread2(int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        cout << "Count: " << i << " from thread 2" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main()
{
    cout << "Hello, World!" << endl;
    thread t1(thread1);
    thread t2(thread2, 5, 1);
    auto func = bind(thread2, placeholders::_1, 5);
    thread t3(func, 1);
    thread t4{thread1};

    // t1.detach(); // Detach t1 to run independently
    // t1.swap(t4); // Swap t1 with t4
    t4.join();
    t2.join();
    t3.join();
    t1.join();
    return 0;
}