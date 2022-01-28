#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

int myInt{};
int myInt1{};


std::atomic_flag atomicFlag{};
std::atomic_flag EndFlag{};

void Sender() {

    std::cout << "Input two numbers."  << std::endl;
    std::cin >> myInt >> myInt1;

    std::cout << "Sender: Data prepared."  << std::endl;
    atomicFlag.test_and_set();                             // (1)
    atomicFlag.notify_all();   

}

void Worker() {
    while(!EndFlag.test()){
    std::cout << "Worker: Waiting for data." << std::endl;
    atomicFlag.wait(false); 
    atomicFlag.clear();                               // (2)

    /*Do something*/

    std::cout << "Waiter: Complete the work." << std::endl;
    std::cout << "Waiter: Numbers are "<< myInt <<","<<myInt1<< std::endl;
    std::cout << std::endl;


    }

}



void End() {

    std::cout << "Sender: EndFlg."  << std::endl;
    EndFlag.test_and_set();                             // (1)
    EndFlag.notify_all();   

}



int main() {

    std::cout << std::endl;


    std::thread t1(Worker);

    for (int i=1;i<10;i++)
    {
        Sender();
    }
    End();
    t1.join();

    std::cout << std::endl;
  
}
