#include "FileSystem.h"
#include <iostream>

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling)
{
	// IMPLEMENT ME
    name_ = name;
    isDir_ = isDir;
    parent_ = parent;
    leftmostChild_ = leftmostChild;
    rightSibling_ = rightSibling;
}

/*


Node::~Node()
{
    // IMPLEMENT ME
    if (isDir_)
    {
        clearChildren(this);
    }
    std::cout << "1";
    leftSibling()->rightSibling_ = rightSibling_;
    std::cout << "2";
    rightSibling_ = nullptr;
    leftmostChild_ = nullptr;
    parent_ = nullptr;
    std::cout << "3";
}
*/

Node::~Node()
{
    std::cout<<name_<<" : starting Delete \n";
    if (isDir_ && leftmostChild_ != nullptr)
    {
        std::cout<<name_<<" : deleting driectory children\n";
        clearChildren(leftmostChild_);
    }
    if(parent_->leftmostChild_ == this)
    {
        parent_->leftmostChild_ = rightSibling_;
    }
    else
    {
        leftSibling()->rightSibling_ = rightSibling_;
    }
    /*
    Node* parentCopy = parent_;
    Node* currentNode = parentCopy->leftmostChild_;
    while(currentNode->rightSibling_ != nullptr){
        std::cout<<currentNode->name_<< " -> ";
        currentNode = currentNode->rightSibling_;
    }
    std::cout<<currentNode->name_;
    */
    parent_ = nullptr;
    rightSibling_ = nullptr;
    leftmostChild_ = nullptr;
    
    std::cout<<"deleteComplete\n";
}

void Node::clearChildren(Node* currentNode)
{
    Node* tmp = currentNode;
    Node* tmp1 = tmp;
    while(tmp->rightSibling_ != nullptr)
    {
        tmp1 = tmp;
        tmp = tmp->rightSibling_;
        delete tmp1;
        
    }
    tmp1 = nullptr;
    delete tmp;

}

