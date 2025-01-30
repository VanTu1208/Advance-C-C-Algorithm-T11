#include <iostream>
#include <list>

using namespace std;

void printList(list <int> lst){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {   
        cout << *it << " ";
    }    
    cout << endl << "----------------" << endl;
}



void insertListItem(list <int> &lst ,int position, int value){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == position)
        {
            lst.insert(it,value);
            break;
        }
        i++;
    }
}

void eraseListItem(list <int> &lst ,int position){
    list <int> :: iterator it;
    int i = 0;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == position)
        {
            lst.erase(it);
            break;
        }
        i++;
    }
}



int main()
{
  
    list <int> arr1;

    arr1.push_back(5);
    arr1.push_back(3);
    arr1.push_back(6);
    arr1.push_back(2);
    arr1.push_back(9);
    arr1.push_front(1);

    //in các phần tử, cách 1:
    for(auto item : arr1){
        cout << item << " ";
    }
    cout << endl << "----------------" << endl;


    //Cách 2:
    list <int> :: iterator it;
    int i = 0;
    for (it = arr1.begin(); it != arr1.end(); it++)
    {   
        cout << *it << " ";
    }    
    cout << endl << "----------------" << endl;


    arr1.pop_back();
    printList(arr1);

    arr1.pop_front();
    printList(arr1);


    insertListItem(arr1, 2, 15);
    printList(arr1);


    eraseListItem(arr1, 3);
    printList(arr1);

    return 0;
}

