/* 
 * File:   Directory.cpp
 * Author: Kendrick Campbell
 *
 * Created on November 1, 2023, 9:59 PM
 */

#include "Directory.h"
#include <algorithm>

class INode;
using namespace std;

int totalMEM = 1048576;
int freeMem = totalMEM;

// Creates the root directory Node
DirectoryNode::DirectoryNode(string name) {
    this->dName = name;
    this->parent = nullptr;
    this->children = vector<DirectoryNode*>();
}

// Creates a Directory Node
DirectoryNode::DirectoryNode(string name, bool isFile, int pBits, int setUid, int setGid) {
    // DNode setup
    this->dName = name;
    this->isFile = isFile;
    this->parent = nullptr;
    this->children = vector<DirectoryNode*>();
    this->isLink = false;

    // Converts the bool var to string for iNode constructor
    string fileType;
    if (isFile) {
        fileType = "file";
    } else {
        fileType = "folder";
    }

    // Creates INode and assigns it to the iNodeptr for this dNode
    this->iNodeptr = new INode(fileType, pBits, setUid, setGid);
}

// Deletes dNode, its iNode, and then datablock (if it has one, from deleteINode)
void DirectoryNode::deleteDirectoryNode(DirectoryNode* dNode) {
    INode* deleteINode(dNode->iNodeptr);
    
    // If there is children, recursively deletes them
    if (!children.empty()) {
        for (auto child : dNode->children) {
            deleteDirectoryNode(child);
        }
   
        // removes the node from the parent's child vector
        if (dNode->parent) {
        dNode->parent->children.erase(
            remove_if(dNode->parent->children.begin(),
            dNode->parent->children.end(),
            [dNode](DirectoryNode* node) {return node == dNode; }
            ), 
            dNode->parent->children.end()
            );
        }
    }
    // finally deletes the node itself
    delete dNode;
}

// Returns the name of node given
string DirectoryNode::getName() {
    return this->dName;
}

// tells if node is a file or folder
bool DirectoryNode::isItFile() const {
    return this->isFile;
}

// returns the associated iNode
INode* DirectoryNode::getInode() {
    return this->iNodeptr;
}

// sets inode. helper for linking
void DirectoryNode::setINode(INode* iNode) {
    if (this->iNodeptr != nullptr) {
        INode* deleteINode(this->iNodeptr);
    }
    this->iNodeptr = iNode;
}

// returns parent
DirectoryNode*& DirectoryNode::getParent() {
    return this->parent;
}

// returns the vector of children
vector<DirectoryNode*> DirectoryNode::getChildren() {
    return this->children;
}

// returns link status.
bool DirectoryNode::isItLink() const {
    return this->isLink;
}

// Constructor for directory itself
Directory::Directory() {
    this->root = new DirectoryNode("", false, 777, 0, 0);
    //this->dataListptr = new DataList();
    this->root->getChildren() = vector<DirectoryNode*>();
}

// Travels to node and returns the dNode.
DirectoryNode* Directory::travelTo(string path) const {
    // setup for loop
    DirectoryNode* rc = root;
    DirectoryNode* currDir = root;
    stringstream stream(path);
    string directory;
    cerr << "entered travelTo for" << path << endl;

    // Loops until it finds name, if not sets rc to null
    if (path != "/" && path != "") {
	cerr << "path not root true" << endl;
    while (getline(stream, directory, '/')) {
        bool found = false;
	cerr << directory << endl;
	cerr << "Currently getting line \n";
        vector<DirectoryNode*> children = currDir->getChildren();
	cerr << "example children: " << children[0]->getName() << endl;
        // loops through every child of currDir
        for (int i = 0; i < children.size(); i++) {
	cerr << "entered for loop" << endl;
            if (children.at(i)->getName() == directory) {
		cerr << "target child found " << children.at(i)->getName() << endl;
                rc = children.at(i);
                found = true;
                break;
            }
	cerr << "current child: " << children.at(i)->getName() << endl;
        }

        // If not found, returns null. Handle this error if so.
        if (!found) {
	cerr << "child not found" << endl;
            rc = nullptr;
            break;
        }
    }
    }
    return rc;
}
/**
// Travels to node and returns the dNode.
DirectoryNode* Directory::travelTo(string path) const {
    // setup for loop
    // will output root
    DirectoryNode* rc = root;
    DirectoryNode* currDir = root;
    stringstream stream(path);
    string directory;
    
    if (path != "/" && path != "") {
        // handle case where path is the root.
        // Loops until it finds name, if not sets rc to null
        while (getline(stream, directory, '/')) {
            bool found = false;
            vector<DirectoryNode*> children = currDir->getChildren();
            // loops through every child of currDir
            for (DirectoryNode* child : children) {
                if (child->getName() == directory) {
                    rc = child;
                    found = true;
                    break;
                }
            }

            // If not found, returns null. Handle this error if so.
            if (!found) {
                rc = nullptr;
                break;
            }
        }
    }
    return rc;
}
**/

