#ifndef Assignment3_H
#define Assignment3_H

#include "libraries.h"

void shortestJobFirst(PCBQueue* &readyQueue);

void fileDataToPCB(PCBQueue* &readyQueue, vector <string> fileData);

void VectorIntoList(PCBQueue* &readyQueue,vector <PCBStruct*> &timeRemainingVector);

void findByTimeRemaining(int timeRemaining, PCBQueue* &readyQueue);

void addToList(PCBQueue* &readyQueue, PCBStruct* &structToAdd);

void intTimeRemaining(vector <int> &timeRemainingVector);

void intoQueue(vector <int> timeRemainingVector,PCBQueue* &readyQueue, vector <PCBStruct*> &unorganizedVector);

PCBStruct* findByValue(int value, vector <PCBStruct*> &unorganizedVector);

void orderedInsert(PCBQueue* &readyQueue, PCBStruct* &newPCB);

void printQueue(PCBQueue* queueuToPrint);

#endif // Assignment3_H
