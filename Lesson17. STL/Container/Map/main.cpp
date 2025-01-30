    #include <map>
    #include <iostream>
    #include <string>

    using namespace std;

    struct Animal{
        string EnglishName;
        int soChan;
        string thucAn;
    };

    int main() {
        map<int, string> myMap;// Khai báo đối tượng map với key kiểu int và value kiểu string
        // Thêm phần tử vào map
        myMap[5] = "Five";// Thêm một cặp key-value: 5:"Five"
        myMap[3] = "Three";// Thêm một cặp key-value: 3:"Three"
        myMap[1] = "One";// Thêm một cặp key-value: 1:"One"
        myMap[2] = "Two";// Thêm một cặp key-value: 2:"Two"
        
        myMap.insert({4, "Four"}); // Thêm 1 cặp key-value: 4:"Four"
        myMap.erase(2); //Xóa key 2. Chỉ cần truyền key cần xóa, sẽ tự động xóa value ứng với key đó.

        map<string, Animal> myMap1 = 
        {
            {
                "Chó", {
                    "Dog",
                    4,
                    "Ăn tạp"
                }
            },
            {
                "Gà", {
                    "Chicken",
                    2,
                    "Ăn tạp"
                }
            },
            {
                "Sư tử", {
                    "Lion",
                    4,
                    "Ăn thịt"
                }
            }
        };



        //Đọc dữ liệu cách 1
        for (auto var : myMap)
        {
            cout << "Key: " << var.first << " , " << "Value: " << var.second << endl; //first ứng với key, second là value ứng với key
        }
        cout << endl;
        
        //Cách 2
        map<string,Animal> ::iterator it;
        for (it = myMap1.begin(); it != myMap1.end(); ++it)
        {
            cout << "Key: " << (*it).first << " , " << "Value: " << "English:" << (*it).second.EnglishName << " - Số chân: " << (*it).second.soChan << " - Thức ăn: " << (*it).second.thucAn <<  endl;
        }
        
        

        return 0;
    }



