    #include <iostream>

    using namespace std;

    class HinhChuNhat
    {
    public:
        double chieuDai;
        double chieuRong;
        static int count;

        HinhChuNhat(int dai, int rong)
        {
            chieuDai = dai;
            chieuRong = rong;
            count++;
        }

        ~HinhChuNhat(){
            cout << "Dien tich: " << chieuDai * chieuRong << endl;
        }

        static void display()
        {
            cout << "Number of object: " << count << endl;
        }
    };

    int HinhChuNhat::count = 0;

    int main()
    {
        HinhChuNhat::display();

        HinhChuNhat Hinh1(5, 3);
        HinhChuNhat Hinh2(6, 1);

        HinhChuNhat::display();

        return 0;
    }
