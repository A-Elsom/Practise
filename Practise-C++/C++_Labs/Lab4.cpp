#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node(int i, Node* p) {
		data = i;
		next = p;
	}
};

// print all integers in the list, in order
void print(Node* head)
{
    if (head == nullptr)
    {
        cout << "no head" << endl;
        return;
    }
    if (head->next == NULL)
    {
        cout << head->data << endl;
        return;
    }
    cout << head->data << " , ";
    print(head->next);
    return;
}

// find integer t from the list, returning a pointer to that node.
// If there are more than one match, return the first one.
// if not found, return nullptr
Node* find(Node* head, int t) {
	Node* tmp = head;
	while(tmp != nullptr) {
		if (tmp->data == t) return tmp;
		tmp = tmp->next;
	}
	return tmp;
}

// insert integer t to the list as the new head
// (yep, you can pass pointers by reference!)
void insert_head(Node*& head, int t) {
	Node* tmp = new Node(t, head);
	head = tmp;
}

// insert t as a new node after "location"
// location is assumed to point to a valid position in the list
void insert_after(Node* location, int t) {
    Node* newNode = new Node(t, NULL);
    if (location->next == NULL)
    {
        location->next = newNode;
        return;
    }
    Node* temp = location->next;
    location->next = newNode;
    newNode->next = temp;
    return;
}

// remove head from the list
void remove_head(Node*& head) {
    // IMPLEMENT ME
    Node* temp = head->next;
    head->data = temp->data;
    head->next = temp->next;
    delete temp;
    temp = nullptr;
    return;
}

// remove the NEXT integer i.e. AFTER the one pointed to by "location",
// NOT the one pointed to by it.
// location is assumed to point to a valid position in the list.
// If there is no next integer after location (i.e. location points to
// the last one) do nothing
void remove_after(Node* location) {
    // IMPLEMENT ME
    if (location->next == NULL)
    {
        return;
    }
    Node* temp = location->next;
    location->next = temp->next;
    delete temp;
    temp = nullptr;
    return;
}

// delete all nodes and release all memory
void cleanup(Node*& head, int level) {
    // IMPLEMENT ME
    if (head->next == nullptr)
    {
        return;
    }
    
    cleanup(head->next, level++);
    Node* temp = head->next;
    head->next = nullptr;
    delete temp;
    temp = nullptr;
    level--;
    if (level == 0)
    {
        Node* hTemp = head;
        head = nullptr;
        delete hTemp;
        hTemp = nullptr;
    }
    
    return;
}

int main() {
	// some example usage of these functions
	Node* mylist = nullptr;
	print(mylist);
	insert_head(mylist, 1);
	insert_head(mylist, 2);
	insert_head(mylist, 3);
	print(mylist);
	Node* result = find(mylist,3);
	if (result != nullptr) insert_after(result, 5);
	print(mylist);
	remove_head(mylist);
	print(mylist);
	remove_after(find(mylist,5));
	print(mylist);
	cleanup(mylist, 0);
	print(mylist);

}
