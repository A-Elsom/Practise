#include <ios>
#include <iostream>
class Complex
{
private:
    
public:
    int a,b;
    void operator+(Complex&);
    friend std::ostream &operator<<(std::ostream &out, Complex C);
};