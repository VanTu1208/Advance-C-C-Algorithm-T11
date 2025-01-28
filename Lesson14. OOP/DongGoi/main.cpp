#include <iostream>
#include <string>
using namespace std;

class SinhVien{
    private:
        string name;
        int id;
        float score;
   
    public:
        SinhVien(){
            static int ID = 1;
            id = ID;
            ID++;
        }

        void setName(string newName){   // setter method
            // kiểm tra điều kiện
            name = newName;
        }

        string getName(){   // getter method
            return name;
        }

        void setScore(float newScore){   // setter method
            // kiểm tra điều kiện
            score = newScore;
        }

        float getScore(){   // getter method
            return score;
        }

        int getID(){
            return id;
        }

        void display(){
            cout << "ID: " << getID() << endl;
            cout << "Ten: " << getName() << endl;
            cout << "Score: " << getScore() << endl;
        }
};

int main(int argc, char const *argv[])
{
    SinhVien sv1, sv2;

    sv1.setName("Trung");
    sv1.setScore(9.2);
    sv1.display();

    cout << endl;

    sv2.setName("Anh");
    sv2.setScore(7.6);
    sv2.display();
    return 0;
}
