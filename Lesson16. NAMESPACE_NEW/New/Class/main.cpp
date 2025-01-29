#include <iostream>

class Student {
public:
    std::string name;

    // Constructor
    Student(std::string n) { 
        name = n; 
    }

    void display() { 
        std::cout << "Student Name: " << name << std::endl; 
    }
};

int main() {
    // Cấp phát động một đối tượng Student
    Student s1("Tu"); //Vùng nhớ được đặt tại bộ nhớ Stack
    
    Student* s2 = new Student("Hoai"); //Vùng nhớ được đặt tại bộ nhớ Heap


    // Gọi phương thức của đối tượng
    s1.display();
    s2->display();
    // Giải phóng bộ nhớ
    delete s2;

    return 0;
}