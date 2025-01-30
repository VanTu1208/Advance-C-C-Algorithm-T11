#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{

    vector <int> arr = {3,5,7,4,1};

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }

    int numFind = 7;
    auto index = find(arr.begin(),arr.end(), numFind);
    if (index != arr.end())
    {
        cout << "Đã tìm thấy "<< numFind <<" tại vị trí " << (index - arr.begin()) << endl;
    }
    else
    {
        cout << "Không tìm thấy " << numFind << endl;
    }



    sort(arr.begin(), arr.end());
    
    cout << "Sắp xếp vector tăng dần: " << endl;

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }

    sort(arr.begin(), arr.end(), greater<>());
    
    cout << "Sắp xếp vector giảm dần: " << endl;

    for (auto const var : arr)
    {
        cout << "Vector: " << var << endl;
    }


    
    
    
    

    return 0;
}