// adds node into directory
bool Directory::addDNode(string path, string nodeName, bool isFile, int pBits, int setUid, int setGid) {
    bool rc = false; 

    cerr << "Adding node at " << path << endl;
cerr << "new node name is: " << nodeName << endl;

    // finds node of given path
    DirectoryNode* targetDir = travelTo(path);
cerr << "TT completed" << endl;
    // check if dir exists and if it is a folder.
    if (targetDir != nullptr && targetDir->isItFile() == false) {
cerr << "add loop entered" << endl;
        DirectoryNode* newNode = new DirectoryNode(nodeName, isFile, pBits, setUid, setGid);
        newNode->getParent() = targetDir;
cerr << " new parent: " << newNode->getParent()->getName() << endl;
	vector<DirectoryNode*> childv = targetDir->getChildren();
        childv.push_back(newNode);
	targetDir->getChildren() = childv;
	rc = true;
cerr << "children addition completed: " << childv[0]->getName()<< endl;
cerr << getPathString(newNode) << endl;
    }
cerr << "rc value: " << rc << endl;
    return rc;
}
/**
// adds node into directory
bool Directory::addDNode(string path, string nodeName, bool isFile, int pBits, int setUid, int setGid) {
    bool rc = false; 
    // finds node of given path
    DirectoryNode* targetDir = travelTo(path);
    // check if dir exists and if it is a folder.
    if (targetDir != nullptr && targetDir->isItFile() == false) {
        DirectoryNode* newNode = new DirectoryNode(nodeName, isFile, pBits, setUid, setGid);
        newNode->getParent() = targetDir;
        targetDir->getChildren().push_back(newNode);
        rc = true;
    }
    return rc;
}
**/

// removes the node from directory
bool Directory::removeDNode(string path, string nodeName) {
    bool rc = false;
    //convert path to node
    DirectoryNode* targetDir = travelTo(path);
    if (targetDir) {
        
        for (auto child : targetDir->getChildren()) {
            if(child->getName() == nodeName) {
                DirectoryNode* deleteDirectoryNode(child);
                DirectoryNode* parent = targetDir->getParent();
                //auto it = std::find(targetDir->getChildren().begin(), targetDir->getChildren().end(), child);
                //if (it != targetDir->getChildren().end()) {
                    //targetDir->getChildren().erase(it); // Removing the node from the parent's children vector
                //}
                rc = true;
                break;
            }
        }
    }
    return rc;
}

string Directory::getPathString(DirectoryNode* dNode) const {
    DirectoryNode* currDN = dNode;
    string temp, currName, path = "";
    bool firstLoop = true;

    while (true) {
	if (currDN->getParent()->getName() != "/") {
	    currName = currDN->getName();
	    currDN = dNode->getParent();
	    temp = path;
	    path = currName;
	    path = path + "/" + temp;
	    temp = "";
	    cerr << "The current path is " << path << endl;
	} else {
	    currName = currDN->getName();
	    if (firstLoop) {
		path = "/" + currName;
		break;
	    } else {
	        temp = path;
	        path = "/" + currName + "/" + temp;
	        temp = "";
	        break;
	    }
	}
	bool firstLoop = false;
    }
    return path;
}
/**
string Directory::getPathString(DirectoryNode* dNode) const {
    vector<string> sections;
    string path;
    while (dNode != nullptr) {
        sections.insert(sections.begin(), dNode->getName());
        dNode = dNode->getParent();
    }

    for (string& part : sections) {
        path += "/" + part;
    }
    return path.empty() ? "/" : path;
}
 */

bool Directory::createLink(string toBeLinkedToPath, string newPath) {
    bool rc = false;
    // If input is invalid, outputs false
    if (!toBeLinkedToPath.empty() || !newPath.empty()) {
        
        // Find node of old path
        DirectoryNode* toBeLinkedToNode = travelTo(toBeLinkedToPath);
        // check that oldpath exists.
        if (toBeLinkedToNode) {
            // extract name from new path
            string newName = newPath.substr(newPath.find_last_of('/') + 1);
            
            // find the parent node that the new node will be a child of
            string parentPath = newPath.substr(0, newPath.find_last_of('/'));
            DirectoryNode* parent = travelTo(parentPath);
            
            // check to make sure a parent is found
            if (parent) {
                // Creates the new node
                DirectoryNode* newLinkNode = new DirectoryNode(newName, toBeLinkedToNode->isItFile(), 0, 0, 0);
                // replaces the new iNode with the oldPath's iNode.
                toBeLinkedToNode->getInode()->update_Atime();
                newLinkNode->setINode(toBeLinkedToNode->getInode());
                // updates that the node is a link type
                newLinkNode->setLinkStatus(true);
                // assigns new node as the parent's child.
                parent->getChildren().push_back(newLinkNode);
                rc = true;
            }
        }
    }
    return rc;
}

bool Directory::deleteLink(string path) {
    bool rc = false;
    if (!path.empty()) {
        // find node
        DirectoryNode* node = travelTo(path);
        // redundant, i know, but it works
        node->getInode()->sub_nLink(node->getInode());
        // check if node and its parent exists
        if (node && node->getParent()) {
            DirectoryNode* parent = node->getParent();
            // search for the correct child node
            for (auto child : parent->getChildren()) {
                if (child->getName() == node->getName()) {
                    removeDNode(Directory::getPathString(parent), node->getName());
                    rc = true;
                }
            }
        }
    }
    return rc;
}

void DirectoryNode::setLinkStatus(bool status) {
    this->isLink = status;
}

//DataList* Directory::getDataListptr() {
  //  return this->dataListptr;
//}

string DirectoryNode::readFile() {
    this->iNodeptr->update_Atime();
    return this->iNodeptr->get_addr(iNodeptr)->getContent();
}

void DirectoryNode::writeFile(string input) {
    this->iNodeptr->update_Atime();
    this->iNodeptr->update_Mtime();   
    this->iNodeptr->get_addr(iNodeptr)->getContent() += input;
}