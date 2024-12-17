#ifndef CAL_H
#define CAL_H

typedef struct {
    float x1;
    float x2;
} Equation;

static int A,B,C;

void inputCoefficients(int a, int b, int c);

static float calculateDelta();

void result(Equation *equation);


#endif