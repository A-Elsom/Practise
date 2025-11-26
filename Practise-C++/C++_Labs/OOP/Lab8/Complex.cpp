#include "Complex.h"
#include <iostream>
void Complex::operator+(Complex& x){
    a = a + x.a;
    b = b + x.b;
}

std::ostream& operator<<(std::ostream &out, Complex c){
    out << c.a << " + i"<<c.b;
    return out;
}
