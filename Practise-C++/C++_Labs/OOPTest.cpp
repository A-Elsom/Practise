#include <iostream>
using namespace std;

class myClass
{
public:
    double xPos, yPos;
    string output;

    string movement(string input)
    {
        if (input == "w")
        {
            output = "up";
        }
        else if (input == "d")
        {
            output = "right";
        }
        else if (input == "a")
        {
            output = "left";
        }
        else
        {
            output = "down";
        }
        return output;
    }
};

int main()
{
    myClass* newClass = new myClass();
    string input;
    cin >> input;
    while (input != "-1")
    {
        cout << newClass->movement(input);
        cin >> input;
    }
}