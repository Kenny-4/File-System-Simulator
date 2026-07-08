/* 
 * File:   data.cpp
 * Author: Kendrick Campbell
 *
 * Created on October 24, 2023, 1:26 PM
 */

#include "data.h"
#include "Directory.h"


// Creates a new datablock
DataBlock::DataBlock(int num) {
    this->numBlocks = num;
    this->next = nullptr;
    this->content = "";
}

DataBlock::~DataBlock() {
    delete this;
}

// Sets number of blocks of the data
bool DataBlock::setNumBlocks(DataBlock* block, int num) {
    bool rc = false;
    if (block != nullptr) {
       block->numBlocks = num;
       rc = true;
   }
    return rc;
}

string DataBlock::getContent() {
    return this->content;
}

// returns the number of blocks that the data holds
int DataBlock::getNumBlocks(DataBlock* block) {
    return block->numBlocks;
}

// Creates the dataList
DataList::DataList()  {
    first = last = nullptr;
}

// Adds block to the end of the list
void DataBlock::add(DataBlock* block) {
    if (freeMem - block->getNumBlocks(block) < 0) {
        cerr << "Cannot add block. Out of memory" << endl;
    } else {
        freeMem - block->getNumBlocks(block);
    }
    //if (!first) {
        // Case of empty list
        //first = block;
    //} else {
        //last->next = block;
    //}
    //last = block;
}

// Removes block from the list
void DataBlock::remove(DataBlock* block) {
    //if (block && first) {
        // Check that block is real and list isn't empty
        //if (first == block) {
            // Case if block is first
            //first = first->next;
            freeMem + block->getNumBlocks(block);
            delete block;
            //if (first == nullptr) {
                // Case if block is only thing in list
            //    last = nullptr;
            //}
        //} else {
            // Case that block is in the middle of list
            //DataBlock* current = first;
            // Searches for block to be removed
            //while (current && current->next != block) {
                //current = current->next;
            //}
            //if (current) {
                // Fixes the next ptr
                //current->next = block->next;
                // GLOBAL VAR MEMORY - getNumBlocks(block);
                //delete block;
                //if (current->next == nullptr) {
                //last = current;
                //}
            //}
        //}
    //}
}