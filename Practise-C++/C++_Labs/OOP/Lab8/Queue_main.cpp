#include <iostream>
#include <string>
#include "Queue.h"
using namespace std;

int main() {

	Queue<int> iq;
    try{
        iq.insert(1);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.insert(2);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
	try{
       iq.insert(3);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.insert(4);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.remove();
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.remove();
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.remove();
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.insert(5);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.insert(6);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.insert(7);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
    try{
       iq.insert(8);
    }
    catch(std::overflow_error){
        cout<<"overflow Error"<<endl;
    }
    catch(std::underflow_error){
        cout<<"underflow Error"<<endl;
    }
    iq.printAll();
	

	Queue<string> sq(10);
	sq.insert("hello world");
	sq.printAll();
	//cout << sq.remove() << endl;
	sq.printAll();
	//cout << sq.remove() << endl;
	sq.printAll();

}
