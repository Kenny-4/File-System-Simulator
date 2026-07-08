/* 
 * File:   Directory.h
 * Author: Kendrick Campbell
 *
 * Created on October 24, 2023, 12:01 AM
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "iNodes.h"

using namespace std;

extern int totalMEM;
extern int freeMem;

class DirectoryNode {
private:
    string dName; // Name of item in directory
    bool isFile; // True if file, false if folder
    DirectoryNode* parent; // Keeps track of parent folder
    vector<DirectoryNode*> children; // If folder, may have children if notempty
    INode* iNodeptr; // a pointer to it's iNode
    bool isLink; // check if node links to another node's iNode
    
public:
    DirectoryNode(string letter); // For the root node
    DirectoryNode(string name, bool isFile, int pBits, int setUid, int setGid); // for any other node
    void deleteDirectoryNode(DirectoryNode* dNode); // Deletes the item, calls iNode destruct. 
    string getName(); // gives name of file
    bool isItFile() const; // tells if item is file or folder
    DirectoryNode*& getParent(); // finds the parent
    INode* getInode(); // produces pointer to iNode
    void setINode(INode* iNode); // set an iNode for linking
    vector<DirectoryNode*> getChildren();
    bool isItLink() const; // returns the link status
    void setLinkStatus(bool status); // sets link indicator
    string readFile();
    void writeFile(string input);
    
};

class Directory {
public:
    //static DataList* dataListptr; // dataList associated with directory (for INodes constructor to work with)
    DirectoryNode* root; // Start of directory
    Directory(); // Directory constructor
    DirectoryNode* travelTo(string path) const; // use this to get the node indicated by path
    bool addDNode(string path, string nodeName, bool isFile, int pBits, int setUid, int setGid); // Adds the item to dir
    bool removeDNode(string currPath, string nodeName); // rem the item from dir
    string getPathString(DirectoryNode* dNode) const; // returns the path in string
    bool createLink(string toBeLinkedToPath, string newPath);
    bool deleteLink(string path); // deletes link of given path.
    //DataList* getDataListptr();
    
    
};

#endif /* DIRECTORY_H */

