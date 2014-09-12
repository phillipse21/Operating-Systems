#include "libraries.h"

using namespace std;

//set process name
void PCBStruct::setProcessName(string name)
{
    this -> processName = name;
}

//set appOrSystem
void PCBStruct::setAppOrSystem(char aOrS)
{
    this -> appOrSystem = aOrS;
}

//set priority
void PCBStruct::setPriority(int priority)
{
    this -> priority = priority;
}

//set runningReadyBlocked
void PCBStruct::setRunningReadyBlocked(int state)
{
    this -> runningReadyBlocked = state;
}

//set suspended
void PCBStruct::setSuspended(bool suspended)
{
    this ->suspended = suspended;
}

//set memoryNeeded
void PCBStruct::setMemoryNeeded(int memoryNeeded)
{
    this -> memoryNeeded = memoryNeeded;
}

//set nextPtr
void PCBStruct::setNextPtr(PCBStruct *nextPtr)
{
    this -> nextPtr = nextPtr;
}

//set prevPtr
void PCBStruct::setPrevPtr(PCBStruct *prevPtr)
{
    this -> prevPtr = prevPtr;
}

//get process name
string PCBStruct::getProcessName()
{
    return processName;
}

//get appOrSystem
char PCBStruct::getAppOrSystem()
{
    return appOrSystem;
}

//get priority
int PCBStruct::getPriority()
{
    return priority;
}

//get runningReadyBlocked
int PCBStruct::getRunningReadyBlocked()
{
    return runningReadyBlocked;
}

//get suspended
bool PCBStruct::getSuspended()
{
    return suspended;
}

//get memoryNeeded
int PCBStruct::getMemoryNeeded()
{
    return memoryNeeded;
}

//return nextPtr
PCBStruct* PCBStruct::getNextPtr()
{
    return nextPtr;
}

//return prevPtr
PCBStruct* PCBStruct::getPrevPtr()
{
    return prevPtr;
}

//traverses through list and increments numOfNodes
void PCBQueue::findNumOfNodes()
{
    PCBStruct* traversePtr = headNodePtr;

    while(traversePtr->nextPtr() != NULL)
    {
        if(traversePtr != headNodePtr && traversePtr != tailNodePtr)
            numOfNodes++;

        traversePtr = traversePtr->nextPtr
    }
}

//set headNodeValues
void PCBQueue::setHeadNodePtr(PCBStruct *headNode)
{
    headNode->setProcessName("");
    headNode->setAppOrSystem(' ');
    headNode->setPriority(-128);
    headNode->setRunningReadyBlocked(3);
    headNode->setSuspended(true);
    headNode->setMemoryNeeded(-1);
}

//set tailNodeValue
void PCBQueue::setTailNodePtr(PCBStruct *tailNode)
{
    tailNodePtr->setProcessName("");
    tailNodePtr->setAppOrSystem(' ');
    tailNodePtr->setPriority(-128);
    tailNodePtr->setRunningReadyBlocked(3);
    tailNodePtr->setSuspended(true);
    tailNodePtr->setMemoryNeeded(-1);
}

//return numOfNodes
int PCBQueue::getNumOfNodes()
{
    return numOfNodes;
}

//return headNodePtr
PCBStruct* PCBQueue::getHeadNodePtr()
{
    return headNodePtr;
}

//return tailNodePtr
PCBStruct* PCBQueue::getTailNodePtr()
{
    return tailNodePtr;
}

//create new PCB
void PCBQueue::createNewPCB()
{
    PCBStruct *newPCB = new PCBStruct;
    newPCB->setProcessName("");
    newPCB->setAppOrSystem(' ');
    newPCB->setPriority(-128);
    newPCB->setRunningReadyBlocked(-1);
    newPCB->setSuspended(false);
    newPCB->setMemoryNeeded(-1);
    newPCB->setNextPtr(NULL);
    newPCB->setPrevPtr(NULL);
}

//add new node after headNode
void PCBQueue::addNodeToBeginning()
{
    PCBStruct *oldFirstPCB = headNode->getNextPtr();
    PCBStruct *oldNextPtr = oldFirstPCB->getNextPtr();
    PCBStruct *newFirstNode = createNewPCB();

    headNode->setNextPtr(newFirstNode);
    newFirstNode->setPrevPtr(headNode);

    newFirstNode->setNextPtr(oldFirstPCB);
    oldFirstPCB->setPrevPtr(newFirstNode);

}

