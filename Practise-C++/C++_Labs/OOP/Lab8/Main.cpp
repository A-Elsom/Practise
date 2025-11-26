#include "Complex.h"
#include <iostream>

int main(){
    Complex a;
    Complex b;;

    a.a = 3;
    a.b = 4;
    b.a = 5;
    b.b = 6;

    a+b;
    std::cout<<a;
    return 0;
}