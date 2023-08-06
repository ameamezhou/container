#include <iostream>
#include <thread>
#include <vector>

void run()
{
    while (true) {

    }
}

int main()
{
    std::vector<std::thread> treads;
    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        threads.emplace_back(run);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}