/*void clearChildren1(Node* currentNode)
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
        delete currentNode;
        return;
    }
}
*/
Node* Node::containsRequestedDir(string reqDir)
{
    Node* currentNode = leftmostChild_;
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

bool Node::compareOrder(string checkName, int orderIndex)
{
    bool isGreater = false;
    int convCharThis = tolower(static_cast<int>(name_[orderIndex]));
    int convCharCheck = tolower(static_cast<int>(checkName[orderIndex]));
    if (convCharCheck == convCharThis)
    {
        if (checkName.length() < orderIndex)
        {
            return true;
        }
        if (name_.length() < orderIndex)
        {
            return false;
        }
        isGreater = compareOrder(checkName, orderIndex + 1);
    }
    else
    {
        if (convCharCheck > convCharThis)
        {
            isGreater = false;
        }
        else
        {
            isGreater = true;
        }
    }
    return isGreater;

}

Node* Node::leftSibling() const
{
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
    root_ = new Node("", true);
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
    root_->~Node();
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
    Node* tempNode = curr_;
    
    while (currentNode != curr_)
    {
        if (currentNode != root_)
        {
             buildString += "/" + currentNode->name_;
        }
        while (tempNode->parent_ != currentNode)
        {
            tempNode = tempNode->parent_;
        }
        currentNode = tempNode;
        tempNode = curr_;
    }
    buildString += "/" + curr_->name_;
    currentNode = nullptr;
    return buildString; // dummy
}

string FileSystem::tree() const {
	// IMPLEMENT ME
    Node* temp = curr_->leftmostChild_;
    Node* tempDir = curr_;
    
    int offset = 0;
    string buildString = "";
    buildString += displayDirChildren(curr_, 0);

    return buildString; // dummy
}

string FileSystem::displayDirChildren(Node* currentDir, int offset) const
{
    if (!currentDir->isDir_)
    {
        return "requested directory is not a directory";
    }

    string createString = "";
    createString += addOffset(offset) + currentDir->name_ + "/";
    offset++;
    Node* currentNode = currentDir->leftmostChild_;

    while (currentNode != nullptr)
    {
        
        if (currentNode->isDir_)
        {
            createString += "\n" + displayDirChildren(currentNode, offset);
        }
        else
        {
            createString += "\n" + addOffset(offset) + currentNode->name_;
        }
        
        currentNode = currentNode->rightSibling_;
    }

    currentNode = nullptr;
    return createString;
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
        newNode = nullptr;
    }
    else
    {
        if (currentNode->rightSibling_ == nullptr)
        {
            if (newNode->compareOrder(currentNode->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newNode; !!dont understand why this is here
                newNode->rightSibling_ = currentNode;
            }
            else
            {
                currentNode->rightSibling_ = newNode;
            }
        }
        else
        {
            while (newNode->compareOrder(currentNode->name_, 0) == true && currentNode->rightSibling_ != nullptr)
            {
                currentNode = currentNode->rightSibling_;
            }
            if (currentNode->rightSibling_ != nullptr)
            {
                newNode->rightSibling_ = currentNode->rightSibling_;
            }
            if (newNode->compareOrder(currentNode->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newNode; !!again dont understand why i put this here
                currentNode->leftSibling()->rightSibling_ = newNode;
                newNode->rightSibling_ = currentNode;
            }
            else
            {
                newNode->rightSibling_ = currentNode->rightSibling_;
                currentNode->rightSibling_ = newNode;
            }
        }
    }
    currentNode = nullptr;
    newNode = nullptr;
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
        if (currentNode->rightSibling_ == nullptr)
        {
            if (newDir->compareOrder(currentNode->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newDir;
                newDir->rightSibling_ = currentNode;
            }
            else
            {
                currentNode->rightSibling_ = newDir;
            }
        }
        else
        {
            while (newDir->compareOrder(currentNode->name_, 0) == true && currentNode->rightSibling_ != nullptr)
            {
                currentNode = currentNode->rightSibling_;
            }
            if (currentNode->rightSibling_ != nullptr)
            {
                newDir->rightSibling_ = currentNode->rightSibling_;
            }
            if (newDir->compareOrder(currentNode->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newDir;
                currentNode->leftSibling()->rightSibling_ = newDir;
                newDir->rightSibling_ = currentNode;
            }
            else
            {
                currentNode->rightSibling_ = newDir;
            }
        }
    }
    return ""; // dummy
}

string FileSystem::rm(const string& name) {
    // IMPLEMENT ME
    Node* rmNode = curr_->containsRequestedDir(name);
    if (rmNode == nullptr)
    {
        return "file not found";
    }
    else if (rmNode->isDir_)
    {
        return "not a file";
    }
    delete rmNode;
    //rmNode = nullptr;
    return ""; // dummy
}

string FileSystem::rmdir(const string& name) {
    // IMPLEMENT ME
    Node* rmDirNode = curr_->containsRequestedDir(name);
    if (rmDirNode == nullptr)
    {
        return "directory not found";
    }
    else if(!rmDirNode->isDir_)
    {
        return "not a directory";
    }
    rmDirNode->~Node();
    rmDirNode = nullptr;
    return ""; // dummy
}

string FileSystem::mv(const string& src, const string& dest) {
    // IMPLEMENT ME
    if (src == dest)
    {
        return "source and destination are the same";
    }
    if (!curr_->containsRequestedDir(src))
    {
        return "source does not exist";
    }
    Node* srcNode = curr_->containsRequestedDir(src);
    if (!curr_->containsRequestedDir(dest) && dest != "..")
    {
        srcNode->name_ = dest;
    }
    else if (curr_->containsRequestedDir(dest))
    {
        if (!curr_->containsRequestedDir(dest)->isDir_ && srcNode->isDir_)
        {
            return "source is a directory but destination is an existing file";
        }
        return "destination already has a file of same name";
    }

    Node* destNode = nullptr;

    if (dest == "..")
    {
        if (curr_ != root_)
        {
            destNode = curr_->parent_;
        }
        else
        {
            return "invalid path";
        }
    }
    else
    {
        destNode = curr_->containsRequestedDir(dest);
    }

    if (destNode->isDir_)
    {
        if (destNode->containsRequestedDir(src))
        {
            return "destination already has file/directory of same name";
        }
        if (curr_->leftmostChild_ == srcNode)
        {
            curr_->leftmostChild_ = srcNode->rightSibling_;
        }
        if (destNode->leftmostChild_ == nullptr)
        {
            destNode->leftmostChild_ = srcNode;
            srcNode->parent_ = destNode;
            srcNode->rightSibling_ = nullptr;
        }
        else
        {
            Node* tempNode = destNode->leftmostChild_;
            srcNode->parent_ = destNode;
            while (srcNode->compareOrder(tempNode->name_, 0) && tempNode->rightSibling_ != nullptr)
            {
                tempNode = tempNode->rightSibling_;
            }
            if (tempNode->rightSibling_ != nullptr)
            {
                srcNode->rightSibling_ = tempNode->rightSibling_;
            }
            else
            {
                srcNode->rightSibling_ = nullptr;
            }
            tempNode->rightSibling_ = srcNode;
            tempNode = nullptr;
        }
    }
    else
    {
        return "destination is not a directory";
    }
    return ""; // dummy
}
