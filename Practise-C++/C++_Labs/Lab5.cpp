#include <iostream>
#include <stdlib.h> // for rand()
using std::cout;
using std::endl;

const int INITIALCAP = 10;

class DynArray {
public:
    DynArray();
    DynArray(int, int*);
    DynArray(const DynArray&);
    DynArray& operator=(const DynArray&);
    ~DynArray();
	void init(int size, int* initialData);

	bool set(int i, int v);
	int get(int i) const;
	int size() const;
	void print() const;

	void append(int x);

private:
	int size_;
	int capacity_;
	int* array_;
};

// Constructor. Set array to initial size 0 and initial capacity INITIALCAP
DynArray::DynArray() {
    cout << "Default constructor" << endl;
    array_ = new int[10];
    // IMPlEMENT ME
}

DynArray::DynArray(int size, int* initialData)
{
    capacity_ = size_ = size;
	array_ = new int[size];
	for(int i = 0; i < size; ++i)
		array_[i] = initialData[i];
}

DynArray::DynArray(const DynArray& copyArray)
{
    delete[] array_;
    size_ = copyArray.size_;
    capacity_ = copyArray.capacity_;
    array_ = new int[copyArray.size()];
    for (int i = 0; i < copyArray.size();i++)
    {
        array_[i] = copyArray.array_[i];
    }
}

DynArray& DynArray::operator=(const DynArray& other)
{
    if (&other != this)
    {
        delete[] array_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        array_ = new int[other.size()];
        for (int i = 0; i < other.size();i++)
        {
            array_[i] = other.array_[i];
        }
    }
    return *this;
}

// Destructor
DynArray::~DynArray() {
	cout << "Destructor" << endl;
    // IMPLEMENT ME
    delete[] array_;
    array_ = nullptr;
    
}

// Set the array to the given size with the data copied from the pointer
// initialData. This pointer is supposed to point to an int array of the
// correct size.
// This is supposed to be called once only after zero-parameter constructor.
// If called at other times, old data is lost and there will be memory leak.
// Really should rewrite this as a parameterized constructor
void DynArray::init(int size, int* initialData) {
	capacity_ = size_ = size;
	array_ = new int[size];
	for(int i = 0; i < size; ++i)
		array_[i] = initialData[i];
}

// Print the contents of the array.
void DynArray::print() const {
	cout << "[ ";
	for(int i = 0; i < size_; ++i)
		cout << array_[i] << " ";
	cout << "]" << endl;
}

// Set the i-th entry of the array to v.
bool DynArray::set(int i, int v) {
	if(i < 0 || i > size_) {
		return false;
	}
	array_[i] = v;
	return true;
}

// Return the i-th entry of the array.
// Doesn't check bounds...
int DynArray::get(int i) const {
	return array_[i];
}

// Return the number of elements stored.
int DynArray::size() const {
	return size_;
}

// Add x to the end of the array, expanding if necessary.
void DynArray::append(int x) {
	if (size_ == capacity_) {
		capacity_ *= 2;
		int* temp = new int[capacity_];
		for(int i=0;i<size_;i++) temp[i] = array_[i];
		delete [] array_;
		array_ = temp;
	}
	array_[size_++] = x;
}

int main() {

	// two primitive arrays
	int array1[10];
	for(int i = 0; i < 10; ++i) {
		array1[i] = rand()%100;
	}
	int array2[20];
	for(int i = 0; i < 20; ++i) {
		array2[i] = rand()%100;
	}

	// two DynArrays
	DynArray a1 = DynArray(10, array1);
	a1.print();

	DynArray a2 = DynArray(20, array2);
	a2.print();

	// this part is about deep copy, to be used later

	a2 = a1;
	cout << "copied a1 to a2." << endl;
	cout << "a2 new size: " << a2.size() << endl;
	cout << "a2 new content: ";
	a2.print();

	a1.set(0,888);
	cout << "a1 after modification: ";
	a1.print();
	cout << "a2 after a1's modification: ";
	a2.print();

	// try this and see what happens to a2?
	a1.append(999);
	a1.print();
	a2.print();

	return 0;
}
