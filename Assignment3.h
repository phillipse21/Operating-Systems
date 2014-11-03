#ifndef Assignment3_H
#define Assignment3_H

#include "libraries.h"

void decrementTime(PCBQueue *&readyQueue);

void removeFirstPCB(PCBQueue *&readyQueue);

void shortestJobFirst(PCBQueue* &readyQueue,vector <string> memoryTable);//MemoryTable* &FirstFitTable,MemoryTable*&NextFitTable,
                       // MemoryTable* &bestFitTable,MemoryTable* &worstFitTable);

void fileDataToPCB(PCBQueue* &readyQueue, vector <string> fileData, vector <string> memoryTable);
                   //MemoryTable* &FirstFitTable,MemoryTable*&NextFitTable,
                    //MemoryTable* &bestFitTable,MemoryTable* &worstFitTable);

void intTimeRemaining(vector <int> &timeRemainingVector);

void orderedInsert(PCBQueue* &readyQueue, PCBStruct* &newPCB);

void ReadytoRunning(PCBQueue *readyQueue,vector <string> memoryTable);//MemoryTable *&mainMemoryTable);

void printWithTimeRemaining(PCBQueue* readyQueue);

void firstInFirstOut(PCBQueue* readyQueue,tm * &timeInfo,time_t initialTime,
                    vector <string> &memoryTable,vector <Spans*> &spanVector);
                    // MemoryTable* &FirstFitTable,MemoryTable*&NextFitTable,
                    //MemoryTable* &bestFitTable,MemoryTable* &worstFitTable);

void shortestTimeToCompletionFirst(PCBQueue* readyQueue,tm * &timeInfo,time_t initialTime,
                                   vector <string> memoryTable);
                                //   MemoryTable* &FirstFitTable,MemoryTable*&NextFitTable,
                                 //  MemoryTable* &bestFitTable,MemoryTable* &worstFitTable);

void whereToAddSTCF(PCBQueue* &readyQueue, PCBStruct* newPCB,ofstream& oFile, tm * &timeInfo,time_t initialTime);

void fixedPriorityPreEmptiveScheduling(PCBQueue* &readyQueue,tm * &timeInfo, time_t initialTime,
                                       vector <string> memoryTable);
                               //        MemoryTable* &FirstFitTable,MemoryTable*&NextFitTable,
                             //      MemoryTable* &bestFitTable,MemoryTable* &worstFitTable);

void whereToAddFPPS(PCBQueue* &readyQueue, PCBStruct* newPCB,ofstream& oFile, tm * &timeInfo,time_t initialTime);


#endif // Assignment3_H
