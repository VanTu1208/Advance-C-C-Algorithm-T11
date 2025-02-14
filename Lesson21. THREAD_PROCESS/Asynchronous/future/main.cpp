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
    for (int i = 0; i < 7; i++)
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

void task1(uint32_t time)
{
    int i = 0;
    while (1)
    {
        unique_lock<mutex> ulock(mtx);
        cout << "Counter Task 1: " << i++ << endl;
        ulock.unlock();
        delay(time);
    }
}

void task2(uint32_t time)
{
    int i = 0;
    while (1)
    {
        unique_lock<mutex> ulock(mtx);
        cout << "Counter Task 2: " << i++ << endl;
        ulock.unlock();
        delay(time);
    }
}

int main(int argc, char const *argv[])
{
    future<int> sensor_future = async(launch::async, sensor_read); // sensor_read chạy độc lập với task1, task2 và main task
    /*
        async: Khởi tạo luồng bất đồng bộ
        aunch::async: Tạo và chạy task
        sensor_read: Hàm được thực thi
        future<int> sensor_future: Kết quả được lưu trữ vào biến int sensor_future

    */

    thread t1(task1, 1); // t1: đại diện cho luồng 1
    thread t2(task2, 3); // t2: đại diện cho luồng 2

    int i = 0;
    while (i < 10)
    {
        unique_lock<mutex> ulock(mtx);
        cout << "This is main, i = " << i++ << endl;
        ulock.unlock();
        delay(1);
    }

    cout << "Data đã hoàn thành 1: " << sensor_future.get() << endl; // delete
    //sensor_future.get() đọc giá trị cuối cùng của luồng bất đồng bộ và xóa để đảm bảo chỉ có một luồng được đọc.
    //cout << "Data đã hoàn thành 2: " << sensor_future.get() << endl;

    t1.join();
    t2.join();

    return 0;
}