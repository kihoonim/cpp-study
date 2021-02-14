#include <iostream>
#include <thread>
#include <future>

void f1(int n) {
    std::cout << "thread " << n << std::endl;
}

void thread_example() {
    std::thread t1;
    t1 = std::thread(f1, 1);
    t1.join();
    std::thread t2(f1, 2);
    std::thread t3(std::move(t2));
    std::thread t4([]() { return; });
    t4.detach();
    t3.join();
}

void promise_future_example() {
    auto meaning = [](std::promise<int>& prom) {
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
        std::cout << "thread start" << std::endl;
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
        prom.set_value(42);
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
        std::cout << "thread end" << std::endl;
    };

    std::promise<int> prom;
    std::thread(meaning, std::ref(prom)).detach();

    std::future<int> result = prom.get_future();
    std::cout << "get_future" << std::endl;
    std::cout << "result : " << result.get() << std::endl;
    std::this_thread::sleep_for(std::chrono::duration<int>(5));
}

void promise_future_example_2() {
    auto meaning = std::packaged_task<int(int)>(
        [](int n) { return n; }
    );
    auto result = meaning.get_future();
    auto t = std::thread(std::move(meaning), 42);
    std:: cout << "result : " << result.get() << std::endl;
    t.join();
}

void promise_future_example_3() {
    auto meaning = [](int n) { return n; };
    auto result = std::async(std::move(meaning), 42);
    std::cout <<
}

int main() {
    //thread_example();
    //promise_future_example();
    promise_future_example_2();
}