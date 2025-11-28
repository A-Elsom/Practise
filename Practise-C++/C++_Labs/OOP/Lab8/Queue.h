#include <iostream>
#ifndef ARRAY_H_
#define ARRAY_H_
using std::cout;
using std::endl;

const int DEFAULT_CAPACITY = 5;

template <class T>
class Queue {
public:
	Queue(int capacity = DEFAULT_CAPACITY) : data_(new T [capacity]), head_(0), tail_(0), capacity_(capacity){

    }
	~Queue();
	void insert(const T& item){
        
    }
	T remove();
	void printAll(); // just for debugging
private:
	T* data_;
	int head_; // index to first element
	int tail_; // index to just past the last element
	int capacity_;
};

#endif