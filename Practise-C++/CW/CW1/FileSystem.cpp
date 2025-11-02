#include "FileSystem.h"

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling) {
	// IMPLEMENT ME
    name_ = name;
    isDir_ = isDir;
    parent_ = parent;
    leftmostChild_ = leftmostChild;
    rightSibling_ = rightSibling;
}

Node::~Node() {
    // IMPLEMENT ME
    if (isDir_)
    {
        clearChildren(this);
    }
    else
    {
        leftSibling()->rightSibling_ = rightSibling_;
    }
    rightSibling_ = nullptr;
    leftmostChild_ = nullptr;
    parent_ = nullptr;
    delete this;
}

void Node::clearChildren(Node* currentNode)
{
    Node* tempNode = currentNode;
    if (currentNode->isDir_)
    {
        clearChildren(currentNode->leftmostChild_);
        return;
    }
    if (currentNode->rightSibling_ == nullptr)
    {
        return;
    }
    else
    {
        clearChildren(currentNode->rightSibling_);
        tempNode = currentNode->rightSibling_;
        tempNode->rightSibling_ = nullptr;
        tempNode->leftmostChild_ = nullptr;
        tempNode->parent_ = nullptr;
        delete tempNode;
        tempNode = nullptr;
        return;
    }
}

Node* Node::containsRequestedDir(string reqDir)
{
    Node* currentNode = this;
    while (currentNode->rightSibling_ != nullptr)
    {
        if (currentNode->name_ == reqDir)
        {
            return currentNode;
        }
        currentNode = currentNode->rightSibling_;
    }
    return nullptr;
}

Node* Node::leftSibling() const {
	// IMPLEMENT ME
    
    if (parent_->leftmostChild_ != this)
    {
        Node* currentNode = parent_->leftmostChild_;
        while (currentNode->rightSibling_ != this)
        {
            currentNode = currentNode->rightSibling_;
        }
        if (currentNode->rightSibling_ == this)
        {
            return currentNode;
        }
    }
    return nullptr; // dummy
}

FileSystem::FileSystem() {
    // IMPLEMENT ME
    root_ = new Node("root", true);
}

// DO NOT CHANGE
FileSystem::FileSystem(const string& testinput) {

	curr_ = root_ = new Node("", true);

	if (testinput == "1") {
		Node* e   = new Node("e"      , true , root_);
		Node* d   = new Node("d.txt"  , false, root_, nullptr, e);
		Node* c   = new Node("c.txt"  , false, root_, nullptr, d);
		Node* b   = new Node("b"      , true , root_, nullptr, c);
		Node* a   = new Node("a.txt"  , false, root_, nullptr, b);
		Node* ee  = new Node("ee.txt" , false, e);
		Node* bb2 = new Node("bb2"    , true , b);
		Node* bb1 = new Node("bb1"    , true , b, nullptr, bb2);
		Node* bbb = new Node("bbb.txt", false, bb1);
		root_->leftmostChild_ = a;
		b->leftmostChild_ = bb1;
		bb1->leftmostChild_ = bbb;
		e->leftmostChild_ = ee;
	}
	else if (testinput == "2") {
		Node* h = new Node("h"    , true , root_);
		Node* g = new Node("g.txt", false, root_, nullptr, h);
		Node* f = new Node("f"    , true , root_, nullptr, g);
		Node* e = new Node("e.txt", false, root_, nullptr, f);
		Node* d = new Node("d"    , true , root_, nullptr, e);
		Node* c = new Node("c.txt", false, root_, nullptr, d);
		Node* b = new Node("b"    , true , root_, nullptr, c);
		Node* a = new Node("a.txt", false, root_, nullptr, b);
		root_->leftmostChild_ = a;
	}
	else if (testinput == "3") {
		Node* c0 = new Node("c0", true, root_);
		Node* b0 = new Node("b0", true, root_, nullptr, c0);
		Node* a0 = new Node("a0", true, root_, nullptr, b0);
		Node* c1 = new Node("c1", true, a0);
		Node* b1 = new Node("b1", true, a0, nullptr, c1);
		Node* a1 = new Node("a1", true, a0, nullptr, b1);
		Node* c2 = new Node("c2", true, b0);
		Node* b2 = new Node("b2", true, b0, nullptr, c2);
		Node* a2 = new Node("a2", true, b0, nullptr, b2);
		Node* c3 = new Node("c3", true, c0);
		Node* b3 = new Node("b3", true, c0, nullptr, c3);
		Node* a3 = new Node("a3", true, c0, nullptr, b3);
		Node* c4 = new Node("c4", true, a1);
		Node* b4 = new Node("b4", true, a1, nullptr, c4);
		Node* a4 = new Node("a4", true, a1, nullptr, b4);
		root_->leftmostChild_ = a0;
		a0->leftmostChild_ = a1;
		b0->leftmostChild_ = a2;
		c0->leftmostChild_ = a3;
		a1->leftmostChild_ = a4;
	}
}

