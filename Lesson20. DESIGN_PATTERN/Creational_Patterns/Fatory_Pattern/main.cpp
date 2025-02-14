#include <iostream>
#include <string>

using namespace std;

// Base class
class Sensor
{
    public:
        // phương thức ảo thuần túy đọc dữ liệu cảm biến
        virtual void readData() = 0;
};

// Concrete product: temperature
class TemperatureSensor : public Sensor
{
    public:
        // Đọc dữ liệu từ cảm biến nhiệt độ
        void readData() override
        {
            cout << "reading temp data..." << endl;
            // cấu hình, logic xử lý
        }
};

// Concrete product: humidity
class HumiditySensor : public Sensor
{
    public:
        // Đọc dữ liệu từ cảm biến độ ẩm
        void readData() override
        {
            cout << "reading humidity data..." << endl;
        }
};

// Concrete product: pressure
class PressureSensor : public Sensor
{
    public:
        // Đọc dữ liệu từ cảm biến áp suất
        void readData() override
        {
            cout << "reading pressure data..." << endl;
        }
};

// Concrete product: light
class LightSensor : public Sensor
{
    public:
        // Đọc dữ liệu từ cảm biến áp suất
        void readData() override
        {
            cout << "reading light data..." << endl;
        }
};

// Định nghĩa các loại cảm biến
typedef enum
{
    TEMPERATURE,    //0
    PRESSURE,       //1
    HUMIDITY,       //2
    LIGHT           //3
} SensorType;

// Sensor Factory để tạo ra các đối tượng cảm biến
class SensorFactory
{
    public:
        // Tạo đối tượng cảm biến dựa trên loại cảm biến
        static Sensor* createSensor(SensorType type)
        {
            switch (type) //Tạo switch để lựa chọn đối tượng thuộc lớp nào để khởi tạo
            {
                case SensorType::TEMPERATURE:
                    return new TemperatureSensor(); // 0xc8

                case SensorType::HUMIDITY:
                    return new HumiditySensor();    // 0xa1

                case SensorType::PRESSURE:
                    return new PressureSensor();    // 0xf4
               
                case SensorType::LIGHT:
                    return new LightSensor();       // 0x04

                default:
                    cout << "Invalid sensor type!\n";
                    return nullptr;
            }
        }
};

int main(int argc, char const *argv[])
{
    Sensor* sensor1 = SensorFactory::createSensor(TEMPERATURE);
    sensor1->readData();

    auto sensor2 = SensorFactory::createSensor(PRESSURE);
    sensor2->readData();

    auto sensor3 = SensorFactory::createSensor(HUMIDITY);
    sensor3->readData();

    SensorFactory::createSensor(LIGHT)->readData();

    return 0;
}

