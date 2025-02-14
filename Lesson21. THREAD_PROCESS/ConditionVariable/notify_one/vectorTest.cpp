#include <iostream>
#include <thread>               // tạo ra các luồng
#include <mutex>                // khóa dữ liệu khi có nhiều luồng cùng truy cập
#include <condition_variable>   // sử dụng biến điều kiện giúp đồng bộ hóa giữa các luồng
#include <chrono>               // quản lý thời gian
#include <atomic>
#include <vector>


using namespace std;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::milliseconds(time));
}

atomic<int> sensorData(0);
vector<int> buffer(0);

const uint32_t BUFFER_SIZE = 5;

mutex mtx;

condition_variable cv;

void sensor_read(){
    while (1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []()->bool{return buffer.size() < BUFFER_SIZE;});

        buffer.push_back(++sensorData);
        
        cout << "Read Sensor Data Done, Value: " << buffer.back() << endl;
    
        lock.unlock();

        cv.notify_one();
        delay(1000);
    }
}


void process_data_1(){
    while (1){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []()->bool{return !buffer.empty();}); // trả về true -> break
        
        cout << "Process Data: " << buffer.front() << endl;
        buffer.erase(buffer.begin());
        cv.notify_one();
        lock.unlock();
        delay(5000);
    }
}


int main(int argc, char const *argv[])
{
    thread task1(sensor_read);
    thread task2(process_data_1);

    task1.join();
    task2.join();

    return 0;
}


