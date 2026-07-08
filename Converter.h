/* 
 * File:   Converter.h
 * Author: Kendrick Campbell
 *
 * Created on November 5, 2023, 1:23 PM
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include "Directory.h"
#include "iNodes.h"
#include "data.h"

using namespace std;

class OffsetConverter {
private:
    unordered_map<void*, int> ptrTo_OffsetMap;
    unordered_map<int, void*> offsetTo_ptrMap;
    
public:
    
    int convertToOffset(void* ptr); // Can take any pointer
    
    // goes through whole directory and serializes each node
    void serializeToFile(string& filename, Directory* dir);
    // load file and rebuild the file system structure (All you nate)
    void deserializeFromFile(string& filename);
};

#endif /* CONVERTER_H */

