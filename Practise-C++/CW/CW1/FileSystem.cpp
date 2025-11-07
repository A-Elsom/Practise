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
    //std::cout<<name_<<" : starting Delete \n";
    if (isDir_ && leftmostChild_ != nullptr)
    {
        //std::cout<<name_<<" : deleting driectory children\n";
        clearChildren(leftmostChild_);
    }
    if(parent_ != nullptr){//check if deleting root
        if (parent_->leftmostChild_ == this)
        {
            parent_->leftmostChild_ = rightSibling_;
        }
        else
        {
            leftSibling()->rightSibling_ = rightSibling_;
        }
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
    if(parent_ != nullptr){
        parent_ = nullptr;
    }
    if(rightSibling_ != nullptr){
        rightSibling_ = nullptr;
    }
    
    leftmostChild_ = nullptr;
    
    //std::cout<<"deleteComplete\n";
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
    tmp = nullptr;
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
    if(currentNode != nullptr){
        while (currentNode->rightSibling_ != nullptr)
        {
            if (currentNode->name_ == reqDir)
            {
                return currentNode;
            }
            currentNode = currentNode->rightSibling_;
        }
        if(currentNode->name_ == reqDir){
            return currentNode;
        }
    }   
    return nullptr;
}

bool Node::compareOrder(string checkName, int orderIndex)
{
    //check if they are of the same case
    bool isGreater = false;
    bool checkCase1 = checkName[orderIndex] == toupper(checkName[orderIndex]);
    bool checkCase2 = name_[orderIndex] == toupper(name_[orderIndex]);
    if(checkCase1 == checkCase2){
        if(checkName[orderIndex] == name_[orderIndex]){
            if(checkName.length() < orderIndex){
                return true;
            }
            if(name_.length() < orderIndex){
                return false;
            }
            isGreater = compareOrder(checkName, orderIndex + 1);
        }
        else if(checkName[orderIndex] > name_[orderIndex]){
            isGreater = false;
        }
        else{
            isGreater = true;
        }
    }
    else if(checkCase1 == true && checkCase2 == false){
        isGreater = true;
    }
    else if(checkCase1 == false && checkCase2 == true){
        isGreater = false;
    }
    else{
        isGreater = false;
    }
    return isGreater;
    //check if checkName is greater than name_ return false
    //otherwise name_ must be greater return true


    /*
    //bool isGreater = false;
    std::cout << "checking order";
    if(name_.compare(checkName) == 0){
        return true;
    }
    else if(name_.compare(checkName) > 0){
        return true;
    }
    else{
        return false;
    }
    
    char convCharThis = toupper(static_cast<char>(name_.at(orderIndex)));
    char convCharCheck = toupper(static_cast<char>(checkName.at(orderIndex)));

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
    */
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
    curr_ = root_ = new Node("", true);
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
    delete root_;
    root_ = nullptr;
    curr_ = nullptr;
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
        if (curr_->containsRequestedDir(path)->isDir_)
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
     Node* newDir = new Node(name, false, curr_);
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
            /*
            if (currentNode->rightSibling_ == nullptr)
            {
                //newDir->rightSibling_ = currentNode->rightSibling_;
                currentNode->rightSibling_
            }
                */
            if (newDir->compareOrder(currentNode->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newDir;
                if(currentNode == curr_->leftmostChild_){
                    curr_->leftmostChild_ = newDir;
                }else{
                    currentNode->leftSibling()->rightSibling_ = newDir;
                }
                
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
            /*
            if (currentNode->rightSibling_ == nullptr)
            {
                //newDir->rightSibling_ = currentNode->rightSibling_;
                currentNode->rightSibling_
            }
                */
            if (newDir->compareOrder(currentNode->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newDir;
                if(currentNode == curr_->leftmostChild_){
                    curr_->leftmostChild_ = newDir;
                }else{
                    currentNode->leftSibling()->rightSibling_ = newDir;
                }
                
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
    if(rmDirNode->leftmostChild_ != nullptr){
        return "directory not empty";
    }
    rmDirNode->~Node();
    rmDirNode = nullptr;
    return ""; // dummy
}

string FileSystem::mv(const string& src, const string& dest){
    int mode = -1; // used to show whether src is being moved or renamed: 0 = move, 1 = rename, 2 = parent dir move
    if(src == dest){
        return "source and destination are the same";
    }
    //check if source exists
    if(curr_->containsRequestedDir(src) == nullptr){
        return "source does not exist";
    }
    else{
        //find whether assigning new name to source or moving to destination
        //error checking
        Node* destNode = curr_->containsRequestedDir(dest);
        Node* srcNode = curr_->containsRequestedDir(src);
        //check whether the destination exists in curr_
        if(destNode != nullptr){
            //check if dest is a file or dir
            if(destNode->isDir_ == true){
                if(destNode->containsRequestedDir(src) != nullptr){
                    return "destination already has file/directory of same name";
                }
                else{
                    mode = 0;
                }
            }
            else{
                if(srcNode->isDir_ == true){
                    //cannot rename as directory would be renaming to a file type
                    return "source is a directory but destination is an existing file";
                }
                else{
                    return "destination already has file of same name";
                }
                //return "";
            }
        }
        else{
            //check if user wants to mv to parent folder
            if(dest == ".."){
                if(curr_ != root_){
                    mode = 0;
                    destNode = curr_->parent_;
                    if(destNode->containsRequestedDir(src) != nullptr){
                        return "destination already has file/directory of same name";
                    }
                }
                else{
                    return "invalid path";
                }
            }
            else{
                //rename file
                mode = 1;
            }
            
            
        }
        //move or rename src to dest
        if(mode == 0){
            //move to dest
            
            //dereference from existing directory
            if(curr_->leftmostChild_ == srcNode){
                if(srcNode->rightSibling_ != nullptr){
                    curr_->leftmostChild_ = srcNode->rightSibling_;
                }
                else{
                    //shouldnt every encounter this issue as destnode must be a directory within curr_
                    curr_->leftmostChild_ = nullptr;
                }
            }
            else{
                //set left sibling to point to srcNode's rightsib
                if(srcNode->rightSibling_ != nullptr){
                    srcNode->leftSibling()->rightSibling_ = srcNode->rightSibling_;
                }
                else{
                    srcNode->leftSibling()->rightSibling_ = nullptr;
                }
            }
            //check if destNode has any children
            if(destNode->leftmostChild_ == nullptr){
                destNode->leftmostChild_ = srcNode;
                srcNode->rightSibling_ = nullptr;
                srcNode->parent_ = destNode;
            }
            else{
                // insert in order
                srcNode->parent_ = destNode;
                Node* tempNode = destNode->leftmostChild_;
                while(tempNode->rightSibling_ != nullptr && srcNode->compareOrder(tempNode->name_,0) == true){
                    tempNode = tempNode->rightSibling_;
                }

                //check which condition failed
                if(tempNode->rightSibling_ == nullptr){
                    if(srcNode->compareOrder(tempNode->name_,0) == false){
                        if(tempNode == destNode->leftmostChild_){
                            destNode->leftmostChild_ = srcNode;
                        }
                        else{
                            tempNode->leftSibling()->rightSibling_ = srcNode;
                        }
                        srcNode->rightSibling_ = tempNode;
                    }
                    else{
                        tempNode->rightSibling_ = srcNode;    
                        srcNode->rightSibling_ = nullptr; 
                    }
                }
                else{
                    if(destNode->leftmostChild_ == tempNode){
                        destNode->leftmostChild_ = srcNode;
                    }
                    else{
                        tempNode->leftSibling()->rightSibling_ = srcNode;
                    }
                    srcNode->rightSibling_ = tempNode;
                }
            }
            //return "";
        }
        else if(mode == 1){
            //dereference from current dir
            if(curr_->leftmostChild_ == srcNode){
                if(srcNode->rightSibling_ != nullptr){
                    curr_->leftmostChild_ = srcNode->rightSibling_;
                }
                else{
                    //shouldnt every encounter this issue as destnode must be a directory within curr_
                    curr_->leftmostChild_ = nullptr;
                }
            }
            else{
                //set left sibling to point to srcNode's rightsib
                if(srcNode->rightSibling_ != nullptr){
                    srcNode->leftSibling()->rightSibling_ = srcNode->rightSibling_;
                }
                else{
                    srcNode->leftSibling()->rightSibling_ = nullptr;
                }
            }
            //rename to dest
            srcNode->name_ = dest;
            //sort back into curr_
            if(curr_->leftmostChild_ == nullptr){
                curr_->leftmostChild_ = srcNode;
                srcNode->rightSibling_ = nullptr;
            }
            else{
                // insert in order
                Node* tempNode = curr_->leftmostChild_;
                while(tempNode->rightSibling_ != nullptr && srcNode->compareOrder(tempNode->name_,0) == true){
                    tempNode = tempNode->rightSibling_;
                }

                //check which condition failed
                if(tempNode->rightSibling_ == nullptr){
                    
                    if(srcNode->compareOrder(tempNode->name_,0) == false){
                        
                        if(tempNode == curr_->leftmostChild_){
                            curr_->leftmostChild_ = srcNode;
                        }
                        else{
                            tempNode->leftSibling()->rightSibling_ = srcNode;
                        }
                        srcNode->rightSibling_ = tempNode;
                    }
                    else{
                        tempNode->rightSibling_ = srcNode;
                        srcNode->rightSibling_ = nullptr; 
                    }
                    
                }
                else{
                    if(tempNode == curr_->leftmostChild_){
                        
                        curr_->leftmostChild_ = srcNode;
                    }
                    else{
                        
                        tempNode->leftSibling()->rightSibling_ = srcNode;
                    }
                    
                    srcNode->rightSibling_ = tempNode;
                }
                tempNode = nullptr;
            }
            destNode = nullptr;
            srcNode = nullptr;
            //return "";
        }
    }
    return "";
}

/*
string FileSystem::mv(const string& src, const string& dest) {
    if(src == dest){
        return "source and destination are the same";
    }
    
    if(curr_->containsRequestedDir(src) == nullptr){
        return "source does not exist";
    }

    Node* srcNode = curr_->containsRequestedDir(src);
    Node* destNode = curr_->containsRequestedDir(dest);
    //std::cout<<destNode->name_;

    if(destNode != nullptr || dest == ".."){
        if(destNode != nullptr){
            if(destNode->isDir_ == false && srcNode->isDir_ == true){
                    return "source is a directory but destination is an existing file";
            }

            if(destNode->isDir_ == true){
                
                //move source to destination
                //check if it is the start of curr directory
                if(curr_->leftmostChild_ == srcNode){
                    if(srcNode->rightSibling_ != nullptr){
                        curr_->leftmostChild_ = srcNode->rightSibling_;
                    }
                    else{
                        curr_->leftmostChild_ = nullptr;
                    }
                }//check if final in curr directory
                else{
                    if(srcNode->rightSibling_ == nullptr){
                        srcNode->leftSibling()->rightSibling_ = nullptr;
                    }
                    else{
                        srcNode->leftSibling()->rightSibling_ = srcNode->rightSibling_;
                    }
                }
                //now move to destination directory
                srcNode->parent_ = destNode;
                //slot in alphabetically
                /*
                if(destNode->leftmostChild_ != nullptr){
                    
                    while(tmp->rightSibling_ != nullptr && srcNode->compareOrder(tmp->name_, 0) == true){
                        tmp = tmp->rightSibling_;
                    }
                    if(tmp->rightSibling_ == nullptr){
                        tmp->rightSibling_ = srcNode;
                        srcNode->rightSibling_ = nullptr;
                    }
                    else{
                        tmp->leftSibling()->rightSibling_ = srcNode;
                        srcNode->rightSibling_ = tmp;
                    }
                    tmp = nullptr;
                    srcNode = nullptr;
                    destNode = nullptr;
                    return "";
                }*/
               /*
                Node* tmp = destNode->leftmostChild_;
                while (srcNode->compareOrder(tmp->name_, 0) == true && tmp->rightSibling_ != nullptr)
                {
                    tmp = tmp->rightSibling_;
                }
                if (srcNode->compareOrder(tmp->name_, 0) == false)
                {
                    //curr_->leftmostChild_ = newDir;
                    if(tmp == curr_->leftmostChild_){
                        curr_->leftmostChild_ = srcNode;
                    }else{
                        tmp->leftSibling()->rightSibling_ = srcNode;
                    }
                    
                    srcNode->rightSibling_ = tmp;
                }
                else
                {
                    tmp->rightSibling_ = srcNode;
                }
            }
            else if(dest == ".."){
                if(curr_ != root_){
                    return "invalid path";
                }
                else{
                    destNode = curr_->parent_;
                    //move src to dest
                    //check if it is the start of curr directory
                    if(curr_->leftmostChild_ == srcNode){
                        if(srcNode->rightSibling_ != nullptr){
                            curr_->leftmostChild_ = srcNode->rightSibling_;
                        }
                        else{
                            curr_->leftmostChild_ = nullptr;
                        }
                    }//check if final in curr directory
                    else{
                        if(srcNode->rightSibling_ == nullptr){
                            srcNode->leftSibling()->rightSibling_ = nullptr;
                        }
                        else{
                            srcNode->leftSibling()->rightSibling_ = srcNode->rightSibling_;
                        }
                    }
                    //now move to destination directory
                    srcNode->parent_ = destNode;
                    //slot in alphabetically
                    if(destNode->leftmostChild_ != nullptr){
                        Node* tmp = destNode->leftmostChild_;
                        while(tmp->rightSibling_ != nullptr && srcNode->compareOrder(tmp->name_, 0) == false){
                            tmp = tmp->rightSibling_;
                        }
                        if(tmp->rightSibling_ == nullptr){
                            tmp->rightSibling_ = srcNode;
                            srcNode->rightSibling_ = nullptr;
                        }
                        else{
                            srcNode->rightSibling_ = tmp->rightSibling_;
                            tmp->rightSibling_ = srcNode;
                        }
                        tmp = nullptr;
                        srcNode = nullptr;
                        destNode = nullptr;
                        return "";
                    }
                }
            }
            else{
                return "destination already has file/directory of same name";
            }
        }
        
    }
    else{
        //rename source to dest
        //std::cout<<"changing name of file/ directory";
        srcNode->name_ = dest;
        
        if(srcNode->parent_->leftmostChild_ != nullptr){
            Node* tmp = srcNode->parent_->leftmostChild_;
            while (srcNode->compareOrder(tmp->name_, 0) == true && tmp->rightSibling_ != nullptr)
            {
                tmp = tmp->rightSibling_;
            }
            if (srcNode->compareOrder(tmp->name_, 0) == false)
            {
                //curr_->leftmostChild_ = newDir;
                if(tmp == curr_->leftmostChild_){
                    curr_->leftmostChild_ = srcNode;
                }else{
                    tmp->leftSibling()->rightSibling_ = srcNode;
                }
                
                srcNode->rightSibling_ = tmp;
            }
            else
            {
                tmp->rightSibling_ = srcNode;
            }
        }
        return "";
    }
    return "";

}*/