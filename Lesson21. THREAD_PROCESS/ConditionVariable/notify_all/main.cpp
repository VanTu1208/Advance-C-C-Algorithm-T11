#include <iostream>
#include <thread>               // tạo ra các luồng
#include <mutex>                // khóa dữ liệu khi có nhiều luồng cùng truy cập
#include <condition_variable>   // sử dụng biến điều kiện giúp đồng bộ hóa giữa các luồng
#include <chrono>               // quản lý thời gian

using namespace std;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}

int sensor_data = 0;

bool check_data = false;

mutex mtx;

condition_variable cv;

void sensor_read(){
    while (1){
        delay(2);
        sensor_data = rand() % 100;
        check_data = true;
        unique_lock<mutex> lock(mtx);    // có thể ko cần
        cout << "Read data done!\n";
        lock.unlock();
        cv.notify_all();
    }
}
void process_data_1(){
    while (1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []()->bool{return check_data;}); // trả về true -> break
        cout << "Process Data 1: " << sensor_data << endl;
        lock.unlock();
        check_data = false;  
    }
}

void process_data_2(){
    while (1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []()->bool{return check_data;}); // trả về true -> break
        cout << "Process Data 2: " << sensor_data << endl;
        lock.unlock();  // giảm độ nghẽn
        check_data = false;       
    }
}

int main(int argc, char const *argv[])
{
    thread task1(sensor_read);
    thread task2(process_data_1);
    thread task3(process_data_2);


    task1.join();
    task2.join();
    task3.join();


    return 0;
}
