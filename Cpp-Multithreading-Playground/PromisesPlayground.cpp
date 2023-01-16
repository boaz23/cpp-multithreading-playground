#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <chrono>
#include <optional>

namespace promises_playground
{
void run()
{
    std::promise<std::string> promise{};
    std::shared_future<std::string> future = promise.get_future().share();

    std::thread t1{ [&future]
    {
        std::cout << "t1 done: " + future.get() + "\n";
    } };
    std::thread t2{ [&future]
    {
        std::optional<int> n;
        try
        {
            size_t idx{0};
            std::string value = future.get();
            n = std::stoi(value, &idx);
            if (idx != value.length())
            {
                n = std::nullopt;
            }
        }
        catch (std::invalid_argument &e)
        {
            n = std::nullopt;
        }

        if (n.has_value())
        {
            std::cout << "t2 done: " + std::to_string(n.value() + 1) + "\n";
        }
        else
        {
            std::cout << "t2 done: NaN\n";
        }
    } };
    std::thread t3{ [&future]
    {
        std::string s = future.get().empty() ? "empty" : "not empty";
        std::cout << "t3 done: " + s + "\n";
    } };

    std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
    promise.set_value("fff");
    t1.join();
    t2.join();
    t3.join();
    std::cout << "Done!";
}
}