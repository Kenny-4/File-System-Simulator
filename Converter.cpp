 /* 
 * File:   Converter.cpp
 * Author: Kendrick Campbell
 *
 * Created on November 5, 2023, 2:08 PM
 */

#include <iostream>
#include <stack>
#include <vector>

#include "Converter.h"

// may or may not be useful?
int OffsetConverter::convertToOffset(void* ptr) {
    int rc;
    if (ptrTo_OffsetMap.find(ptr) != ptrTo_OffsetMap.end()) {
        // in case the ptr already is in the map.
        rc = ptrTo_OffsetMap[ptr];
    } else {
        // converts the ptr to offset, inserts into map.
        ptrTo_OffsetMap[ptr] = currOffset;
        currOffset += sizeof(*ptr);
        rc = ptrTo_OffsetMap[ptr];
    }
    return rc;
};

// serialize through whole list
void OffsetConverter::serializeToFile(string& filename, Directory* dir) {
    stack<DirectoryNode*> nodeStack; // stack of nodes to be processed
    vector<DirectoryNode*> visitedNodes; // tracks nodes that have been visited
    nodeStack.push(dir->root); // start at root
    
    // serialize the dir
    
    // loops through nodes till all have been visited
    while (!nodeStack.empty()) {
        DirectoryNode* currNode = nodeStack.top(); // select dNode
        nodeStack.pop(); // remove dNode from list to be visited
        
        // get attributes of dNode (use these below)
        currNode->getName()
        currNode->isItFile()
        currNode->isItLink()
        currNode->getParent()
        currNode->getChildren()
        // serialize dNode attributes
                
        if (currNode->isItLink() == true) {
            // if dNode is a link type
            // get INode (use below)
            currNode->getInode()
            // serialize the ptr to inode specifically
            // dont serialize the rest of INode (so we don't repeat tasks)
        } else {
            // else (dNode is a regular type)
            // get Inode
            currNode->getInode()
            // access iNode attributes (examples below)
            get_pBits(currNode->getInode())
            get_setUid(currNode->getInode())
            get_setGid(currNode->getInode())
            get_nLinks(currNode->getInode())
            get_uId(currNode->getInode())
            get_gId(currNode->getInode())
            get_size(currNode->getInode())
            get_addr(currNode->getInode())
            // Serialize INode attributes here
            
            if (get_addr(currNode->getInode()) != nullptr) {
                // if iNode addr is not nullptr (has a file datablock)
                // access dataBlock attributes (just this one)
                getNumBlocks(get_addr(currNode->getInode()))
                // serialize databblock attributes here
            }
                
        }
        
        // add dNode to list of visited
        visitedNodes.push_back(currNode);
        
        // Update stack to be searched, by adding children of currNode (if there is any)
        for (DirectoryNode* child : currNode->getChildren()) {
            if (find(visitedNodes.begin(), visitedNodes.end(), child) == visitedNodes.end()) {
                nodeStack.push(child);
            }
        }
        // end of loop, starts again if stack is not empty.
    }
}