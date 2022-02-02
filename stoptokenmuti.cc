#include <atomic>
#include <thread>
#include <iostream>

#include <future>
#include <chrono>
#include <thread>


using namespace std::chrono_literals;

std::atomic<int> fin = {0};



using namespace::std::literals;

auto func = [](std::stop_token stoken) {                             // (1)
        int counter{0};
        auto thread_id = std::this_thread::get_id();
        std::stop_callback callBack(stoken, [] {  // (2)
            std::cout << "Thread1 stop. \n " ;
        });
        while (!stoken.stop_requested()) {
            std::this_thread::sleep_for(1s);
            ++counter;
            std::cout<<"func1 alive.\n";

        }
    };


auto func2 = [](std::stop_token stoken) {                             // (1)
        int counter{0};
        auto thread_id = std::this_thread::get_id();
        std::stop_callback callBack(stoken, [] {  // (2)
            std::cout << "Thread2 stop. \n " ;
        });
        while (!stoken.stop_requested()) {
            std::this_thread::sleep_for(1.2s);
            ++counter;
            std::cout<<"func2 alive.\n";

        }
    };





int main() {
    
    std::cout << '\n';
    
    auto thr = std::jthread(func);
     auto thr2 = std::jthread(func2);
     auto thr3 = std::jthread(
         [](std::stop_token stoken) {                             // (1)
        int counter{0};
        auto thread_id = std::this_thread::get_id();
        std::stop_callback callBack(stoken, [] {  // (2)
            std::cout << "Thread3 stop. \n " ;
        });
        while (!stoken.stop_requested()) {
            std::this_thread::sleep_for(0.2s);
            ++counter;
            std::cout<<"func3 alive.\n";
            for (auto i =0 ;i <10;i++){
            std::this_thread::sleep_for(0.2s);
            
            }
            fin = 1;

        }
    }
    );
 

      

    while(fin != 1){

    std::cout<<"waitting.\n";
        std::this_thread::sleep_for(1s);
    }
    thr.request_stop(); 
    thr2.request_stop(); 
    thr3.request_stop(); 

/*
     
    if (fin == 1){

    thr.request_stop(); 
    thr2.request_stop(); 
    thr3.request_stop(); 
    
    std::cout << '\n';

    }
    */

}

    
    
