#include <iostream>
#include <fstream>
#include <string>
#include "projectXML.h"

using namespace std;

int main(){
    int rc = 1;

    cerr << "Pre Directory Creation \n";
    Directory myDir;

    cerr << "Post directory, pre pxml \n";
    pXML myPXML(myDir);

    cerr << "Post pmxl, pre dn \n";
    myDir.addDNode("/", "deeznuts", false, 1, 1, 1);
    myDir.addDNode("deeznuts", "ligma", true, 1, 1, 1);

    cerr << "writeXML \n";
    myPXML.serializeDir(myDir);

    //cerr << "parseXML";
    //myPXML.parseXML();

    return rc;
};
