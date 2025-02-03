#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec = {2,15,4,6,5,3,8,1,9};

    // sort(vec.begin(), vec.end(), greater<int>());

    cout << "Vector ban đầu: ";

    for (auto item : vec)
    {
        cout << item << " ";
    }
    cout << endl;

    // sắp xếp tăng dần
    sort(vec.begin(), vec.end(), [](int i, int j) -> bool
    {
        return i < j;
    });

    cout << "Vector sau khi sắp xếp: ";

    for (auto item : vec)
    {
        cout << item << " ";
    }
    cout << endl;

    cout << "Vector sau khi sắp xếp: ";

    // sắp xếp giảm dần
    sort(vec.begin(), vec.end(), [](int i, int j) -> bool
    {
        return i > j;
    });

    for (auto item : vec)
    {
        cout << item << " ";
    }
    cout << endl;


    int count_even = 0;
    int count_odd  = 0;

    vector<int> evens, odds;


    //vec.begin() và vec.end() xác định phạm vi của vector vec.
    //count_if sẽ duyệt từng phần tử trong phạm vi này, truyền từng phần tử đó vào lambda [&](int x).
    //x trong lambda là một tham số của hàm pred, được truyền vào từ count_if.
    
    count_if(vec.begin(), vec.end(), [&](int x)
    {
        if (x % 2 == 0)
        {
            count_even++;
            evens.push_back(x);
        } else {
            count_odd++;
            odds.push_back(x);
        }

        return false;
    });


    std::cout << "Số lượng số chẵn: " << count_even << endl;

    for (auto i : evens)
    {
        cout << i << " ";
    }

    cout << endl;

    cout << "Số lượng số lẻ: " << count_odd << endl;

    for (auto i : odds)
    {
        cout << i << " ";
    }

    return 0;
}
