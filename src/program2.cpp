#include <c++/9/iostream>
#include <c++/9/chrono>
#include <c++/9/thread>
#include <c++/9/mutex>
#include <string.h>
#include <c++/9/atomic>
#include <boost/log/trivial.hpp>

std::mutex mywrite;
std::atomic<bool> flag(false);
std::atomic<bool> kill(false);
std::atomic<bool> cleanup(false);


void run(const char* name){

    mywrite.lock();
    BOOST_LOG_TRIVIAL(info) << "staring thread";
    std::cout << "starting thread " << name << std::endl;
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl << std::endl;
    mywrite.unlock();

    if( strcmp(name, "booger") == 0 ){
        std::this_thread::sleep_for(std::chrono::seconds(5));
    } else {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        flag = true;
    }

    mywrite.lock();
    std::cout << "Thread " << name << " ending" << std::endl << std::endl;
    mywrite.unlock();
}

void eternity(){

    mywrite.lock();
    std::cout << "starting thread eternity" << std::endl;
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl << std::endl;
    mywrite.unlock();

    for(int i = 0; i < 30; i++){
        if( kill ){
            mywrite.lock();
            std::cout << "eternity received the kill flag" << std::endl;
            mywrite.unlock();
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    mywrite.lock();
    std::cout << "eternity thread ending" << std::endl;
    std::cout << std::endl;
    mywrite.unlock();
    cleanup = true;
}

int main(){

    std::thread t1(run, "booger");
    std::thread t2(run, "snot");
    std::thread t3(eternity);

    t1.detach();
    t2.detach();
    t3.detach();

    while( !cleanup ){
        if( flag ){
            flag = false;
            mywrite.lock();
            std::cout << "flag caught" << std::endl;
            std::cout << "sending kill" << std::endl << std::endl;
            mywrite.unlock();
            kill = true;
        }
    }
    
    std::cout << "main thread ending" << std::endl;


    return 0;
}
