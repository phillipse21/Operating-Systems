#ifndef Assignment4_H
#define Assignment4_H

#include "libraries.h"

class MemoryBlock
{
    public:
        MemoryBlock();
        void setIndexNum(int index);
        void setProcessName(string name);
        void setFreeSpace(bool free);
        void setMiddleBlock(bool middle);
        void setUpPtr(MemoryBlock* up);
        void setDownPtr(MemoryBlock* down);
        int getIndexNum();
        string getProcessName();
        bool getFreeSpace();
        bool getMiddleBlock();
        MemoryBlock* getUpPtr();
        MemoryBlock* getDownPtr();
        void freeBlockByIndexNum(int indexNum);
    private:
        int indexNum;
        string processName;
        bool freeSpace;
        bool middleBlock;
        MemoryBlock* upPtr;
        MemoryBlock* downPtr;
};

class freeSpans
{
public:
    freeSpans(int beginningIndex, int endIndex);
    void setBeginningIndex(int beginning);
    void setEndIndex(int endIndex);
    void setNumOfBlocks(int blocks);
    void setMiddleOfSpan(int middle);
    int getBeginningIndex();
    int getEndIndex();
    int getNumOfBlocks();
    int getMiddleOfSpan();
    void findNumOfBlocks();
    void findMiddleOfSpan();
private:
    int beginningIndex;
    int endIndex;
    int middleOfSpan;
    int numOfBlocks;
};

class MemoryTable
{
public:
    MemoryTable();
    void setHeadBlockPtr(MemoryBlock* headBlockPtr);
    void setTailBlockPtr(MemoryBlock* tailBlockPtr);
    void setNumOfFreeSpans(int numOfFreeSpans);
    void setNumOfFreeBlocks(int numOfFreeBlocks);
    MemoryBlock* getHeadBlockPtr();
    MemoryBlock* getTailBlockPtr();
    int getNumOfFreeSpans();
    int getNumOfFreeBlocks();
    int getSizeOfTable();
    freeSpans* getFreeSpanByVectorIndex(int i);
    void findFreeSpans();
    MemoryBlock* findMemoryBlockByIndex(int i);
    void setMiddleBlocks();
    void showMemoryTable();
private:
    MemoryBlock* headBlockPtr;
    MemoryBlock* tailBlockPtr;
    vector <freeSpans*> freeSpanVector;
    int numOfFreeSpans;
    int numOfFreeBlocks;
    int sizeOfTable;
};


bool firstFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable);


#endif
