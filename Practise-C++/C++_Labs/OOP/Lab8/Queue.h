#include <iostream>
using std::cout;
using std::endl;

const int DEFAULT_CAPACITY = 5;

template <class T>
class Queue {
public:
	Queue(int capacity = DEFAULT_CAPACITY) : data_(new T [capacity]), head_(0), tail_(0), capacity_(capacity){

    }
	~Queue(){
		delete [] data_;
	}
	void insert(const T& item){
		int currentIndex = tail_;
        if((tail_+ 1) == capacity_){
			//move to front of array and loop til space found
			currentIndex = 0;
		}
		bool hasPlaced = false;
		while(currentIndex != data_[head_] && !hasPlaced){
			if(data_[currentIndex] == nullptr){
				data_[currentIndex] = item;
				tail_ = currentIndex;
				hasPlaced = true;
			}
			currentIndex++;
		}
		if(hasPlaced){
			return;
		}
		
    }
	T remove(){
		if(tail_ == head_){
			cout<<"error- good luck guessing what it is";
		}
		T* tmp = data_[head_];
		data_[head_] = nullptr;
		if(head_ + 1 == Capacity_){
			head_ = 0;
		}
		else{
			head_ += 1;
		}
		return &tmp;
	}
	void printAll(); // just for debugging
private:
	T* data_;
	int head_; // index to first element
	int tail_; // index to just past the last element
	int capacity_;
};
