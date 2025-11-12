#include "FileSystem.h"

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling)
{
	// IMPLEMENT ME
    name_ = name;
    isDir_ = isDir;
    parent_ = parent;
    leftmostChild_ = leftmostChild;
    rightSibling_ = rightSibling;
}

Node::~Node()
{
    //destroy children
    if (isDir_ && leftmostChild_ != nullptr)
    {
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

    parent_ = nullptr;
    rightSibling_ = nullptr;
    leftmostChild_ = nullptr;

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

Node* Node::contains(string reqName)
{
    Node* currentNode = leftmostChild_;
    if(currentNode != nullptr){
        while (currentNode->rightSibling_ != nullptr)
        {
            if (currentNode->name_ == reqName)
            {
                return currentNode;
            }
            currentNode = currentNode->rightSibling_;
        }
        if(currentNode->name_ == reqName){
            return currentNode;
        }
    }   
    return nullptr;
}

bool Node::compareOrder(string checkName, int orderIndex)
{
    bool isGreater = false;
    bool checkCase1 = checkName[orderIndex] == toupper(checkName[orderIndex]);
    bool checkCase2 = name_[orderIndex] == toupper(name_[orderIndex]);
    //check if they are of the same case
    if(checkCase1 == checkCase2){
        //check if they are the same character
        if(checkName[orderIndex] == name_[orderIndex]){
            //check which string stops first
            if(checkName.length() < orderIndex){
                return true;
            }
            if(name_.length() < orderIndex){
                return false;
            }
            //recurse to check next character
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

//This works for absolute paths
string FileSystem::cd(const string& path){
    //checks that the path isnt empty
    if (path != ""){
        string subPath = "";
        //go thorugh each character in the path, build subPath until '/' is reached
        for(int i = 0; i < path.length(); i++){
            if(path[i] == '/'){
                if(i == 0){
                    curr_ = root_;
                }
                else{
                    if(subPath == ".."){
                        if(curr_ != root_){
                            curr_ = curr_->parent_;
                            subPath = "";
                        }
                        else{
                            return "invalid path";
                        }
                    }
                    else{
                        Node* tmp = curr_->contains(subPath);
                        //sets the curr_ to tmp if it is valid
                        if(tmp != nullptr){
                            if(tmp->isDir_){
                                curr_ = tmp;
                                subPath = "";
                            }
                            else{
                                return "invalid path";
                            }
                        }
                        else{
                            return "invalid path";
                        }
                        tmp = nullptr;
                    }
                    
                    
                }
            }
            else{
                //build subPath string
                subPath += path[i];
            }
        }
        //deals with the final directory in the path
        if(subPath != ""){
            if(subPath == ".."){
                if(curr_ != root_){
                    curr_ = curr_->parent_;
                    subPath = "";
                }
                else{
                    return "invalid path";
                }
            }
            else{
                if(curr_->contains(subPath) != nullptr){
                    if(curr_->contains(subPath) -> isDir_){
                        curr_ = curr_->contains(subPath);
                        subPath = "";
                    }
                    else{
                        return "invalid path";
                    }
                }
                else{
                    return "invalid path";
                }
            }
        }
    }
    return "";
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
    //calling in order to use recursion
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
    if (curr_->contains(name) != nullptr)
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
            //inserts the new file into the correct order within the directory
            while (newDir->compareOrder(currentNode->name_, 0) == true && currentNode->rightSibling_ != nullptr)
            {
                currentNode = currentNode->rightSibling_;
            }
            if (newDir->compareOrder(currentNode->name_, 0) == false)
            {
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
    if (curr_->contains(name) != nullptr)
    {
        if ((curr_->contains(name))->isDir_)
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
            //sets the new directory in its ordered position in the current dir
            while (newDir->compareOrder(currentNode->name_, 0) == true && currentNode->rightSibling_ != nullptr)
            {
                currentNode = currentNode->rightSibling_;
            }
            if (newDir->compareOrder(currentNode->name_, 0) == false)
            {
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
    Node* rmNode = curr_->contains(name);
    if (rmNode == nullptr)
    {
        return "file not found";
    }
    else if (rmNode->isDir_)
    {
        return "not a file";
    }
    delete rmNode;
    rmNode = nullptr;
    return ""; // dummy
}

string FileSystem::rmdir(const string& name) {
    // IMPLEMENT ME
    Node* rmDirNode = curr_->contains(name);
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
    delete rmDirNode;
    rmDirNode = nullptr;
    return ""; // dummy
}

string FileSystem::mv(const string& src, const string& dest){
    int mode = -1; // used to show whether src is being moved or renamed: 0 = move, 1 = rename, 2 = parent dir move
    if(src == dest){
        return "source and destination are the same";
    }
    //check if source exists
    if(curr_->contains(src) == nullptr){
        return "source does not exist";
    }
    else{
        //find whether assigning new name to source or moving to destination
        //error checking
        Node* destNode = curr_->contains(dest);
        Node* srcNode = curr_->contains(src);
        //check whether the destination exists in curr_
        if(destNode != nullptr){
            //check if dest is a file or dir
            if(destNode->isDir_ == true){
                if(destNode->contains(src) != nullptr){
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
                    if(destNode->contains(src) != nullptr){
                        return "destination already has file/directory of same name";
                    }
                }
                else{
                    return "invalid path";
                }
            }
            else{
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
                    //shouldnt ever encounter this issue as destnode must be a directory within curr_
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
                //find the node that the srcNode will be inserted before, or after if no node is of greater priority that src node
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
        }
        else if(mode == 1){
            //dereference from current dir
            if(curr_->leftmostChild_ == srcNode){
                if(srcNode->rightSibling_ != nullptr){
                    curr_->leftmostChild_ = srcNode->rightSibling_;
                }
                else{
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
                //find the node that the srcNode will be inserted before, or after if no node is of greater priority that src node
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
        }
    }
    return "";
}