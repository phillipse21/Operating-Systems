#ifndef Assignment3_H
#define Assignment3_H

#include "libraries.h"

void shortestJobFirst(PCBQueue* &readyQueue);

void fileDataToPCB(PCBQueue* &readyQueue, vector <string> fileData);

void intTimeRemaining(vector <int> &timeRemainingVector);

void orderedInsert(PCBQueue* &readyQueue, PCBStruct* &newPCB);

void ReadytoRunning(PCBQueue* &readyQueue);

void printWithTimeRemaining(PCBQueue* readyQueue);


#endif // Assignment3_H
