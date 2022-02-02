#include <chrono>
#include <iostream>
#include <thread>


using namespace::std::literals;

auto func = [](std::stop_token stoken) {                             // (1)
        int counter{0};
        auto thread_id = std::this_thread::get_id();
        std::stop_callback callBack(stoken, [] {  // (2)
            std::cout << "Thread stop. \n " ;
        });
        while (!stoken.stop_requested()) {
            std::this_thread::sleep_for(0.2s);
            ++counter;
        }
    };

int main() {
    
    std::cout << '\n';
    
    auto thr = std::jthread(func);
    std::this_thread::sleep_for(2s);                 
    thr.request_stop(); 

    std::cout << '\n';
    
}
