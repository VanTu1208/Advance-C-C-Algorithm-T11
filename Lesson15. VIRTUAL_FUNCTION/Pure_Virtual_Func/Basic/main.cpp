#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0; // Hàm ảo thuần túy
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing Square" << endl;
    }
};

int main() {
    
    //Shape shapeA; Không thể tạo đối tượng cho lớp trừu tượng
    
    Shape* shape1;
    Square h1;
    shape1 = &h1;

    Shape* shape2 = new Circle();   

    shape1->draw(); // Drawing Circle
    shape2->draw(); // Drawing Square

    delete shape2;

    return 0;
}