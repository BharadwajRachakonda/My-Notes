#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
atomic<int> square_sum(0);

void square(int n)
{
    square_sum += n * n;
}

int main()
{
    vector<thread> threads;
    for (int i = 1; i <= 10; ++i)
    {
        threads.emplace_back(square, i);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    cout << "Sum of squares from 1 to 10: " << square_sum.load() << endl;
    return 0;
}