#include <iostream>
#include <thread>
#include <future>
#include <mutex>

using namespace std;

int sensor_data = 0;

mutex mtx;

void delay(uint32_t time)
{
    this_thread::sleep_for(chrono::seconds(time));
}

int sensor_read()
{
    for (int i = 0; i < 5; i++)
    {
        unique_lock<mutex> ulock(mtx);
        sensor_data = rand() % 100;
        cout << "Sensor read Data " << i << ", Value = " << sensor_data << endl;
        ulock.unlock();
        delay(1);
    }
    cout << "Read data done!\n";
    return sensor_data;
}

void task1(uint32_t time, shared_future<int> shF)
{
    delay(7);
    while (1)
    {
        unique_lock<mutex> ulock(mtx);
        cout << "Task 1 yêu cầu Data: " << shF.get() << endl;
        ulock.unlock();
        delay(time);
        
    }
}

void task2(uint32_t time, shared_future<int> shF)
{
    delay(7);
    while (1)
    {

        unique_lock<mutex> ulock(mtx);
        cout << "Task 2 yêu cầu Data: " << shF.get() << endl;
        ulock.unlock();
        delay(time);
        
    }
}

int main(int argc, char const *argv[])
{
    shared_future<int> sensor_share_future = async(launch::async, sensor_read).share(); // sensor_read chạy độc lập với task1, task2 và main task
    /*
        async: Khởi tạo luồng bất đồng bộ
        aunch::async: Tạo và chạy task
        sensor_read: Hàm được thực thi
        shared_future<int> sensor_share_future:  Kết quả được lưu trữ vào biến int sensor_future thuộc kiểu shared_future

        Tuy nhiên, mặc định hàm async sẽ trả về một giá trị thuộc kiểu future. Vì thể cần phải gọi phương thức share() để chuyển đổi
        future thành shared_future

    */

    thread t1(task1, 1, sensor_share_future); // t1: đại diện cho luồng 1
    thread t2(task2, 3, sensor_share_future); // t2: đại diện cho luồng 2

    int i = 0;
    while (i < 6)
    {
        unique_lock<mutex> ulock(mtx);
        cout << "This is main, i = " << i++ << endl;
        ulock.unlock();
        delay(1);
    }

    cout << "Main Task yêu cầu Data: " << sensor_share_future.get() << endl;//Chỉ đọc mà không xóa, có thể gọi nhiều lần

    t1.join();
    t2.join();

    return 0;
}