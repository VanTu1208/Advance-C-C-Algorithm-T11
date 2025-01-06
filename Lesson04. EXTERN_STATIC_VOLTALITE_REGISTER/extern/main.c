#include <stdio.h>
#include "print1.h"
#include "add.h"

int main(){
    
    print("Extern Variable: "); println_Int(externVariable);
    
    int result = add(3,5);

    print("Result: "); println_Int(result);
    
    return 0;
}