#ifndef DATASTRUCTURES_H
#define DATASTRCUTURES_H

#define CHUNK_SIZE 16384
#include <cstdio>

#include <fstream>
void chunkFile(char *fullFilePath, char *chunkName, unsigned long chunkSize);

void joinFile(char *chunkName, char *fileOutput);

int getFileSize(std::ifstream *file);

unsigned int hashChunk(char *name);

#endif
