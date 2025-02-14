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

bool check_data = false;// False: chưa đọc dữ liệu, true đã đọc dữ liệu

mutex mtx;

condition_variable cv;

void sensor_read(){
    while (1){
        delay(2);
        sensor_data = rand() % 100; //Mô phỏng để đọc giá trị ngẫu nhiên
        check_data = true;  //đã đọc xong dữ liệu
        unique_lock<mutex> lock(mtx); //Khóa để sử dụng ngoại vi terminal
        cout << "Read data done!\n";
        lock.unlock(); //Bỏ khóa terminal
        cv.notify_one(); //Gửi thông báo đến một luồng xử lý
    }
}

void process_data(){
    while (1){
        unique_lock<mutex> uniquelock(mtx);
        cv.wait(uniquelock, []()->bool{return check_data;}); //Mở khóa tạm thời để kiểm tra check_data từ luồng 1, nếu true thì thoát và khóa luồng lại, false thì chờ
        /*
            wait(unique_lock<mutex>& __lock, _Predicate __p)
            {
                while (!__p())
                wait(__lock);
            }
                - unique_lock<mutex>& __lock: Một biến unique_lock để cung cấp cả cơ chế thủ công và tự động, không thể dùng lock_guard
                - _Predicate __p là một lambda để kiểm tra giá trị true hoặc false
                    Trong hàm wait() sẽ có một vòng lặp đệ quy, nếu tham số 2 trả về false thì sẽ gọi lại hàm wait và tiếp tục chờ.
                    Nếu trả về true thì thoát ra hàm wait
        */ 
        cout << "Data: " << sensor_data << endl;
        uniquelock.unlock();// Sau khi sử dụng terminal thì mở khóa để luồng khác có thể sử dụng
        check_data = false; 
    }
}

int main(int argc, char const *argv[])
{
    thread task1(sensor_read);
    thread task2(process_data);

    task1.join();
    task2.join();

    return 0;
}
