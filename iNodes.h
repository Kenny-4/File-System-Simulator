/* 
 * File:   iNodes.h
 * Author: Kendrick Campbell
 *
 * Created on October 23, 2023, 11:51 PM
 */

#ifndef INODES_H
#define INODES_H

#include <string>
#include <ctime>
#include <iostream>
#include "data.h"

using namespace std;

class INode {
private:
    INode* next;
    // Mode properties
    string fileType; // only "file" or "folder"
    int pBits; // read,write,execute permissions
    // setUid/Gid can either be 0 or 1.
    int setUid; // if 1: file executes according to owner/file group perms
    int setGid; // if 0: file executes according to user/group perms
    
    // Regular properties
    int nLinks; // number of links
    int uId; // id of user
    int gId; // id of group
    int size; // size of blocks used by storage (numBlocks of dataBlock)
    DataBlock* addr; // pointer to dataBlock associated with it
    int gen; // generation of iNode
    time_t Atime; // accessed time
    time_t Mtime; // file modified time
    time_t Ctime; // inode modified time
    
public:
    // Constructor
    INode(string fileType,int pBits, int setUid, int setGid);
   
    // Proper delete function
    void deleteINode(INode* iNode);
    
    // Get property commands
    string get_fileType(INode* iNode) const;
    int get_pBits(INode* iNode) const;
    int get_setUid(INode* iNode) const;
    int get_setGid(INode* iNode) const;
    int get_nLinks(INode* iNode) const;
    int get_uId(INode* iNode) const;
    int get_gId(INode* iNode) const;
    int get_size(INode* iNode) const;
    DataBlock* get_addr(INode* iNode) const;
    int get_gen(INode* iNode) const;
    time_t get_Atime(INode* iNode) const;
    time_t get_Mtime(INode* iNode) const;
    time_t get_Ctime(INode* iNode) const;
    
    // Set property commands
    void set_fileType(INode* iNode, string type);
    void set_pBits(INode* iNode, int pBits);
    void set_setUid(INode* iNode, int setuid);
    void set_setGid(INode* iNode, int setgid);
    void set_nLinks(INode* iNode, int num);
    void add_nLink(INode* iNode);
    int sub_nLink(INode* iNode);
    void set_uId(INode* iNode, int id);
    void set_gId(INode* iNode, int id);
    void set_size(INode* iNode, int blocks);
    void set_addr(INode* iNode, DataBlock* block);
    void set_gen(INode* iNode, int num);
    void add_gen(INode* iNode);
    void set_Atime(time_t time);
    void update_Atime();
    void set_Mtime(time_t time);
    void update_Mtime();
    void set_Ctime(time_t time);
    void update_Ctime();
    
};

#endif /* INODES_H */

