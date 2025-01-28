#include <iostream>
using namespace std;

class Dad {
public:
    virtual void display() { // Phương thức ảo
        cout << "Display từ lớp Dad" << endl;
    }
};

class ConA : public Dad {
public:
    void display() override { // Ghi đè phương thức của lớp cha
        cout << "Display từ lớp conA" << endl;
    }
};

class Mom {
public:
    void display() { // Phương thức ảo
        cout << "Display từ lớp Mom" << endl;
    }
};


class ConB : public Mom {
public:
    void display() { // Ghi đè phương thức của lớp cha
        cout << "Display từ lớp conB" << endl;
    }
};

int main() {
    
    Dad* D;
    ConA A;
    D = &A;
    
    D->display(); 

    Mom* M;
    ConB B;
    M = &B;

    M->display();

    return 0;
}