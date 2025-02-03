#include <iostream>
#include <memory>   // Cần thiết để sử dụng smart pointer

using namespace std;

class SpeedSensor
{
    private:
        int data;

    public:
        SpeedSensor(int value): data(value){
            cout << "Constructor called, data = " << data << endl;
        }

        ~SpeedSensor(){
            cout << "Destructor called\n";
        }

        void readData(){
            cout << "Reading speed data...\n";
        }

        void setData(int value){
            data = value;
        }

        void display(){
            cout << "Data: " << data << endl;
        }
};

int main() 
{
    unique_ptr<SpeedSensor> uptr = make_unique<SpeedSensor>(10);
    // unique_ptr<SpeedSensor> uptr(new SpeedSensor(10));


    uptr->display();
    uptr->readData();
    uptr->setData(20);
    uptr->display();



    (*uptr).display();
    /***************************************************************
     * sử dụng toán tử (*), ta sẽ lấy ra được đối tượng kiểu SpeedSensor,
     * từ đó có thể sử dụng toán tử (.) để truy cấp các biến và hàm
     * thành viên của đối tượng này
     **************************************************************/    


    /* sử dụng release() để tách quyền sở hữu và trả về con trỏ thô */
    cout << "\nrelease()\n";
    SpeedSensor *rawPtr = uptr.release();
    if (!uptr){
        cout << "ptr đã bị tách quyền sở hữu và trở thành nullptr\n";
    }
    rawPtr->display();  // truy cập đối tượng bằng con trỏ thô
    delete rawPtr;      // phải giải phóng bộ nhớ thủ công khi dùng con trỏ thô

    
    /* sử dụng reset() để giải phóng đối tượng cũ và gán đối tượng mới */
    cout << "\nreset()\n";
    uptr.reset(new SpeedSensor(50)); // ptr quản lý đối tượng mới
    uptr->display();                 // truy cập đối tượng mới


    /* sử dụng get() để trả về con trỏ thô nhưng vẫn giữ nguyên quyền sở hữu */
    cout << "\nget()\n";
    uptr = make_unique<SpeedSensor>(30);
    SpeedSensor *rawPtr2 = uptr.get();   // get() trả về con trỏ thô nhưng ptr vẫn sở hữu đối tượng
    rawPtr2->display();
    cout << "ptr vẫn sở hữu đối tượng\n";


    /* sử dụng operator = với std::move() để chuyển quyền sở hữu */
    cout << "\nmove()\n";
    unique_ptr<SpeedSensor> newPtr = move(uptr); // chuyển quyền sở hữu từ ptr sang newPtr
    if (!uptr){
        cout << "ptr đã trở thành nullptr sau khi chuyển quyền sở hữu\n";
    }
    newPtr->display();  // newPtr giờ sở hữu đối tượng
    return 0;
}
