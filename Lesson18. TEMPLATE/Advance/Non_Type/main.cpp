#include <iostream>
using namespace std;

template <typename T, int N>
class Array {
private:
    T arr[N];
public:
    void set(int index, T value) {
        if (index >= 0 && index < N) {
            arr[index] = value;
        }
    }
    T get(int index) {
        return arr[index];
    }
    int size() {
        return N;
    }

    void print(){
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array<int, 5> arrInt;
    arrInt.set(0, 10);
    arrInt.set(1, 6);
    arrInt.set(2, 3);
    cout << "Kích thước mảng: " << arrInt.size() << endl;
    arrInt.print();

    Array<string, 3> arrString;
    arrString.set(1, "Tu");
    arrString.set(0, "Toan");
    arrString.set(2, "Hung");

    cout << "Kích thước mảng: " << arrString.size() << endl;
    arrString.print();

    return 0;

}