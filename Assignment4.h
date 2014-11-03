/*
#ifndef Assignment4_H
#define Assignment4_H

#include "libraries.h"
/*
class MemoryBlock
{
    public:
        MemoryBlock();
        void setIndexNum(int index);
        void setProcessName(string name);
        void setFreeSpace(bool free);
        void setUpPtr(MemoryBlock* up);
        void setDownPtr(MemoryBlock* down);
        int getIndexNum();
        string getProcessName();
        bool getFreeSpace();
        MemoryBlock* getUpPtr();
        MemoryBlock* getDownPtr();
        void freeBlockByIndexNum(int indexNum);
    private:
        int indexNum;
        string processName;
        bool freeSpace;
        MemoryBlock* upPtr;
        MemoryBlock* downPtr;
};


class MemoryTable
{
public:
    MemoryTable();
    void setHeadBlockPtr(MemoryBlock* headBlockPtr);
    void setTailBlockPtr(MemoryBlock* tailBlockPtr);
    void setNumOfFreeBlocks(int numOfFreeBlocks);
    MemoryBlock* getHeadBlockPtr();
    MemoryBlock* getTailBlockPtr();
    int getNumOfFreeBlocks();
    int getSizeOfTable();
    MemoryBlock* findMemoryBlockByIndex(int i);
    void showMemoryTable();
    int findNumOfFreeBlocks();
    void removeFromTable(PCBStruct* deleteFromTable);
private:
    MemoryBlock* headBlockPtr;
    MemoryBlock* tailBlockPtr;
    int numOfFreeBlocks;
    int sizeOfTable;
};
*/
/*
class Spans
{
    public:
        Spans(int beginning, int ending);
        int getBeginning();
        int getEnding();
    private:
        int beginning;
        int ending;
};

void removeProcessFromTable(PCBStruct* processToDelete,MemoryTable *&mainMemoryTable);

void printWithTimeRemainingAndTable(PCBQueue *&readyQueue, MemoryTable *mainMemoryTable);

bool firstFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable,int beginning);

bool nextFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable);

bool bestFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable);

bool worstFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable);

void PrintTable(string fileName,MemoryTable* mainMemoryTable);

#endif

*/
