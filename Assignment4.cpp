#include "libraries.h"

MemoryBlock::MemoryBlock()
{
    indexNum = -1;
    processName = "";
    freeSpace = true;
    upPtr = NULL;
    downPtr = NULL;
}

void MemoryBlock::setIndexNum(int index)
{
    this->indexNum = index;
}

void MemoryBlock::setProcessName(string name)
{
    this -> processName = name;
}

void MemoryBlock::setFreeSpace(bool free)
{
    this -> freeSpace = free;
}

void MemoryBlock::setMiddleBlock(bool middle)
{
    this -> middleBlock = middle;
}

void MemoryBlock::setUpPtr(MemoryBlock* up)
{
    this -> upPtr = up;
}

void MemoryBlock::setDownPtr(MemoryBlock* down)
{
    this -> downPtr = down;
}

int MemoryBlock::getIndexNum()
{
    return indexNum;
}

string MemoryBlock::getProcessName()
{
    return processName;
}

bool MemoryBlock::getFreeSpace()
{
    return freeSpace;
}

bool MemoryBlock::getMiddleBlock()
{
    return middleBlock;
}

MemoryBlock* MemoryBlock::getUpPtr()
{
    return upPtr;
}

MemoryBlock* MemoryBlock::getDownPtr()
{
    return downPtr;
}


freeSpans::freeSpans(int beginningIndex, int endIndex)
{
    this -> beginningIndex = beginningIndex;
    this -> endIndex = endIndex;
}

void freeSpans::setBeginningIndex(int beginning)
{
    this -> beginningIndex = beginning;
}

void freeSpans::setEndIndex(int endIndex)
{
    this -> endIndex = endIndex;
}

void freeSpans::setNumOfBlocks(int blocks)
{
    this -> numOfBlocks = blocks;
}

void freeSpans::setMiddleOfSpan(int middle)
{
    this -> middleOfSpan = middle;
}

int freeSpans::getBeginningIndex()
{
    return beginningIndex;
}

int freeSpans::getEndIndex()
{
    return endIndex;
}

int freeSpans::getNumOfBlocks()
{
    return numOfBlocks;
}

int freeSpans::getMiddleOfSpan()
{
    return middleOfSpan;
}

void freeSpans::findNumOfBlocks()
{
    numOfBlocks = endIndex - beginningIndex + 1;
}

void freeSpans::findMiddleOfSpan()
{
    findNumOfBlocks();
    middleOfSpan = numOfBlocks/2;
}


MemoryTable::MemoryTable()
{
    headBlockPtr = new MemoryBlock;
    tailBlockPtr = new MemoryBlock;


    headBlockPtr->setDownPtr(tailBlockPtr);
    headBlockPtr->setUpPtr(NULL);

    tailBlockPtr->setUpPtr(headBlockPtr);
    tailBlockPtr->setDownPtr(NULL);

    numOfFreeSpans = 0;
    numOfFreeBlocks = 0;
    sizeOfTable = 1024;

    MemoryBlock* oldLast= NULL;

    for(int i = 1; i < sizeOfTable+1; i++)
    {
        MemoryBlock* newMemoryBlock = new MemoryBlock;
        newMemoryBlock->setIndexNum(i);

        oldLast = tailBlockPtr->getUpPtr();

        oldLast->setDownPtr(newMemoryBlock);
        tailBlockPtr->setUpPtr(newMemoryBlock);

        newMemoryBlock->setDownPtr(tailBlockPtr);
        newMemoryBlock->setUpPtr(oldLast);
    }

}

void MemoryTable::setHeadBlockPtr(MemoryBlock* headBlockPtr)
{
    this -> headBlockPtr = headBlockPtr;
}

void MemoryTable::setTailBlockPtr(MemoryBlock* tailBlockPtr)
{
    this -> tailBlockPtr = tailBlockPtr;
}

void MemoryTable::setNumOfFreeSpans(int numOfFreeSpans)
{
    this -> numOfFreeSpans = numOfFreeSpans;
}

void MemoryTable::setNumOfFreeBlocks(int numOfFreeBlocks)
{
    this -> numOfFreeBlocks = numOfFreeBlocks;
}

MemoryBlock* MemoryTable::getHeadBlockPtr()
{
    return headBlockPtr;
}

MemoryBlock* MemoryTable::getTailBlockPtr()
{
    return tailBlockPtr;
}

int MemoryTable::getNumOfFreeSpans()
{
    return numOfFreeSpans;
}

int MemoryTable::getNumOfFreeBlocks()
{
    return numOfFreeBlocks;
}

int MemoryTable::getSizeOfTable()
{
    return sizeOfTable;
}

freeSpans* MemoryTable::getFreeSpanByVectorIndex(int i)
{
    return freeSpanVector[i];
}

void MemoryTable::findFreeSpans()
{
    int tempBeginning = 0;
    int tempEnd = 0;
    MemoryBlock* traversePtr = headBlockPtr->getDownPtr();

    while(traversePtr != tailBlockPtr)
    {
        if(traversePtr->getFreeSpace() == true && traversePtr->getUpPtr()->getFreeSpace() == false)
        {
            tempBeginning = traversePtr->getIndexNum();
        }
        else if(traversePtr->getFreeSpace() == false && traversePtr->getUpPtr()->getFreeSpace() == true)
        {
            tempEnd = traversePtr->getUpPtr()->getIndexNum();
            freeSpans* newSpan =  new freeSpans(tempBeginning,tempEnd);
            freeSpanVector.push_back(newSpan);
            tempBeginning = 0;
            tempEnd = 0;
        }

        traversePtr = traversePtr->getDownPtr();
    }
}

