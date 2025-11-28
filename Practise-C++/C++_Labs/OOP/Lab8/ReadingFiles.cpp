#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
    float height;
};

int main()
{
	string line;
	string element;
	char del = ' ';
	int i = 0;
	int n = 0;
	ifstream fin("input.txt");
	Person persons[4];
	// FILL IN THIS
	while(getline (fin, line)){
		//out<<line<<endl;
		persons[n] = Person();
		stringstream sLine(line);
		while(getline (sLine, element, del)){
			switch(i){
				case 0:
					persons[n].name = element;
					break;
				case 1:
					persons[n].age = stoi(element);
					break;
				case 2:
					persons[n].height = stof(element);
					break;
			}
			i++;
		}
		i=0;
		n++;
	}



	for(int i=0;i<4;i++) {
		cout << persons[i].name << " ";
        	cout << persons[i].age << " ";
        	cout << persons[i].height << endl;
    	}
    return 0;
}
