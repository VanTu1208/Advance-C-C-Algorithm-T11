#include <math.h>
#include <stdio.h>
#include "cal.h"


void inputCoefficients(int a, int b, int c) {
    A = a;
    B = b;
    C = c;
}

static float calculateDelta() 
{
    return B * B - 4 * A * C;
}

void result(Equation *equation) {
    float delta = calculateDelta();
    if (delta > 0) {
        equation->x1 = (-B + sqrt(delta)) / (2 * A);
        equation->x2 = (-B - sqrt(delta)) / (2 * A);
    } else if (delta == 0) {
        equation->x1 = equation->x2 = -B / (2 * A);
    } else {
        equation->x1 = equation->x2 = -1;
    }
}