MemoryBlock* MemoryTable::findMemoryBlockByIndex(int i)
{
    MemoryBlock* traverseBlock = headBlockPtr->getDownPtr();

    while(traverseBlock->getIndexNum() != i)
    {
        traverseBlock = traverseBlock->getDownPtr();
    }
    if(traverseBlock->getIndexNum() == i)
    {
        return traverseBlock;
    }
}

void MemoryTable::setMiddleBlocks()
{
    freeSpans* currentSpan = NULL;
    MemoryBlock* middleBlock = NULL;
    for(int i = 0; i < freeSpanVector.size();i++)
    {
        currentSpan = freeSpanVector[i];
        middleBlock = findMemoryBlockByIndex(currentSpan->getMiddleOfSpan());
        middleBlock->setMiddleBlock(true);
    }
}

void MemoryTable::showMemoryTable()
{
    system("CLS");

    MemoryBlock* traverseBlock = headBlockPtr->getDownPtr();
    while(traverseBlock != tailBlockPtr)
    {
        cout << traverseBlock->getIndexNum() << ": " << traverseBlock->getProcessName() << endl;
        traverseBlock = traverseBlock->getDownPtr();
    }
}

void traverseThroughQueue(PCBQueue* readyQueue)
{
    MemoryTable* FirstFitTable = new MemoryTable;
    MemoryTable* NextFitTable = new MemoryTable;

    PCBStruct* traversePCB = readyQueue->getHeadNodePtr()->getNextPtr();

    while(traversePCB != readyQueue->getTailNodePtr())
    {
        firstFit(traversePCB,FirstFitTable);
    }
}

bool firstFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable)
{
    int spaceNeeded = newProcess->getMemoryNeeded();
    int counter = 0;
    int beginningIndex = 0;
    int endingIndex = 0;
    bool spaceFound = false;

    MemoryBlock* traverseBlock = mainMemoryTable->getHeadBlockPtr()->getDownPtr();
    while(traverseBlock != mainMemoryTable->getTailBlockPtr() && counter < spaceNeeded)
    {
        if(counter == spaceNeeded)
        {
            freeSpans* newSpan = new freeSpans(beginningIndex,endingIndex);
            MemoryBlock* current = NULL;
            for(int i = beginningIndex; i <= endingIndex; i++)
            {
                current = mainMemoryTable->findMemoryBlockByIndex(i);
                current->setProcessName(newProcess->getProcessName());
                current->setFreeSpace(false);
            }
            spaceFound = true;
            return spaceFound;
        }
        if(traverseBlock->getUpPtr()->getFreeSpace() == false && traverseBlock->getFreeSpace() == true)
        {
            beginningIndex = traverseBlock->getIndexNum();
            counter++;
        }
        else if(traverseBlock->getDownPtr()->getFreeSpace() == false && traverseBlock->getFreeSpace() == true)
        {
            endingIndex = traverseBlock->getIndexNum();
            counter++;
        }
        traverseBlock = traverseBlock->getDownPtr();
    }

    if(traverseBlock == mainMemoryTable->getTailBlockPtr() && spaceFound)
    {
        return spaceFound;
    }
}

bool nextFit(PCBStruct* newProcess, MemoryTable* &mainMemoryTable)
{
    bool processAdded = false;
    int counter = 0;
    int beginningIndex = 0;
    int endingIndex = 0;
    int memoryNeeded = newProcess->getMemoryNeeded();

    MemoryBlock* traverseBlock = mainMemoryTable->getHeadBlockPtr();
    while(traverseBlock != mainMemoryTable->getTailBlockPtr())
    {
        if(counter == memoryNeeded)
        {
            freeSpans* newSpan = new freeSpans(beginningIndex,endingIndex);
            MemoryBlock* current = NULL;
            for(int i = beginningIndex; i <= endingIndex; i++)
            {
                current = mainMemoryTable->findMemoryBlockByIndex(i);
                current->setProcessName(newProcess->getProcessName());
                current->setFreeSpace(false);
            }
            processAdded = true;
            return processAdded;
        }
        if(traverseBlock->getUpPtr()->getFreeSpace() == false && traverseBlock->getFreeSpace() == true)
        {
            beginningIndex = traverseBlock->getIndexNum();
            counter++;
        }
        else if(traverseBlock->getDownPtr()->getFreeSpace() == false && traverseBlock->getFreeSpace() == true)
        {
            endingIndex = traverseBlock->getIndexNum();
            counter++;
            if(counter < memoryNeeded)
            {
                beginningIndex = 0;
                endingIndex = 0;
                processAdded = false;
            }
        }
        traverseBlock = traverseBlock->getDownPtr();
    }
}


void sendToFile(string fileName, MemoryTable* mainMemoryTable)
{
    ofstream oFile;
    oFile.open(fileName.c_str());

    MemoryBlock* traverseBlock = mainMemoryTable->getHeadBlockPtr()->getDownPtr();
    while(traverseBlock != mainMemoryTable->getTailBlockPtr())
    {
        oFile << traverseBlock->getIndexNum() << ": " << traverseBlock->getProcessName() << endl;
        oFile << "____________________________________________________________________" << endl;
        traverseBlock = traverseBlock->getDownPtr();
    }
}
