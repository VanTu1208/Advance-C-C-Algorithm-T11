#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() { // Hàm ảo
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Dog gaugau" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Cat meows" << endl;
    }
};

void playSound(Animal* a) {
    a->makeSound(); // Gọi hàm ảo
}

int main() {
    Dog d;
    Cat c;
    
    playSound(&d); // Dog barks
    playSound(&c); // Cat meows

    return 0;
}