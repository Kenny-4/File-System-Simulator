// Nathanael Jacob
// OS Group Project
// projectXML.cpp

#include "projectXML.h"

using namespace std;

// Constructor
pXML::pXML(Directory myDir) {
    string filetype, pbits, nlinks, uid, gid, setuid, setgid, size, gen, atime, mtime, ctime, link, name, parent;
    time_t Atime, Mtime, Ctime;
    long int storeTime;
//  addr, link, getIN are pointers
    XMLfile.open("XMLstorage.txt");
};

// Destructor
pXML::~pXML() {
    filetype, pbits, nlinks, uid, gid, setuid, setgid, size, gen, atime, mtime, ctime, link, name, parent = "";
};


int pXML::parseTag(string tag) {
    // A program to read a tag and get an ID from it
    int tagID = -1;

    // Identifier for the end of a node
    if (tag == "<iNode>") {
	tagID = 100;
    // The various descriptors
    } else if (tag =="<filetype>") {
	tagID = 0;
    } else if (tag =="<pbits>") {
        tagID = 1;
    } else if (tag =="<nlinks>") {
        tagID = 2;
    } else if (tag =="<uid>") {
        tagID = 3;
    } else if (tag =="<gid>") {
        tagID = 4;
    } else if (tag =="<size>") {
        tagID = 5;
    } else if (tag =="<addr>") {
        tagID = 6;
    } else if (tag =="<gen>") {
        tagID = 7;
    } else if (tag =="<atime>") {
        tagID = 8;
    } else if (tag =="<mtime>") {
        tagID = 9;
    } else if (tag =="<ctime>") {
        tagID = 10;
    } else if (tag =="<link>") {
	tagID = 11;
    } else if (tag=="<name>") {
	tagID = 12;
    } else if (tag=="<getIN>") {
	tagID = 13;
    } else if (tag=="<parent>") {
	tagID = 14;
    } else if (tag=="<setuid>") {
	tagID = 15;
    } else if (tag=="<setgid>") {
	tagID = 16;
    }

    // If tagID is 100, convert to node
    // If tagID is -1, an error ocurred
    return tagID;
};


int pXML::parseXML() {
    int tagID;
    string line;
    string descriptor;
    string myChar;
    bool isFile = false;
    string travelPath = "/";
    time_t temp;
    DirectoryNode* targetDir;
    INode* targetIN;

    // This program has to take a file and read each line
    if (XMLfile.is_open()) {
	while (XMLfile) {
	    while (true) {
	        // It will read each line individually, analyzing each char
	        myChar = XMLfile.get();
		line += myChar;

		// If the end of a tag is detected, extract the id and the descriptor
		if (myChar == ">") {
		   getline(XMLfile, descriptor);
		   tagID = pXML::parseTag(line);
		   break;
	    	}
	    }

	    // Sort the collected data into an array
	    switch (tagID) {
		case 100: // if it detects <0iNode>, end the sorting and place into directory
                    // Convert the contents of the array into an iNode
		    if (filetype == "file") {
			isFile = true;
		    }
		    myDir.addDNode(parent, name, isFile, stoi(pbits), stoi(uid), stoi(gid));

		    // Travel to the dNode we just added
		    if (parent != "/") {
			// Checking that our parent is not the root
			string travelPath = parent + "/" + name;
		    }
		    targetDir = myDir.travelTo(travelPath);
		    targetIN = targetDir->getInode();

		    // So that we can edit its iNode
		    targetIN->set_nLinks(targetIN, stoi(nlinks));
		    targetIN->set_size(targetIN, stoi(size));
		    targetIN->set_gen(targetIN, stoi(gen));
		    targetIN->set_setUid(targetIN, stoi(setuid));
		    targetIN->set_setGid(targetIN, stoi(setgid));

		    // Convert string to long.
		    storeTime = stol(atime);

		    // Convert long to time_t
		    temp = storeTime;

		    // Store it
		    targetIN->set_Atime(temp);

		    // Rinse and Repeat
		    storeTime = stol(mtime);
		    temp = storeTime;
		    targetIN->set_Mtime(temp);

		    storeTime = stol(ctime);
		    temp = storeTime;
		    targetIN->set_Ctime(temp);

                    // Wipe the contents of the array
		    isFile = false;
		    parent = "";
                    filetype, pbits, nlinks, uid, gid, setuid, setgid, size, gen, atime, mtime, ctime, link, name = "";
		    break;

                case 0:
                    filetype = descriptor;
                    break;
                case 1:
                    pbits = descriptor;
                    break;
                case 2:
                    nlinks = descriptor;
                    break;
                case 3:
                    uid = descriptor;
                    break;
                case 4:
                    gid = descriptor;
                    break;
                case 5:
                    size = descriptor;
                    break;
                case 6:
                    //addr = descriptor; // addr is the associated data
                    break;
                case 7:
                    gen = descriptor;
                    break;
                case 8:
                    atime = descriptor;
                    break;
                case 9:
                    mtime = descriptor;
                    break;
                case 10:
                    ctime = descriptor;
                    break;
		case 11:
		    link = descriptor;
		    break;
		case 12:
		    name = descriptor;
		    break;
		case 13:
		    getIN = descriptor;
		    break;
		case 14:
		    // Parent is a path that says "go here, make this my parent"
		    // By default, it is set to the root, or "/"
		    parent = descriptor;
		    break;
		case 15:
		    setuid = descriptor;
		    break;
		case 16:
		    setgid = descriptor;
		    break;
		default:
		    cout << "The tag was not recognized.";
		    break;
	    }

	    // Reset vars
	    descriptor, line = "";
	}
    }
    // If tagID returns -1, an error has occurred
    return tagID;
};

