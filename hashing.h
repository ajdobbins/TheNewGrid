#ifndef DATASTRUCTURES_H
#define DATASTRCUTURES_H
//#define CHUNK_SIZE 16384
#define CHUNK_SIZE 1000
#include <cstdio>

#include <fstream>
void chunkFile(char *fullFilePath, char *chunkName, unsigned long chunkSize);

void joinFile(char *chunkName, char *fileOutput);

int getFileSize(std::ifstream *file);

int hashChunk(unsigned int hash, const char *name);


int saveToTable(unsigned int x, const char * name);

#endif
