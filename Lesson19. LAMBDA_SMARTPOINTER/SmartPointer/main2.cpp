#include <iostream>

using namespace std;

/*
 * unique pointer
 * shared pointer
 * weak pointer
 */

void test()
{
    int *ptr = (int*)malloc(5); // 0xf0 - 0xf4

    ptr = nullptr;

    int *ptr1 = (int*)0xf1;
}

int main(int argc, char const *argv[])
{

    return 0;
}
