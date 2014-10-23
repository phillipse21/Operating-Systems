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

MemoryBlock* MemoryBlock::getUpPtr()
{
    return upPtr;
}

MemoryBlock* MemoryBlock::getDownPtr()
{
    return downPtr;
}


MemoryTable::MemoryTable()
{
    headBlockPtr = new MemoryBlock;
    tailBlockPtr = new MemoryBlock;


    headBlockPtr->setDownPtr(tailBlockPtr);
    headBlockPtr->setUpPtr(NULL);

    tailBlockPtr->setUpPtr(headBlockPtr);
    tailBlockPtr->setDownPtr(NULL);

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

int MemoryTable::getNumOfFreeBlocks()
{
    return numOfFreeBlocks;
}

int MemoryTable::getSizeOfTable()
{
    return sizeOfTable;
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


int MemoryTable::findNumOfFreeBlocks()
{
    numOfFreeBlocks = 0;
    MemoryBlock* current = headBlockPtr;
    while(current != tailBlockPtr)
    {
        if(current->getFreeSpace() == true)
            numOfFreeBlocks++;
        current = current->getDownPtr();
    }
}

void MemoryTable::removeFromTable(PCBStruct* deleteFromTable)
{
    cout << "278" << endl;
    MemoryBlock* current = headBlockPtr;
    while(current != tailBlockPtr)
    {
        if(current->getProcessName() == deleteFromTable->getProcessName())
        {
            current->setProcessName("");
            current->setFreeSpace(true);
        }
        current = current->getDownPtr();
    }
}


void MemoryTable::showMemoryTable()
{
    //system("CLS");

    MemoryBlock* traverseBlock = headBlockPtr->getDownPtr();
    while(traverseBlock != tailBlockPtr)
    {
        if(traverseBlock->getProcessName() == "")
            return;
        cout << traverseBlock->getIndexNum() << ": " << traverseBlock->getProcessName() << endl;
        traverseBlock = traverseBlock->getDownPtr();
    }
}



bool firstFit(PCBStruct* newProcess, MemoryTable *&mainMemoryTable,int beginning)
{
    int spaceNeeded = newProcess->getMemoryNeeded();

    int sizeOfTable = mainMemoryTable->getSizeOfTable();
    int counter = 0;
    int beginningIndex = 0;
    int endingIndex = 0;
    bool spaceFound = false;
    bool consecutive = true;
    mainMemoryTable->findNumOfFreeBlocks();
    if(spaceNeeded > mainMemoryTable->getNumOfFreeBlocks())
        return false;

    if(beginning > sizeOfTable)
    {
        return true;
    }
    else
    {
        beginningIndex = beginning;
    }
    endingIndex = beginning + spaceNeeded;
    if(endingIndex > sizeOfTable)
        return true;

    //cout << "Beginning: " << beginningIndex << "\tEnd: " << endingIndex << endl;

    MemoryBlock* startingBlock = mainMemoryTable->getHeadBlockPtr();
    MemoryBlock* tempStartingBlock = NULL;
    while(startingBlock->getIndexNum() != beginning+1)
    {
        startingBlock = startingBlock->getDownPtr();
    }
    tempStartingBlock = startingBlock;

    MemoryBlock* endingBlock = startingBlock;
    MemoryBlock* tempEndingBlock = NULL;
    while(endingBlock->getIndexNum() != endingIndex)
    {
        endingBlock = endingBlock->getDownPtr();
    }
    tempEndingBlock = endingBlock;

    MemoryBlock *current = startingBlock;
    while(startingBlock != endingBlock)
    {
        if(startingBlock->getFreeSpace() != true)
        {
            firstFit(newProcess,mainMemoryTable,startingBlock->getDownPtr()->getIndexNum());
        }
        startingBlock = startingBlock->getDownPtr();
    }

    if(startingBlock == endingBlock && consecutive == true)
    {
        while(tempStartingBlock != tempEndingBlock)
        {
            tempStartingBlock->setFreeSpace(false);
            tempStartingBlock->setProcessName(newProcess->getProcessName());
            tempStartingBlock = tempStartingBlock->getDownPtr();
        }
      //  cout << "process added" << endl;
        return true;
    }
    else
    {
        cout << "process not added" << endl;
        return false;
    }



    /*
    cout << "Beginning: "

    //for(int i = 0; i < sizeOfTable; i++)
   // {
        //beginningIndex = sizeOfTable + 1;
        //endingIndex = sizeOfTable +1;
        for(int x = beginningIndex; x < sizeOfTable;x++)
        {
            if(traverseBlock->getFreeSpace() == true && (traverseBlock->getUpPtr() != mainMemoryTable->getHeadBlockPtr()
                || traverseBlock != mainMemoryTable->getTailBlockPtr()))
            {
                counter++;
                if(beginningIndex > sizeOfTable)
                {
                    beginningIndex = x;
                    counter++;
                }
                else if(endingIndex > sizeOfTable && (traverseBlock->getDownPtr() == NULL ||
                        traverseBlock->getDownPtr()->getFreeSpace() == false))
                {
                    if(counter == spaceNeeded)
                    {
                        counter++;
                        endingIndex = beginningIndex + counter;
                        spaceFound = true;
                        setBlocks(mainMemoryTable,newProcess,beginningIndex,endingIndex);
                        return spaceFound;
                    }
                }
                else
                {
                    counter++;
                    if(counter == spaceNeeded)
                    {
                        endingIndex = beginningIndex+counter;
                        spaceFound = true;
                        setBlocks(mainMemoryTable,newProcess,beginningIndex,endingIndex);
                        return spaceFound;
                    }
                }
                traverseBlock = traverseBlock->getDownPtr();
            }
        }
    //}

*/
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
            MemoryBlock* current = NULL;
            for(int i = beginningIndex; i <= endingIndex; i++)
            {
                current = mainMemoryTable->findMemoryBlockByIndex(i);
                current->setProcessName(newProcess->getProcessName());
                current->setFreeSpace(false);
                cout << current->getProcessName() << endl;
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


void PrintTable(string fileName,MemoryTable* mainMemoryTable)
{
    ofstream oFile;
    oFile.open(fileName.c_str());

    MemoryBlock* traverseBlock = mainMemoryTable->getHeadBlockPtr()->getDownPtr();
    for(int i = 0; i < mainMemoryTable->getSizeOfTable();i++)
    {
        oFile << traverseBlock->getIndexNum() << ": " << traverseBlock->getProcessName() << endl;
        oFile << "____________________________________________________________________" << endl;
        traverseBlock = traverseBlock->getDownPtr();
    }
}
