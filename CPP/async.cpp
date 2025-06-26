#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <future>

using namespace std;

int square(int x)
{
    return x * x;
}

int main()
{
    int total = 0;
    vector<future<int>> futures;
    for (int i = 1; i <= 10; ++i)
    {
        futures.push_back(async(square, i));
    }
    for (auto &fut : futures)
    {
        total += fut.get();
    }

    cout << "Total sum of squares from 1 to 10 is: " << total << endl;
    return 0;
}