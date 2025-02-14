#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;

mutex mtx;

void increment(int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        mtx.lock();     // Khóa mutex trước khi truy cập biến chia sẻ
        cout << ++counter << endl;      // Thao tác trên biến chia sẻ
        mtx.unlock();   // Mở khóa mutex sau khi truy cập
    }
}


int main() {
    const int num_iterations = 100000;


    thread t1(increment, num_iterations);
    thread t2(increment, num_iterations);


    t1.join();
    t2.join();


    cout << "Final counter value: " << counter << endl;


    return 0;
}
