#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void delay(uint32_t time)
{
    this_thread::sleep_for(chrono::milliseconds(time)); //delay theo ms   
}

void counter_1(uint32_t time_delay){
    int a = 0;
    while(a < 100)
    {
        cout << "Task 1 print counter: " << a << endl;
        delay(time_delay);
        a++;
    }
}

void counter_2(uint32_t time_delay){
    int a = 0;
    while(a < 100)
    {
        cout << "Task 2 print counter: " << a << endl;
        delay(time_delay);
        a++;
    }
}



int main(int argc, char const *argv[])
{
    thread task1(counter_1, 1000);

    thread task2(counter_2, 2000);

    task1.join();

    while(1)// Đại diện cho luồng chính, không bao giờ kết thúc làm xảy ra lỗi
    {
        int a = 0;
        while(a < 100)
        {
            cout << "Main task print counter: " << a << endl;
            delay(3000);
            a++;
        }
    }
    return 0;
}
