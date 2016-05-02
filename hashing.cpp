//   -std=c++0x to compile
#include "hashing.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <string>
#define NETWORK_SIZE 3;
using namespace std;
#include <boost/functional/hash.hpp>
#include <unordered_map>
#include <utility>
//const char * hash_table[HASH_TABLE_SIZE];

//giving file name should reveal which device file is held on
    unordered_map <const char*, int> device_map;
// Chunks a file by breaking it up into chunks of "chunkSize" bytes.
// Credit to Martyr2 
// http://www.coderslexicon.com/file-chunking-and-merging-in-c/
void chunkFile(char *fullFilePath, char *chunkName, unsigned long chunkSize) {
        ifstream fileStream;
        fileStream.open(fullFilePath, ios::in | ios::binary);
        
        // File open a success
        if (fileStream.is_open()) {
                ofstream output;
                int counter = 1;

                string fullChunkName;
		
                // Create a buffer to hold each chunk
                char *buffer = new char[chunkSize];

                // Keep reading until end of file
                while (!fileStream.eof()) {

                        // Build the chunk file name. Usually drive:\\chunkName.ext.N
                        // N represents the Nth chunk
                        fullChunkName.clear();
                        fullChunkName.append(chunkName);
                        fullChunkName.append(".");

                     // Convert counter integer into string and append to name.
                        
                        stringstream intBuf;
                        intBuf << counter;
                        fullChunkName.append(intBuf.str());

  			//store in hash table

			boost::hash<std::string> string_hash;
                        const char *fName = fullChunkName.c_str();
                        unsigned int x = string_hash(fName);
                        int devID = saveToTable(x, fName);
                	string devicePath;
			devicePath.append("device");

			      stringstream intBuf2;
                        intBuf2 << devID;
                        devicePath.append(intBuf2.str());

			devicePath.append("/");
			devicePath.append(fullChunkName);
                        // Open new chunk file name for output
                        output.open(devicePath.c_str(),ios::out | ios::trunc | ios::binary);
			                        cout<<devicePath<<endl;
                        // If chunk file opened successfully, read from input and 
                        // write to output chunk. Then close.
                        if (output.is_open()) { 
                                fileStream.read(buffer,chunkSize);
                                // gcount() returns number of bytes read from stream.
                                output.write(buffer,fileStream.gcount());
                                output.close();

                                counter++;

                              
       			 }
                }

                // Cleanup buffer
                delete(buffer);

                // Close input file stream.
                fileStream.close();

                cout << "Chunking complete! " << counter - 1 << " files created." << endl;
        }
        else { cout << "Error opening file!" << endl; }
  
}

void joinFile(char *chunkName, char *fileOutput) {
        string fileName;

        // Create our output file
        ofstream outputfile;
        outputfile.open(fileOutput, ios::out | ios::binary);

        // If successful, loop through chunks matching chunkName
        if (outputfile.is_open()) {
                bool filefound = true;
                int counter = 1;
                int fileSize = 0;

                while (filefound) {
                        filefound = false;

                        // Build the filename
                        fileName.clear();
                        fileName.append(chunkName);
                        fileName.append(".");

                        //char intBuf[10];
                        //_itoa(counter,intBuf,10);
                        stringstream intBuf;
                        intBuf << counter;
                        fileName.append(intBuf.str());

                        // Open chunk to read
                        ifstream fileInput;
                        fileInput.open(fileName.c_str(), ios::in | ios::binary);

                        // If chunk opened successfully, read it and write it to 
                        // output file.

                        if (fileInput.is_open()) {
                                filefound = true;
                                fileSize = getFileSize(&fileInput);
                                char *inputBuffer = new char[fileSize];

                                fileInput.read(inputBuffer,fileSize);
                                outputfile.write(inputBuffer,fileSize);
                                delete(inputBuffer);
                                //int s = strcmp(fileName.c_str(), "test.c.1");

                                //unsigned int x = hashChunk(fileName.c_str());
                                boost::hash<std::string> string_hash;
                                const char *fName = fileName.c_str();
                                unsigned int x = string_hash(fName);
                                cout<<x<<" "<<fName<<endl;
                                //getFromTable(x, fName);       
                                fileInput.close();
                        }
                        counter++;
                }

                // Close output file.
                outputfile.close();

                cout << "File assembly complete!" << endl;
        }
        else { cout << "Error: Unable to open file for output." << endl; }

}







// Simply gets the file size of file.
int getFileSize(ifstream *file) {
        file->seekg(0,ios::end);
        int filesize = file->tellg();
        file->seekg(ios::beg);
        return filesize;
}

//saves in the hash table
//calculates which device this chunk should be sent to
int saveToTable(unsigned int hash, const char* name)
{
	int x;
        x = hash % NETWORK_SIZE;
        //device ID?
        device_map.insert({name, x});
        return x;

}

int hashChunk(unsigned int hash, const char *name)
{ 
	    		cout << name<<endl;
	
	 unordered_map <const char*, int>::const_iterator chunkName = device_map.find(name);

	if ( chunkName == device_map.end() )
    		cout << "not found";
  	//else
    		//cout << name<<endl;
	return chunkName->second;
}
int main()
{
        char *ffp ="test.c";
        chunkFile(ffp, ffp, CHUNK_SIZE/8);
//      char *chunk = "storage.h.1";
        char *output = "og.h";
       // joinFile(ffp,output);
        

//unsigned int x = hashChunk(ffp1);
//cout<<x<<endl;

        return 1;
}



