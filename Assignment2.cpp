#include "libraries.h"

//constructor
PCBStruct::PCBStruct()
{
    processName = "";
    appOrSystem =' ';
    priority = -128;
    runningReadyBlocked = 3;
    suspended = true;
    memoryNeeded = -1;

}

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

//set time remaining
void PCBStruct::setTimeRemaining(int timeRemaining)
{
    this -> timeRemaining = timeRemaining;
}

//set arrival time
void PCBStruct::setArrivalTime(int timeOfArrival)
{
    this -> arrivalTime = timeOfArrival;
}

//set CPU percentage
void PCBStruct::setCpuPercentage(int percentage)
{
    this->cpuPercentage = percentage;
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

//return time remaining
int PCBStruct::getTimeRemaining()
{
    return timeRemaining;
}

//return arrival time
int PCBStruct::getArrivalTime()
{
    return arrivalTime;
}

//return cpu percentage
int PCBStruct::getCpuPercentage()
{
    return cpuPercentage;
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

PCBStruct::~PCBStruct()
{
    processName = "";
    appOrSystem = ' ';
    priority = 0;
    runningReadyBlocked = 0;
    suspended = false;
    memoryNeeded = 0;
    nextPtr = NULL;
    prevPtr = NULL;
}

//constructor
PCBQueue::PCBQueue()
{
    headNodePtr = new PCBStruct;
    tailNodePtr = new PCBStruct;


    tailNodePtr->setProcessName("");
    tailNodePtr->setAppOrSystem(' ');
    tailNodePtr->setPriority(-128);
    tailNodePtr->setRunningReadyBlocked(3);
    tailNodePtr->setSuspended(true);
    tailNodePtr->setMemoryNeeded(-1);

    headNodePtr->setProcessName("");
    headNodePtr->setAppOrSystem(' ');
    headNodePtr->setPriority(-128);
    headNodePtr->setRunningReadyBlocked(3);
    headNodePtr->setSuspended(true);
    headNodePtr->setMemoryNeeded(-1);

    headNodePtr->setNextPtr(tailNodePtr);
    tailNodePtr->setPrevPtr(headNodePtr);

    numOfNodes = 0;

}


//traverses through list and increments numOfNodes
void PCBQueue::findNumOfNodes()
{
    PCBStruct* traversePtr = headNodePtr;

    while(traversePtr->getNextPtr() != tailNodePtr)
    {
        if(traversePtr != headNodePtr && traversePtr != tailNodePtr)
            numOfNodes++;

        traversePtr = traversePtr->getNextPtr();
    }
}

//set headNodeValues
void PCBQueue::setHeadNodePtr(PCBStruct *headNode)
{
    headNodePtr = headNode;
   /* headNode->setProcessName("");
    headNode->setAppOrSystem(' ');
    headNode->setPriority(-128);
    headNode->setRunningReadyBlocked(3);
    headNode->setSuspended(true);
    headNode->setMemoryNeeded(-1);*/
}

//set tailNodeValue
void PCBQueue::setTailNodePtr(PCBStruct *tailNode)
{
    tailNodePtr = tailNode;
    /*tailNodePtr->setProcessName("");
    tailNodePtr->setAppOrSystem(' ');
    tailNodePtr->setPriority(-128);
    tailNodePtr->setRunningReadyBlocked(3);
    tailNodePtr->setSuspended(true);
    tailNodePtr->setMemoryNeeded(-1);*/
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
PCBStruct* PCBQueue::createNewPCB()
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
    return newPCB;
}

//add new node after headNode
void PCBQueue::addNodeToBeginning()
{
    PCBStruct *oldFirstPCB = headNodePtr->getNextPtr();
    PCBStruct *oldNextPtr = oldFirstPCB->getNextPtr();
    PCBStruct *newFirstNode = createNewPCB();

    headNodePtr->setNextPtr(newFirstNode);
    newFirstNode->setPrevPtr(headNodePtr);

    newFirstNode->setNextPtr(oldFirstPCB);
    oldFirstPCB->setPrevPtr(newFirstNode);

}

void PCBQueue::addNodeToHead(PCBStruct* nodeToAdd)
{
    PCBStruct* oldFirst = headNodePtr->getNextPtr();

    nodeToAdd->setNextPtr(oldFirst);
    nodeToAdd->setPrevPtr(headNodePtr);

    headNodePtr->setNextPtr(nodeToAdd);
    oldFirst->setPrevPtr(nodeToAdd);
}

void PCBQueue::addNodeBefore(PCBStruct* nodeToAdd, PCBStruct* newAfterNode)
{
    PCBStruct* oldPrev = newAfterNode->getPrevPtr();

    newAfterNode->setPrevPtr(nodeToAdd);
    oldPrev->setNextPtr(nodeToAdd);

    nodeToAdd->setNextPtr(newAfterNode);
    nodeToAdd->setPrevPtr(oldPrev);
}

void PCBQueue::addToEnd(PCBStruct* nodeToAdd)
{
    PCBStruct* oldLast = tailNodePtr->getPrevPtr();

    oldLast->setNextPtr(nodeToAdd);
    tailNodePtr->setPrevPtr(nodeToAdd);

    nodeToAdd->setNextPtr(tailNodePtr);
    nodeToAdd->setPrevPtr(oldLast);
}
/*

//create new node & returns pointer to new PCB
PCBStruct* allocatePCB()
{
    PCBStruct* newNode = new PCBStruct;

    if(newNode->getPriority() != -128 || newNode->getAppOrSystem() != ' ' ||
      newNode->getProcessName() != "" || newNode->getRunningReadyBlocked() != 3 ||
      newNode->getSuspended() != true || newNode->getMemoryNeeded() != -1)
    {
        cout << "Error 13: Failure to create new PCB" << endl;
    }
    else
        return newNode;
}


//Frees all memory associated with a PCB
void freePCB(PCBStruct* nodeTODelete)
{
    nodeTODelete->~PCBStruct();
}

//SetupPCB
void  setupPCB(string name,int priority,char appOrSystem,PCBQueue* blocked, PCBQueue* suspended)
{
    bool sameName = findSameName(blocked,suspended,name);

    if(sameName = false)
    {
        PCBStruct* newPCB = allocatePCB();

        if(newPCB == NULL)
        {
            newPCB = new PCBStruct;
        }

        newPCB->setProcessName(name);
        newPCB->setPriority(priority);
        newPCB->setAppOrSystem(appOrSystem);
        newPCB->setSuspended(false);
    }
    else
        return;


}
*/
//searches all queues and all states to find the PCB with that name
PCBStruct* findSameName(PCBQueue* blocked, PCBQueue* ready, string name)
{
    PCBStruct* traversePtr = blocked->getHeadNodePtr();
    PCBStruct* secondTraversePtr = ready->getHeadNodePtr();
    int sizeOfBlocked = blocked->getNumOfNodes();
    int sizeofReady = ready->getNumOfNodes();

    if(sizeOfBlocked > sizeofReady)
    {
        while(traversePtr->getNextPtr() != NULL)
        {
            if(secondTraversePtr->getNextPtr() != NULL)
            {
                if(secondTraversePtr->getProcessName() == name)
                    return secondTraversePtr;
                else
                    secondTraversePtr = secondTraversePtr->getNextPtr();
            }

            if(traversePtr->getProcessName() == name)
                return traversePtr;
            else
                traversePtr = traversePtr->getNextPtr();
        }
        if(traversePtr->getNextPtr() == NULL)
            return NULL;
    }
    else if(sizeOfBlocked < sizeofReady)
    {
        while(secondTraversePtr->getNextPtr() != NULL)
        {
            if(traversePtr->getNextPtr() != NULL)
            {
                if(traversePtr->getProcessName() == name)
                    return traversePtr;
                else
                    traversePtr = traversePtr->getNextPtr();
            }

            if(secondTraversePtr->getProcessName() == name)
                return secondTraversePtr;
            else
                secondTraversePtr = secondTraversePtr->getNextPtr();
        }
        if(secondTraversePtr->getNextPtr() == NULL)
            return NULL;
    }
    else
    {
        while(traversePtr->getNextPtr() != NULL && secondTraversePtr->getNextPtr() != NULL)
        {
            if(traversePtr->getProcessName() == name)
                return traversePtr;
            else if(secondTraversePtr->getProcessName() == name)
                return secondTraversePtr;
            else
                traversePtr = traversePtr->getNextPtr();
                secondTraversePtr = secondTraversePtr->getNextPtr();
        }

        return NULL;

    }
}
/*
//inserts the given PCB pointer to the specified queue
void insertPCB(PCBQueue* &blocked, PCBQueue* &ready, PCBStruct* newPCB)
{
    if(newPCB->getSuspended() == false)
    {
        PCBStruct* oldLast = blocked->getTailNodePtr()->getPrevPtr();
        oldLast->setNextPtr(newPCB);
        blocked->getTailNodePtr()->setPrevPtr(newPCB);

        newPCB->setNextPtr(blocked->getTailNodePtr());
        newPCB->setPrevPtr(oldLast);

        return;
    }
    else
    {
       PCBStruct* oldLast = ready->getTailNodePtr()->getPrevPtr();
       oldLast->setNextPtr(newPCB);
       ready->getTailNodePtr()->setPrevPtr(newPCB);

       newPCB->setNextPtr(ready->getTailNodePtr());
       newPCB->setPrevPtr(oldLast);

       return;
    }
}

//removes PCB from the queue it's in
void removePCB(PCBStruct* nodeToRemove,PCBQueue* &blocked, PCBQueue* &ready)
{
    string nameToFind = nodeToRemove->getProcessName();
    nodeToRemove = findSameName(blocked,ready,nameToFind);

    if(nodeToRemove != NULL)
    {
        PCBStruct* newNext = nodeToRemove->getNextPtr();
        PCBStruct* newPrev = nodeToRemove->getPrevPtr();

        nodeToRemove->setNextPtr(NULL);
        nodeToRemove->setPrevPtr(NULL);

        newPrev->setNextPtr(newNext);
        newNext->setPrevPtr(newPrev);

        return;
    }
    else
    {
        cout << "Error 15: The specified PCB is not in list." << endl;
        return;
    }
}

//allocates and sets up a new PCB and inserts it into the ready queue
void createPCB(PCBQueue* &ready, PCBQueue* &blocked)
{
    PCBStruct* PCBtoAdd = new PCBStruct;
    PCBStruct* oldLast = ready->getTailNodePtr()->getPrevPtr();

    string name;
    int newPriority = 0;
    char category = ' ';

    cout << "Please enter the process name of the new PCB: ";
    cin >> name;

    PCBStruct* sameName = findSameName(ready,blocked,name);
    if(sameName != NULL)
    {
        cout << "Error 014: There is already a process in that name" << endl;
        createPCB(ready,blocked);
    }

    cout << "Please enter the priority of the new PCB: ";
    cin >> newPriority;
    cout << "Please enter a for Application or s for System: ";
    cin >> category;

    cout << endl;

    PCBtoAdd->setProcessName(name);

    if(newPriority < -127 || newPriority > 128)
    {
        cout << "Error 019: Invalid priority value." << endl;
        createPCB(ready,blocked);
    }
    else
    {
        PCBtoAdd->setPriority(newPriority);
    }

    if(category != 'a' && category != 's' && category != 'S' && category != 'A')
    {
        cout << "Error 020: Invalid class value." << endl;
        createPCB(ready,blocked);
    }
    else
    {
        PCBtoAdd->setAppOrSystem(category);
    }

    PCBtoAdd->setSuspended(false);
    PCBtoAdd->setRunningReadyBlocked(1);

    cout << PCBtoAdd->getProcessName() << " now has a priority of " << PCBtoAdd->getPriority() << endl;
    cout << PCBtoAdd->getProcessName() << " now has a class of ";
    if(PCBtoAdd->getAppOrSystem() == 'a')
    {
        cout << "Application" << endl;
    }
    else
        cout << "System." << endl;


    PCBtoAdd->setNextPtr(ready->getTailNodePtr());
    PCBtoAdd->setPrevPtr(oldLast);

    if(oldLast == ready->getHeadNodePtr())
    {
        ready->getHeadNodePtr()->setNextPtr(PCBtoAdd);
        ready->getTailNodePtr()->setPrevPtr(PCBtoAdd);
    }
    else
    {
        oldLast->setNextPtr(PCBtoAdd);
        ready->getTailNodePtr()->setPrevPtr(PCBtoAdd);
    }
}

//removes an existing PCB from its queue
void deletePCB(PCBQueue* blocked,PCBQueue* ready)
{
    string userInput;
    int newPriority = 0;
    cout << "Please enter the process name of the PCB you want to change: ";
    cin >>userInput;

    PCBStruct* PCBtoChange = findSameName(blocked,ready,userInput);

    if(PCBtoChange->getPriority() == -128)
    {
        cout << "Error 018: There is no process with that name.";
        deletePCB(blocked,ready);
    }
    else
    {
        removePCB(PCBtoChange,blocked,ready);

        if(PCBtoChange->getPrevPtr() == NULL && PCBtoChange->getNextPtr() == NULL)
        {
            cout << PCBtoChange->getProcessName() << " has been removed from queue. " << endl;
        }
        freePCB(PCBtoChange);
    }


}

//gets a PCB name from user and places PCB in blocked state
//moves PCB from ready queue into the blocked queue
void block(PCBQueue* &blocked,PCBQueue* &ready)
{
    string userInput;
    int newPriority = 0;
    cout << "Please enter the process name of the PCB you want to change: ";
    cin >>userInput;

    PCBStruct* PCBtoChange = findSameName(blocked,ready,userInput);

    if(PCBtoChange == NULL)
    {
        cout << "Error 018: There is no process with that name.";
        block(blocked,ready);
    }
    else
    {
        removePCB(PCBtoChange,blocked,ready);
        insertPCB(blocked,ready,PCBtoChange);
        PCBtoChange->setRunningReadyBlocked(2);
        cout << PCBtoChange->getProcessName() << "has been moved from the ready queue into the blocked queue";
    }
}

//gets a PCB name from the user and places it to the ready state
//moves PCB from the blocked queue to the ready queue
void unblock(PCBQueue* &blocked,PCBQueue* &ready)
{
    string userInput;
    int newPriority = 0;
    cout << "Please enter the process name of the PCB you want to change: ";
    cin >>userInput;

    PCBStruct* PCBtoChange = findSameName(blocked,ready,userInput);

    if(PCBtoChange == NULL)
    {
        cout << "Error 018: There is no process with that name.";
        unblock(blocked,ready);
    }
    else
    {
        removePCB(PCBtoChange,blocked,ready);
        insertPCB(blocked,ready,PCBtoChange);
        PCBtoChange->setRunningReadyBlocked(1);
        cout << PCBtoChange->getProcessName() << "has been moved from the blocked queue into the ready queue";
    }
}


*/
//finds a PCB via user-entered process name and changes state to suspended
void suspend(PCBQueue* &blocked,PCBQueue* &ready)
{
    string userInput;
    int newPriority = 0;
    cout << "Please enter the process name of the PCB you want to change: ";
    cin >>userInput;

    PCBStruct* PCBtoChange = findSameName(blocked,ready,userInput);

    if(PCBtoChange == NULL)
    {
        cout << "Error 018: There is no process with that name.";
        suspend(blocked,ready);
    }
    else
    {
        PCBtoChange->setSuspended(true);
        cout << PCBtoChange->getProcessName() <<  " state is now ";
        if(PCBtoChange->getSuspended() == true)
            cout << "suspended" << endl;
    }
}

//finds a PCB via user-entered process name and changes state to not suspended
void resume(PCBQueue* &blocked,PCBQueue* &ready)
{
    string userInput;
    int newPriority = 0;
    cout << "Please enter the process name of the PCB you want to change: ";
    cin >>userInput;

    PCBStruct* PCBtoChange = findSameName(blocked,ready,userInput);

    if(PCBtoChange == NULL)
    {
        cout << "Error 018: There is no process with that name.";
        resume(blocked,ready);
    }
    else
    {
        PCBtoChange->setSuspended(false);
        cout << PCBtoChange->getProcessName() <<  " state is now ";
        if(PCBtoChange->getSuspended() == false)
            cout << "not suspended" << endl;
    }


}

//finds a PCB via user-entered process and changes priority to user-defined priority if valid
void setPriority(PCBQueue* &blocked,PCBQueue* &ready)
{
    string userInput;
    int newPriority = 0;
    cout << "Please enter the process name of the PCB you want to change: ";
    cin >>userInput;

    PCBStruct* PCBtoChange = findSameName(blocked,ready,userInput);

    if(PCBtoChange == NULL)
    {
        cout << "Error 018: There is no process with that name.";
        setPriority(blocked,ready);
    }
    else
    {
        cout << "What would you like to set the priority to: ";
        cin >> newPriority;

        if(newPriority < -127 || newPriority > 128)
        {
            cout << "Error 019: Invalid priority value." << endl;
            setPriority(blocked,ready);
        }
        else
        {
            PCBtoChange->setPriority(newPriority);
            cout << PCBtoChange->getProcessName() << " now has a priority of " << PCBtoChange->getPriority() << endl << endl;
        }
    }

}

//shows information from a single PCB requested by user
void showPCB(PCBQueue* blocked,PCBQueue* ready)
{
    string userInput = "";
    cout << "Please enter the process name of the PCB you would like to find: ";
    cin >> userInput;

    PCBStruct* ifFound = findSameName(blocked,ready,userInput);

    if(ifFound == NULL)
    {
        cout << "Error 018: There is no process with that name in this queue" << endl;
    }
    else
    {
        cout << "PCB:" << endl
             << "Process Name - " << ifFound->getProcessName() << endl
             << "Class - ";

        if(ifFound->getAppOrSystem() == 'a')
            cout << "Application" << endl;
        else
            cout << "System" << endl;

        cout << "Priority - " << ifFound->getPriority() << endl;
        cout << "Running/Ready/Blocked - ";

        if(ifFound->getRunningReadyBlocked() == 0)
            cout << "Running" << endl;
        else if(ifFound->getRunningReadyBlocked() == 1)
            cout << "Ready" << endl;
        else
            cout << "Blocked" << endl;

        cout << "Memory - " << ifFound->getMemoryNeeded() << endl;
    }
}


//shows all PCBs from both queues
void showAll(PCBQueue* blocked,PCBQueue* ready)
{
    PCBStruct* blockedTraverse = blocked->getHeadNodePtr()->getNextPtr();
    PCBStruct* readyTraverse = ready->getHeadNodePtr()->getNextPtr();
    blocked->findNumOfNodes();
    ready->findNumOfNodes();
    int blockedSize = blocked->getNumOfNodes();
    int readySize = ready->getNumOfNodes();
    int counter = 1;

    if(blockedSize == 0)
    {
        cout << "The blockedQueue is empty." << endl;
    }
    if(readySize == 0)
    {
        cout << "The readyQueue is empty." << endl;
    }

    while(blockedTraverse != blocked->getTailNodePtr())
    {
        cout << "PCB:" << endl
             << "Process Name - " << blockedTraverse->getProcessName() << endl
             << "Class - ";

        if(blockedTraverse->getAppOrSystem() == 'a')
            cout << "Application" << endl;
        else
            cout << "System" << endl;

        cout << "Priority - " << blockedTraverse->getPriority() << endl;
        cout << "Running/Ready/Blocked - ";

        if(blockedTraverse->getRunningReadyBlocked() == 0)
            cout << "Running" << endl;
        else if(blockedTraverse->getRunningReadyBlocked() == 1)
            cout << "Ready" << endl;
        else
            cout << "Blocked" << endl;

        cout << "Memory - " << blockedTraverse->getMemoryNeeded() << endl;

        blockedTraverse = blockedTraverse->getNextPtr();
    }
    while(readyTraverse != ready->getTailNodePtr())
    {
        cout << "PCB:" << endl
             << "Process Name - " << readyTraverse->getProcessName() << endl
             << "Class - ";

        if(readyTraverse->getAppOrSystem() == 'a')
            cout << "Application" << endl;
        else
            cout << "System" << endl;

        cout << "Priority - " << readyTraverse->getPriority() << endl;
        cout << "Running/Ready/Blocked - ";

        if(readyTraverse->getRunningReadyBlocked() == 0)
            cout << "Running" << endl;
        else if(readyTraverse->getRunningReadyBlocked() == 1)
            cout << "Ready" << endl;
        else
            cout << "Blocked" << endl;

        cout << "Memory - " << readyTraverse->getMemoryNeeded() << endl;

        readyTraverse = readyTraverse->getNextPtr();
    }

}

void showOneQueue(PCBQueue* queueToPrint)
{
    PCBStruct* traverseNode = queueToPrint->getHeadNodePtr()->getNextPtr();
    while(traverseNode != queueToPrint->getTailNodePtr())
    {
        cout << "PCB:" << endl
             << "Process Name - " << traverseNode->getProcessName() << endl
             << "Class - ";

        if(traverseNode->getAppOrSystem() == 'a')
            cout << "Application" << endl;
        else
            cout << "System" << endl;

        cout << "Priority - " << traverseNode->getPriority() << endl;
        cout << "Running/Ready/Blocked - ";

        if(traverseNode->getRunningReadyBlocked() == 0)
            cout << "Running" << endl;
        else if(traverseNode->getRunningReadyBlocked() == 1)
            cout << "Ready" << endl;
        else
            cout << "Blocked" << endl;

        cout << "Memory - " << traverseNode->getMemoryNeeded() << endl;

        traverseNode = traverseNode->getNextPtr();
    }
}
