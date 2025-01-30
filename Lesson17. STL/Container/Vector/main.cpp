#include <iostream>
#include <vector>

using namespace std;


void printVector(vector <int> arr){
    for (int i = 0; i < arr.size(); i++)
    {
        cout  << arr.at(i) << " ";
    }
    cout << endl;
    cout << "-----------" << endl;
}

void printVector1(vector <int> arr){
    vector<int>::iterator item;// Tạo một con trỏ quét qua từng địa chỉ của các phần tử trong vector
    
    for (item = arr.begin(); item != arr.end(); item++) //begin: địa chỉ tại phần tử bắt đầu; end: địa chỉ sau địa chỉ cuối cùng của vector
    {
        cout  << *item << " ";
    }
    cout << endl;
    cout << "-----------" << endl;
}

int main()
{
  
    vector <int> arr = {2,5,7,4,9};
    printVector(arr);

    arr.at(0) = 3;
    arr.pop_back();
    arr.resize(7);
    printVector1(arr);
    

    arr.push_back(10);
    printVector(arr);

    arr.insert(arr.begin() + 2, 20); // Thêm giá trị 20 vào vị trí arr[2] và dịch các phần tử phía sau
    printVector(arr);

    arr.erase(arr.end() - 5);
    printVector(arr);

    return 0;
}



