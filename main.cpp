/* 
 * File:   main.cpp
 * Author: Kendrick Campbell
 *
 * Created on November 27, 2023, 5:14 PM
 */

#include <cstdlib>
#include "Directory.h"
#include "iNodes.h"
#include "data.h"
using namespace std;

int main(int argc, char** argv) {
    Directory myDir;
    myDir.addDNode("/","user", false, 1, 1, 1);
    myDir.addDNode("user", "folder1", false, 1,1,1);
    myDir.addDNode("/user/folder1", "file", true, 1, 1, 1);
    return 0;
}

