/* 
 * File:   data.h
 * Author: Kendrick Campbell
 *
 * Created on October 24, 2023, 12:01 AM
 */

#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

class DataBlock {
    private:
        int numBlocks; // holds how much memory is taken by this block
        DataBlock* next; // pointer to next block
        string content;
        
    public:
        DataBlock(int numBlocks); // constructor for each block
        ~DataBlock(); // destructor for each block
        bool setNumBlocks(DataBlock* block, int numBlocks); // sets number of blocks
        int  getNumBlocks(DataBlock* block); // get number of blocks
        string getContent();
        friend class DataList;
        void add(DataBlock* block);
        void remove(DataBlock* data);
};

class DataList {
    private:
        DataBlock *first; // pointer to first block in list
        DataBlock *last; // pointer to last block in list
        
    public:
        DataList(); // constructor
        ~DataList(); // destructor
        //void add(DataBlock* block); // adds the memory block to list.
        ///void remove(DataBlock* data); // removes the memory block from list
        
        friend class DataBlock;
};

#endif /* DATA_H */

