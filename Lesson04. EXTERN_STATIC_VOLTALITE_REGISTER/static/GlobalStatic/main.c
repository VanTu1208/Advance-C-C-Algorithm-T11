#include <stdio.h>
#include "cal.h"


int main(){
    Equation res;
    inputCoefficients(2,4,1);
    result(&res);

    printf("Ket qua cua phuong trinh bac 2: x1 = %f, x2 = %f", res.x1, res.x2);
    return 0;
}