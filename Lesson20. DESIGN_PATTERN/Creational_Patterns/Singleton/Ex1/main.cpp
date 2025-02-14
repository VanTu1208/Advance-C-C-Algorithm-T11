#include <iostream>

void gpioInit();

void gpioSetPin(int pin, bool value);

void gpioReadPin(int pin);

class GpioManager{
    private:
        void init(){
            gpioInit();
        }
         // Private Constructor 
        GpioManager()
        {
            init();
        }
        
        static GpioManager* instance; //Static Property, trỏ tới một Object duy nhất của Class.
        
    public:
        static GpioManager *getInstace(){ //Static Method: Gọi trực tiếp thông qua Class.
            if(instance == nullptr){// Chỉ khởi tạo đối tượng lần đầu tiên.
                instance = new GpioManager();//Tao đối tượng được cấp phát động, địa chỉ được quản lý bởi con trỏ instance.
                
            }
            return instance;// Trả về dịa chỉ đối tượng được cấp phát.
        }
        void setPin(int pin, bool value){
            gpioSetPin(pin, value);
        }
        void readPin(int pin){
            gpioReadPin(pin);
        }
};

class PORTx{
    private:
        PORTx();
        static PORTx* instance;
        void init(){
            //gpioInit();
        }
    public:
        static PORTx *getInstace(){
            if(!instance){
                instance = new PORTx();
                instance->init();
            }
            return instance;
        }
};


GpioManager* GpioManager::instance = nullptr; //Cấp phát địa chỉ cố định cho Private Property.

int main(int argc, char const *argv[])
{
    GpioManager* gpioManager = GpioManager::getInstace(); //Gọi hàm để khởi tạo đối tượng

    gpioManager->setPin(2, 1);

    gpioManager->readPin(2);

    GpioManager* gpioManager2 = GpioManager::getInstace(); // Gọi hàm để khởi tạo đối tượng nhưng không thể tạo mới mà lấy địa chỉ của đối tượng trên.

    return 0;
}