FileSystem::~FileSystem() {
	// IMPLEMENT ME
    root_->clearChildren(root_);
}

void FileSystem::traverseAndClear(Node currentRoot)
{
    //start at root

    //if current nodes rightsibling_ is a dir recurse

    //remove if root_ clearChildren method works!!!!!!!
}

string FileSystem::cd(const string& path) {
	// IMPLEMENT ME
    if (path == "..")
    {
        if (curr_ == root_)
        {
            return "invalid path";
        }
        curr_ = curr_->parent_;
    }
    else if (path == "/")
    {
        curr_ = root_;
    }
    else if (curr_->containsRequestedDir(path) != nullptr)
    {
        if (curr_->isDir_)
        {
            curr_ = curr_->containsRequestedDir(path);//inneficient use of cpu time
        }
        else
        {
            return "invalid path";
        }
    }
    else
    {
        return "invalid path";
    }
    return ""; // dummy
}

// This is done for you as an example
string FileSystem::ls() const {

	string res;

	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		res += tmp->name_;
		if (tmp->isDir_) res += "/\n";
		else res += "\n";
		tmp = tmp->rightSibling_;
	}
	if (res != "") res.pop_back(); // remove extra \n

	return res;
}

string FileSystem::pwd() const {
	// IMPLEMENT ME
    Node* currentNode = root_;
    string buildString = "";
    while (currentNode != curr_)
    {
        buildString += "/" + currentNode->name_;
    }
    buildString += curr_->name_;
    currentNode = nullptr;
    return buildString; // dummy
}

string FileSystem::tree() const {
	// IMPLEMENT ME
    Node* temp = curr_->leftmostChild_;
    Node* tempDir = curr_;
    int offset = 0;
    string buildString = "";
    while (temp->rightSibling_ != nullptr && tempDir == curr_)
    {
        if (temp->isDir_)
        {
            tempDir = temp;
            buildString += temp->name_ + "/" + "\n";
            temp = tempDir->leftmostChild_;
        }
        else
        {
            buildString += addOffset(offset) + temp->name_;
            if (temp->rightSibling_ == nullptr)
            {
                temp = tempDir;
                tempDir = tempDir->parent_;
            }
        }
    }

    return buildString; // dummy
}

string FileSystem::addOffset(int offset) const
{
    string buildString = "";
    for (int i = 0; i < offset; i++)
    {
        buildString += " ";
    }
    return buildString;
}

string FileSystem::touch(const string& name)
{
    // IMPLEMENT ME
    if (curr_->containsRequestedDir(name) != nullptr)
    {
        return "file/directory already exists";
    }
    Node* newNode = new Node(name, false, curr_);
    Node* currentNode = curr_->leftmostChild_;
    if (currentNode == nullptr)
    {
        curr_->leftmostChild_ = newNode;
    }
    else
    {
         while (currentNode->rightSibling_ != nullptr)
        {
            currentNode = currentNode->rightSibling_;
        }
        currentNode->rightSibling_ = newNode;
    }
    currentNode = nullptr;
    return ""; // dummy
}

string FileSystem::mkdir(const string& name) {
	// IMPLEMENT ME
    if (curr_->containsRequestedDir(name) != nullptr)
    {
        if ((curr_->containsRequestedDir(name))->isDir_)
        {
            return "file/directory already exists";
        }
    }
     Node* newDir = new Node(name, true, curr_);
    if (curr_->leftmostChild_ == nullptr)
    {
        curr_->leftmostChild_ = newDir;
        newDir = nullptr;
    }
    else
    {
        Node* currentNode = curr_->leftmostChild_;
        while (currentNode->rightSibling_ != nullptr)
        {
            currentNode = currentNode->rightSibling_;
        }
        currentNode->rightSibling_ = newDir;
        currentNode = nullptr;
        newDir = nullptr;
    }
    return ""; // dummy
}

string FileSystem::rm(const string& name) {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::rmdir(const string& name) {
	// IMPLEMENT ME

	return ""; // dummy
}

string FileSystem::mv(const string& src, const string& dest) {
	// IMPLEMENT ME

	return ""; // dummy
}
