#include <iostream>
#include <thread>
#include <future>
#include <chrono>


using namespace std;


int asyncTask(){
    this_thread::sleep_for(chrono::seconds(7));
    return 100;
}


int main(int argc, char const *argv[])
{
    future<int> ft = async(launch::async, asyncTask);


    cout << "LOG 1" << endl;


    if (ft.wait_for(chrono::seconds(1)) == future_status::ready){
        cout << "Task completed!\n";
    }
    else{
        cout << "Task is still running...\n";
    }
    cout << "Result: " << ft.get() << endl;    
    return 0;
}
