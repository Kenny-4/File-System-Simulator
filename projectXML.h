// Nathanael Jacob
// OS Group Project
// projectXML.h

#ifndef PXML_H
#define PXML_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stack>


// The includes are implied in the makefile
#include "iNodes.h"
#include "Directory.h"


// This is a class designed to imitate XML functionality without using actual XML
class pXML {

public:
	// Constructor
	pXML(Directory myDir);

	// Destructor
	~pXML();

	// retrieves id of tag
	int parseTag(std::string tag);

	// Parse Program
	// This program will take a .txt file
	// And it will search for a root <iNode> and its children <descriptors>
	// and convert those into iNodes
	int parseXML();

	// Write Program
	// This program will take a list of iNodes and convert it
	// into an easily stored .txt file
	void writeXML(DirectoryNode* dnode);
	void serializeDir(Directory myDir);
	void writeToFile(string line);

private:

	// Class Variable
	// An array which stores the node data
	std::string filetype, pbits, nlinks, uid, gid, setuid, setgid, size, addr, gen, atime, mtime, ctime, link, name, getIN, parent;
	time_t Atime, Mtime, Ctime;
	long int storeTime;

	void serializeDir(DirectoryNode* mydnode);

	// The storage file
	std::fstream XMLfile;

	Directory myDir;
};

#endif /* PXML_H */
