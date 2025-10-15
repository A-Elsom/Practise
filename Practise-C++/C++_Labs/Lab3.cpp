#include <iostream>
#include <cstring>
using namespace std;

/*
    int main(int arg4 , char* arg1[]) {

        
        int* p;
        p = new int[10];
        p[0] = 999;
        cout << p[0] << endl;
        delete [] p;
        
        cout<<"Argument 1 is : " << arg1[1];
        cout<<"Argument 2 is : " << arg1[2];
        cout<<"Argument 3 is : " << arg1[3];
        return 0;
}
*/
int extraTask();

int main(){
    extraTask();
    return 0;
}

int extraTask()
{
    char buff[9];
	char flag = 'N';

	while(flag != 'Y') {

		cout << "Enter your 8-character password:" << endl;
		cin >> buff;

		// correct password is "gfhk7346"
		if (strcmp(buff, "gfhk7346") == 0) flag = 'Y';
		else cout << "FAIL" << endl;
	}
		
	cout << "PASS" << endl;

	return 0;
}

/*
    1 - possibly no errors but would be an Index out of bounds
    2 - possibly no errors, shouldnt be an issue as nothing is dereferenced
    3 - throws an error double free detected
    4 - No errors
    5 - segmentation fault
    6 - no errors
    7 - no errors
*/