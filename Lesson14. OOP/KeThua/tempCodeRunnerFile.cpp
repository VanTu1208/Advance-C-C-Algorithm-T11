#include <iostream>
#include <string>

using namespace std;

class DoiTuong{
    protected:
        string ten;
        int id;

    public:
        DoiTuong(){  
            static int ID = 1;
            id = ID;
            ID++;
        }

        void setName(string _ten){
            // check chuỗi nhập vào
            ten = _ten;
        }

        void display(){
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
        }
};

class SinhVien : public DoiTuong{
    protected:
        string chuyenNganh;

    public:
        void setChuyenNganh(string _nganh){
            chuyenNganh = _nganh;
        }

        void display(){ // override
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
            cout << "Chuyên ngành: " << chuyenNganh << endl;
        }
};

class HocSinh : public DoiTuong{
    protected:
        string lop;
   
    public:
        void setLop(string _lop){
            lop = _lop;
        }

        void display(){ // override
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
            cout << "Lớp: " << lop << endl;
        }
};

class GiaoVien : public DoiTuong{
    protected:
        string chuyenMon;

    public:
        void setChuyenMon(string _mon){
            chuyenMon = _mon;
        }

        void display(){ // override
            cout << "Tên: " << ten << endl;
            cout << "ID: " << id << endl;
            cout << "Chuyên môn: " << chuyenMon << endl;
        }
};

int main(int argc, char const *argv[])
{

    SinhVien sv1;
    sv1.setName("Trung");
    sv1.setChuyenNganh("Computer Engineering");
    sv1.display();

    cout << endl;

    HocSinh hs1;
    hs1.setName("Tuấn");
    hs1.setLop("12A1");
    hs1.display();

    cout << endl;

    GiaoVien gv1;
    gv1.setName("Hải");
    gv1.setChuyenMon("Lý");
    gv1.display();
    return 0;
}
