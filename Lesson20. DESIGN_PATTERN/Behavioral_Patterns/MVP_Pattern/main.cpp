#include <iostream>
#include <string>

using namespace std;

class SinhVienModel{ //Chứa logic liên quan đến dữ liệu của ứng dụng, bao gồm các đối tượng, cơ sở dữ liệu
    private:
        string name;        //Tên từng sinh viên
        int age;            //Tuổi sinh viên
        string studentId;   //id sinh viên

    public:
        SinhVienModel(const string& name, int age, const string& studentId): name(name), age(age), studentId(studentId){}

        // setter method
        void setName(const string& newName){
            name = newName;
        }

        void setAge(int newAge){
            age = newAge;
        }

        void setStudentId(const string& newStudentId){
            studentId = newStudentId;
        }

        // getter method
        string getName() const{
            return name;
        }

        int getAge() const{
            return age;
        }

        string getStudentId() const{
            return studentId;
        }
};

class SinhVienView{ //Giao diện tương tác với người dùng
    public:
        //Hiển thị thông tin sinh viên
        void displayStudentInfo(const string& name, int age, const string& studentId){ 
            cout << "Thông tin sinh viên:" << endl;
            cout << "Tên: " << name << endl;
            cout << "Tuổi: " << age << endl;
            cout << "Mã số sinh viên: " << studentId << endl;
        }

        //Thêm thông tin sinh viên mới
        void inputStudentInfo(string& name, int& age, string& studentId){
            cout << "Nhập thông tin sinh viên:" << endl;

            cout << "Tên: ";
            getline(cin, name);

            cout << "Tuổi: ";
            cin >> age;
            cin.ignore();  // Bỏ qua ký tự newline trong buffer

            cout << "Mã số sinh viên: ";
            getline(cin, studentId);
        }
};

class SinhVienPresenter{ //Xử lý logic, điều phối dữ liệu từ Model đến View và ngược lại.

    private:
        SinhVienModel& model;
        SinhVienView&  view;

    public:
        SinhVienPresenter(SinhVienModel& m, SinhVienView& v): model(m), view(v){}

        void updateStudentInfo(){ //Xử lý việc thêm thông tin sinh viên từ view và gán vào dữ liệu bên trong model
            string name;
            int age;
            string studentId;
           
            view.inputStudentInfo(name, age, studentId);
            model.setName(name);
            model.setAge(age);
            model.setStudentId(studentId);
        }
        //Gọi hàm in từ view và lấy dữ liệu từ model
        void showStudentInfo(){
            view.displayStudentInfo(model.getName(), model.getAge(), model.getStudentId());
        }
};

int main()
{
    // Tạo model, view và presenter
    SinhVienModel model("Tuấn", 20, "HTN123");
    SinhVienView view;
    SinhVienPresenter presenter(model, view);

    int choice;
    do{
        cout << "\n1. Hiển thị thông tin sinh viên" << std::endl;
        cout << "2. Cập nhật thông tin sinh viên" << std::endl;
        cout << "3. Thoát" << std::endl;
        cout << "Nhập lựa chọn: ";
        cin >> choice;
        cin.ignore(); // Bỏ qua ký tự newline trong buffer
       
        switch (choice){
            case 1:
                presenter.showStudentInfo();
                break;
               
            case 2:
                presenter.updateStudentInfo();
                break;

            case 3:
                cout << "Thoát chương trình." << endl;
                break;

            default:
                cout << "Lựa chọn không hợp lệ!" << endl;
        }
       
    } while (choice != 3);

    return 0;
}


