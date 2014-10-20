#ifndef Assignment3_H
#define Assignment3_H

#include "libraries.h"

void shortestJobFirst(PCBQueue* &readyQueue);

void fileDataToPCB(PCBQueue* &readyQueue, vector <string> fileData);

void intTimeRemaining(vector <int> &timeRemainingVector);

void orderedInsert(PCBQueue* &readyQueue, PCBStruct* &newPCB);

void ReadytoRunning(PCBQueue* &readyQueue);

void printWithTimeRemaining(PCBQueue* readyQueue);

void firstInFirstOut(PCBQueue* readyQueue,tm * &timeInfo,time_t initialTime);

void shortestTimeToCompletionFirst(PCBQueue* readyQueue,tm * &timeInfo,time_t initialTime);

void whereToAddSTCF(PCBQueue* &readyQueue, PCBStruct* newPCB,ofstream& oFile, tm * &timeInfo,time_t initialTime);

void fixedPriorityPreEmptiveScheduling(PCBQueue* readyQueue,tm * &timeInfo, time_t initialTime);

void whereToAddFPPS(PCBQueue* &readyQueue, PCBStruct* newPCB,ofstream& oFile, tm * &timeInfo,time_t initialTime);


#endif // Assignment3_H
