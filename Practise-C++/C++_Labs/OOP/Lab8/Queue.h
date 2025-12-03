#include <iostream>
#include <exception>
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
		if ((tail_ + 1) % capacity_ == head_) {
			throw std::overflow_error("b");
		}
		else{
			data_[tail_] = item;
			tail_ = (tail_ + 1) % capacity_;
		}
		
	}
		
	void remove(){
		
		T x;
		if (head_ == tail_) {
			throw std::underflow_error("a");
		}
		else{
			x = data_[head_];
			head_ = (head_ + 1) % capacity_;
		}
		
		//return x;
	}
	void printAll(){
		
		if (head_ <= tail_) {
			for(int i = 0; i < head_; i++) cout << "X ";
			for(int i = head_; i < tail_; i++) cout << data_[i] << " ";
			for(int i = tail_; i < capacity_; i++) cout << "X ";
		}
		else {
			for(int i = 0; i < tail_; i++) cout << data_[i] << " ";
			for(int i = tail_; i < head_; i++) cout << "X ";
			for(int i = head_; i < capacity_; i++) cout << data_[i] << " ";
		}
		cout << endl;
	} // just for debugging
private:
	T* data_;
	int head_; // index to first element
	int tail_; // index to just past the last element
	int capacity_;
};
