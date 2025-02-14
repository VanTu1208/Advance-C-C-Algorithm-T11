#include <iostream>

using namespace std;

class Sensor //Lớp trừu tượng Sensor
{
    public:
        virtual void readData() = 0; //Hàm thuần ảo readData()
};

// Cảm biến nhiệt độ
class TemperatureSensor : public Sensor
{
    public:
        void readData() override { //Ghi đè hàm readData()
            cout<<"Reading temperature data "<<endl;
        }
};

// Cảm biến độ ẩm
class HumiditySensor : public Sensor
{
    public:
        void readData() override { //Ghi đè hàm readData()
            cout<<"Reading humidity data "<<endl;
        }
};

// Decorator Pattern
class SensorDecorator : public Sensor
{
    protected:
        Sensor* wrappedSensor; //Con trỏ trỏ tới đối tượng gốc

    public:
        SensorDecorator(Sensor* sensor) : wrappedSensor(sensor){}

        virtual void readData() override {
            wrappedSensor->readData();
        }
};

// Thêm tính năng Log
class LoggingSensor : public SensorDecorator
{
    public:
        LoggingSensor(Sensor* sensor) : SensorDecorator(sensor){}

        void readData() override{
            cout<<"LOG: sensor data"<<endl;
            wrappedSensor->readData();
            //SensorDecorator::readData();
        }
};


int main(int argc, char const *argv[])
{
    Sensor* tempSensor = new TemperatureSensor(); //0x01
    Sensor* logTemp = new LoggingSensor(tempSensor); //0xa3 -> 0x01
    logTemp->readData();

    Sensor* humSensor = new HumiditySensor();//0x05
    Sensor* logHum = new LoggingSensor(humSensor); //0xb4 -> 0x05
    logHum->readData();

    return 0;
}