void pXML::writeToFile(string line) {
    XMLfile << line + "\n";
};

// Public serializeDir
void pXML::serializeDir(Directory myDir) {
    // Start at root, find vector of children, recursively find each child
    vector<DirectoryNode*> Children = myDir.root->getChildren();
        for (int i = 0; i < Children.size(); i++) {
	cerr << "Searching a Child \n";
	    serializeDir(Children.at(i));
    }
};

// Private serializeDir
void pXML::serializeDir(DirectoryNode* mydnode) {
    if (!mydnode->isItFile()) {
	// If our node is a folder, search the children first 
	vector<DirectoryNode*> Children = mydnode->getChildren();
        for (int i = 0; i < Children.size(); i++) {
	    cerr << "Searching a Child \n";
	    serializeDir(Children.at(i));
	}
    }
    // Then, write our current node
	cerr << "Writing in Serialize \n";
    writeXML(mydnode);
};

void pXML::writeXML(DirectoryNode* mydnode) {
    if (XMLfile.is_open()) {
        while (XMLfile) {
	    // Write a pointer to the dnode's inode
	    INode* myinode = mydnode->getInode();

	    link = "<link>";
	    if (mydnode->isItLink() == true) {
		link += "true";
	    } else {
		link += "false";
	        // Write attributes of the dNode to the file
                filetype = "<filetype>";
                filetype += myinode->get_fileType(myinode);
	        pXML::writeToFile(filetype);

    	        pbits = "<pbits>";
	        pbits += to_string(myinode->get_pBits(myinode));
                pXML::writeToFile(pbits);

	        nlinks = "<nlinks>";
	        nlinks += to_string(myinode->get_nLinks(myinode));
                pXML::writeToFile(nlinks);

	        uid = "<uid>";
	        uid += to_string(myinode->get_uId(myinode));
                pXML::writeToFile(uid);

	        gid = "<gid>";
	        gid += to_string(myinode->get_gId(myinode));
	        pXML::writeToFile(gid);

	        setuid = "<setuid>";
                setuid += to_string(myinode->get_setUid(myinode));
                pXML::writeToFile(setuid);

                setgid = "<setgid>";
                setgid += to_string(myinode->get_setGid(myinode));
                pXML::writeToFile(setgid);

	        size = "<size>";
	        size += to_string(myinode->get_size(myinode));
                pXML::writeToFile(size);

	        gen = "<gen>";
	        gen += to_string(myinode->get_gen(myinode));
	        pXML::writeToFile(gen);

	        atime = "<atime>";
	        atime += to_string(myinode->get_Atime(myinode));
                pXML::writeToFile(atime);

                mtime = "<mtime>";
                mtime += to_string(myinode->get_Mtime(myinode));
                pXML::writeToFile(mtime);

                ctime = "<ctime>";
                ctime += to_string(myinode->get_Ctime(myinode));
                pXML::writeToFile(ctime);
	    }
            pXML::writeToFile(link);

	    name = "<name>";
	    name += mydnode->getName();
            pXML::writeToFile(name);

	    parent = "<parent>";
	    parent += myDir.getPathString(mydnode);
	    pXML::writeToFile(parent);

	    // Mark the ending
            string buffer = "<iNode>";
            pXML::writeToFile(buffer);

	    // Clear Variables
	    filetype, pbits, nlinks, uid, gid, setuid, setgid, size, gen, atime, mtime, ctime, link, name = "";
	    break;
	}
    }
};
