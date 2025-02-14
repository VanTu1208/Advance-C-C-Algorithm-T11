#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Interface for observers (display, logger, etc.)
class Observer
{
    public:
        virtual void update(float temperature, float humidity, float light) = 0; // Hàm thuần ảo Update để lớp con ghi đè;
};


//__________CONCRETE OBSERVER_____________

// Display component (an observer)
class Display : public Observer
{
public:
    void update(float temperature, float humidity, float light) override //Ghi đè hàm Update với chức năng hiển thị
    {
        cout << "Display: Temperature: " << temperature
             << ", Humidity: " << humidity
             << ", Light: " << light << endl;
    }
};

// Logger component (an observer)
class Logger : public Observer
{
public:
    void update(float temperature, float humidity, float light) override
    {
        cout << "Logging data... Temp: " << temperature
             << ", Humidity: " << humidity
             << ", Light: " << light << endl;
    }
};




// Subject (SensorManager) holds the state and notifies observers
class SensorManager
{
    float temperature;
    float humidity;
    float light;
    vector<Observer *> observers; //Vector lưu trữ danh sách Observer.

    public:
        void registerObserver(Observer *observer) // Thêm một thành viên Observer
        {
            observers.push_back(observer);
        }

        void removeObserver(Observer *observer) // Xóa một thành viên Observer
        {
            observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
            /*
                Hàm (remove(observers.begin(), observers.end(), observer) là hàm nằm trong thư viện Std
                    Chức năng: 
                        Duyệt qua các phần tử của vector.
                        Tìm kiếm các Object cần xóa và sau đó chuyển chúng về cuối danh sách
                            Ví dụ: {3,5,1,6,1,8} - Xóa giá trị 1 thông qua hàm remove thành {3,5,6,8,1,1}
                    Đồng thời trả về một iterator trỏ đến vị trí đầu tiên của object cần xóa - tức vị trí phần tử số 1 đầu tiên
                Hàm erase(const_iterator __first, const_iterator __last) sẽ xóa các phần tử trong khoảng địa chỉ được truyền vào.
            */

        }

        void notifyObservers() //Thông báo cho Observer
        {
            for (auto observer : observers)
            {
                observer->update(temperature, humidity, light); //Duyệt qua từng Observer và gọi hàm Update để thực thi các chức năng
            }
        }

        void setMeasurements(float temp, float hum, float lightLvl) // Hàm mô phỏng cập nhật giá trị cảm biến.
        {
            temperature = temp;
            humidity = hum;
            light = lightLvl;
            notifyObservers();
        }
};



int main()
{
    //Tạo đối tượng Subject
    SensorManager sensorManager;

    //Tạo các đối tượng Observer tương ứng với những chức năng khác nhau
    Display displayLCD, displayOled;
    Logger logger;

    //Đăng ký displayLCD và logger làm thành viên
    sensorManager.registerObserver(&displayLCD);
    sensorManager.registerObserver(&logger);
    sensorManager.registerObserver(&displayOled);

    //Gọi các hàm để mô phỏng thay đổi giá trị của cảm biến
    sensorManager.setMeasurements(25.0, 60.0, 700.0);
    
    //Xóa Observer displayOled.
    sensorManager.removeObserver(&displayOled);

    cout << "------------------------------ \n";

    sensorManager.setMeasurements(26.0, 65.0, 800.0); // Another sensor update

    return 0;
}
