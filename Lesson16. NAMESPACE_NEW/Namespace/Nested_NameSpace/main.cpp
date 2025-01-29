#include <iostream>

using namespace std;

namespace A{
    char *name = (char*)"space A";

    namespace C{
        char *str = (char*)"space C";
    }
}

namespace B{
    char *name = (char*)"space B";
}

using namespace A::C;

int main(int argc, char const *argv[])
{
    cout << "Name: " << A::name << endl;
    cout << "Name: " << B::name << endl;
    cout << "Name: " << str << endl;
    
    return 0;
}


