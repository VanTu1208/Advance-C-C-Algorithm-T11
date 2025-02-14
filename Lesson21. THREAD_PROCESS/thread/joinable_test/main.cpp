#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int count1 = 0, count2 = 0;


void delay(uint32_t time)
{
    this_thread::sleep_for(chrono::milliseconds(time)); //delay theo ms   
}

void counter_1(uint32_t time_delay){
    int a = 0;
    while(a < 8)
    {
        cout << "Task 1 print counter: " << a << endl;
        delay(time_delay);
        a++;
        count1 = a;
    }
    
}

void counter_2(uint32_t time_delay){
    int a = 0;
    while(a < 6)
    {
        cout << "Task 2 print counter: " << a << endl;
        delay(time_delay);
        a++;
        count2 = a;
    }
    
}



int main(int argc, char const *argv[])
{
    thread task1(counter_1, 1000);

    thread task2(counter_2, 500);

    if(task1.joinable())
    {
        cout << "Task 1 chưa kết thúc hoặc chưa gọi join()" << endl;
        task1.join();
    }
    else 
    {
        cout << "Task 1 đã kết thúc hoặc đã gọi join()" << endl;
    }

    if(task2.joinable())
    {
        cout << "Task 2 chưa kết thúc hoặc chưa gọi join()" << endl;
        task2.join();
    }
    else 
    {
        cout << "Task 2 đã kết thúc hoặc đã gọi join()" << endl;
    }
    int a = 0;
    while(a < 3)
    {
        delay(2000);
        a++;
        cout << "Main task" << endl;
        
    }
    cout << "Count Task 1 = " << count1 << endl;
    cout << "Count Task 2 = " << count2 << endl;
    return 0;
}
