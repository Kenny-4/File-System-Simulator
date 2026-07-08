/* 
 * File:   iNodes.cpp
 * Author: Kendrick Campbell
 *
 * Created on October 24, 2023, 4:22 PM
 */

#include "iNodes.h"
#include "Directory.h"
class DataList;


// Creates the INode and the DataBlock (if necessary)
INode::INode(string fileType,int pBits, int uid, int gid) {
this->fileType = fileType;
this->pBits = pBits;
this->setUid = 0; // By default, file executes according to current user/group
this->setGid = 0; // If 1, file executes according to initial creator/group
this->nLinks = 1;
this->uId = uid;
this->gId = gid;

if (fileType == "file") {
    // Creates the DataBlock and inserts it into the list
    DataBlock* data = new DataBlock(2);
    data->add(data);
    this->size = 2; // default size of datablock
    this->addr = data;
} else {
    // otherwise a "folder":
    this->size = 1; // number of items in folder (including itself)
    this->addr = nullptr;
}

this->gen = 1;
this->Atime = this->Mtime = this->Ctime = time(nullptr);
}

// deletes iNode and the associated address
void INode::deleteINode(INode* iNode) {
    if (iNode) {
        if (get_fileType(iNode) == "file") {
            get_addr(iNode)->remove(get_addr(iNode));
        }
    }
}

// All of the get commands below
string INode::get_fileType(INode* iNode) const {
    return iNode->fileType;
}
int INode::get_pBits(INode* iNode) const {
    return iNode->pBits;
}
int INode::get_setUid(INode* iNode) const {
    return iNode->setUid;
}
int INode::get_setGid(INode* iNode) const {
    return iNode->setGid;
}
int INode::get_nLinks(INode* iNode) const {
    return iNode->nLinks;
}
int INode::get_uId(INode* iNode) const {
    return iNode->uId;
}
int INode::get_gId(INode* iNode) const {
    return iNode->gId;
}
int INode::get_size(INode* iNode) const {
    return iNode->size;
}
DataBlock* INode::get_addr(INode* iNode) const {
    return iNode->addr;
}
int INode::get_gen(INode* iNode) const {
    return iNode->gen;
}
time_t INode::get_Atime(INode* iNode) const {
    return iNode->Atime;
}
time_t INode::get_Mtime(INode* iNode) const {
    return iNode->Mtime;
}
time_t INode::get_Ctime(INode* iNode) const {
    return iNode->Ctime;
}

// Below are all of the set commands
void INode::set_fileType(INode* iNode, string type) {
    iNode->fileType = type;
}
void INode::set_pBits(INode* iNode, int bits) {
    iNode->pBits = bits;
}
void INode::set_setUid(INode* iNode, int setuid) {
    iNode->setUid = setuid;
}
void INode::set_setGid(INode* iNode, int setgid) {
    iNode->setGid = setgid;
}
// Adds to the number of links when needed
void INode::add_nLink(INode* iNode) {
    iNode->nLinks += 1;
}

void INode::set_nLinks(INode* iNode, int num) {
    iNode->nLinks = num;
}
// subtracts from the number of link, returns the number back to the directory
int INode::sub_nLink(INode* iNode) {
    iNode->nLinks -= 1;
    return nLinks;
}
void INode::set_uId(INode* iNode, int id) {
    iNode->uId = id;
}
void INode::set_gId(INode* iNode, int id) {
    iNode->gId = id;
}
void INode::set_size(INode* iNode, int num) {
    iNode->size = num;
}
void INode::set_addr(INode* iNode, DataBlock* block) {
    iNode->addr = block;
}
// For generation, we only need to add, there is no need to set a specific val.
void INode::add_gen(INode* iNode) {
    iNode->gen += 1;
}

void INode::set_gen(INode* iNode, int num) {
    iNode->gen = num;
}
void INode::set_Atime(time_t time) {
    this->Atime = time;
}

void INode::update_Atime() {
    this->Atime = time(nullptr);
}
void INode::set_Mtime(time_t time) {
    this->Mtime = time;
}

void INode::update_Mtime() {
    this->Mtime = time(nullptr);
}

void INode::set_Ctime(time_t time) {
    this->Ctime = time;
}

void INode::update_Ctime() {
    this->Ctime = time(nullptr);
}
