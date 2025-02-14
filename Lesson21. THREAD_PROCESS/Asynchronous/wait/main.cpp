#include <iostream>
#include <thread>
#include <future>
#include <chrono>


using namespace std;


int asyncTask(){
    this_thread::sleep_for(chrono::seconds(5));
    return 100;
}


// Hàm cho luồng 1, in thông báo sau mỗi giây trong 6 giây
void thread1Task() {
    for (int i = 1; i <= 6; ++i) {
        cout << "Thread 1 - second " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}


// Hàm cho luồng 2, in thông báo sau mỗi 2 giây trong 6 giây
void thread2Task() {
    for (int i = 1; i <= 3; ++i) {
        cout << "Thread 2 - second " << (i * 2) << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}


int main(int argc, char const *argv[])
{
    future<int> ft = async(launch::async, asyncTask);


    thread t1(thread1Task);
    thread t2(thread2Task);
     // Luồng chính chờ đợi tác vụ bất đồng bộ hoàn thành
    cout << "Waiting for the task to complete...\n";


    ft.wait();


    cout << "Task completed! Result: " << ft.get() << endl;


    // Chờ hai luồng phụ hoàn thành
    t1.join();
    t2.join();
    cout << "Main thread finished.\n";


    return 0;
}
