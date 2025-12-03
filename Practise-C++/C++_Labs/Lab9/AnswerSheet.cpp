#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

map<string,int>scores;

void addScore(int score, string name){
    scores[name] += score;
}

void eraseMark(string name){
    scores.erase(name);
}

int printMark(string name){
   
    int temp = scores[name];
    return temp;
}

int main(){
   
    string line;
	string element;
    string name;
    int score;
    int type;
	char del = ' ';
    int amount = 0;
    int n = 0;
	ifstream fin("input.txt");
	// FILL IN THIS
	while(getline (fin, line)){
		//out<<line<<endl;
		stringstream sLine(line);
        if(n == 0){
            amount = stoi(line);
        }else{
            if(n <= amount + 1){
                cout<<line<<endl;
                getline(sLine, element, del);
                type = stoi(element);//gets type
                switch(type){
                    case 1:
                        getline(sLine, element, del);
                        name = element;
                        getline(sLine, element, del);
                        score = stoi(element);
                        addScore(score,name);
                        cout << scores[name]<<endl;
                        break;
                    case 2:
                        getline(sLine, element, del);
                        name = element;
                        eraseMark(name);
                        break;
                    case 3:
                        getline(sLine, element, del);
                        name = element;
                        cout<<name<<endl;
                        score = printMark(name);
                        if(score == -1){
                            cout<<"0"<<endl;
                        }
                        else{
                            cout<<score<<endl;
                        }
                        
                        break;
                }
                cout<<"type : "<<type<<" name : "<<name<<" score : "<<score<<endl;
            }
        }
        name = "";
        score = 0;
        type = 0;
        n++;
    }
}