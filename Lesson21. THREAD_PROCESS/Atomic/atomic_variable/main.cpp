#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> shareValue(0); 
/*atomic là một struct template được dùng trên biến toàn cục để chia sẻ nhiều luồng khác nhau.
Giúp việc thao tác trên biến không bị gián đoạn gây sai xót dữ liệu */

void counter_1(int end){
    for(int i = 0; i < end; i++){
        ++shareValue;
    }
}

void counter_2(int end){
    for(int i = 0; i < end; i++)
        ++shareValue;
}

int main(int argc, char const *argv[])
{
    thread task1(counter_1, 10000);
    thread task2(counter_2, 10000);

    task1.join();
    task2.join();

    cout << shareValue << endl;
    return 0;
}
