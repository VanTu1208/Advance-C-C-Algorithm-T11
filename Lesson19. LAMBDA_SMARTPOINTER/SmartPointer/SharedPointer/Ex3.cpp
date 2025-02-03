#include <iostream>
#include <memory>

using namespace std;

class ECU
{
    public:
        ECU()
        {
            cout << "ECU initialized.\n"; 
        }

        ~ECU()
        { 
            cout << "ECU shutdown.\n"; 
        }

        void controlFunction(){
            cout << "Controlling ECU function...\n";
        }
};

void shareECU() 
{
    shared_ptr<ECU> ecu = make_shared<ECU>();

    // Chia sẻ ECU giữa hai module
    shared_ptr<ECU> module1 = ecu;
    shared_ptr<ECU> module2 = ecu;

    module1->controlFunction();
    module2->controlFunction();

    // Khi tất cả các shared_ptr đến ECU bị hủy, đối tượng ECU sẽ được giải phóng
}

int main(int argc, char const *argv[])
{
    shareECU();
    return 0;
}
