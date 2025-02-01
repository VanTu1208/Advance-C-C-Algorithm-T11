#include <iostream>
#include <string>

using namespace std;

template <typename T>
class MyContainer {
private:
    T element;

public:
    MyContainer(T val) : element(val) {}

    T getValue() const {
        return element;
    }
};

int main()
{

    MyContainer<int> intContainer(42);
    MyContainer<double> doubleContainer(3.14);
    MyContainer<string> stringContainer("Trung");

    int intValue = intContainer.getValue();
    double doubleValue = doubleContainer.getValue();
    string stringValue = stringContainer.getValue();

    cout << "int value: " << intValue << endl;
    cout << "double value: " << doubleValue << endl;
    cout << "string value: " << stringValue << endl;

    return 0;
}
