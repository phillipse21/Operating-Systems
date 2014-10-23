#ifndef Assignment2_H
#define Assignment2_H

#include "libraries.h"

class PCBStruct
{
    public:
        PCBStruct();
        void setProcessName(std::string name);
        void setAppOrSystem(char aOrS);
        void setPriority(int priority);
        void setRunningReadyBlocked(int state);
        void setSuspended(bool suspended);
        void setMemoryNeeded(int memoryNeeded);
        void setTimeRemaining(int timeRemaining);
        void setArrivalTime(int timeOfArrival);
        void setCpuPercentage(int percentage);
        void setNextPtr(PCBStruct *nextPtr);
        void setPrevPtr(PCBStruct *prevPtr);
        std::string getProcessName();
        char getAppOrSystem();
        int getPriority();
        int getRunningReadyBlocked();
        bool getSuspended();
        int getMemoryNeeded();
        int getTimeRemaining();
        int getArrivalTime();
        int getCpuPercentage();
        PCBStruct* getNextPtr();
        PCBStruct* getPrevPtr();
        ~PCBStruct();
    private:
        std::string processName;
        char appOrSystem;
        int priority;
        int runningReadyBlocked;
        bool suspended;
        int memoryNeeded;
        int timeRemaining;
        int arrivalTime;
        int cpuPercentage;
        PCBStruct* nextPtr;
        PCBStruct* prevPtr;
};

class PCBQueue
{
    public:
        PCBQueue();
        void findNumOfNodes();
        void setHeadNodePtr(PCBStruct *headNode);
        void setTailNodePtr(PCBStruct *tailNode);
        int getNumOfNodes();
        PCBStruct* getHeadNodePtr();
        PCBStruct* getTailNodePtr();
        PCBStruct* createNewPCB();
        void addNodeToBeginning();
        void addNodeToHead(PCBStruct* nodeToAdd);
        void addNodeBefore(PCBStruct* nodeToAdd, PCBStruct* newAfterNode);
        void addToEnd(PCBStruct* nodeToAdd);
    private:
        int numOfNodes;
        PCBStruct *headNodePtr;
        PCBStruct *tailNodePtr;
};




//find PCB before tailnode
//PCBStruct* findLastPCB(PCBStruct *headNode, PCBStruct *tailNode);

//add new node to headnode
//void addToBeginningOfList(PCBStruct *&headNode, PCBStruct *&tailNode);

//add new node to headnode
//void addToBeginningOfList(PCBStruct *&headNode, PCBStruct *&tailNode);

//create new node & returns pointer to new PCB
//PCBStruct* allocatePCB();

//Frees all memory associated with a PCB
//void freePCB(PCBStruct* nodeTODelete);

//SetupPCB
//void  setupPCB(string name,int priority,char appOrSystem,PCBQueue* blocked, PCBQueue* ready);

//searches all queues for PCB with a given name
PCBStruct* findSameName(PCBQueue* blocked, PCBQueue* ready, string name);

//inserts the given PCB pointer to the specified queue
//void insertPCB(PCBQueue* &blocked, PCBQueue* &ready, PCBStruct* newPCB);

//allocates and sets up a new PCB and inserts it into the ready queue
//void createPCB(PCBQueue* &ready,PCBQueue* &blocked);

//removes an existing PCB from its queue
//void deletePCB(PCBQueue* blocked,PCBQueue* ready);

//gets a PCB name from user and places PCB in blocked state
//moves PCB from ready queue into the blocked queue
//void block(PCBQueue* &blocked,PCBQueue* &ready);

//gets a PCB name from the user and places it to the ready state
//moves PCB from the blocked queue to the ready queue
//void unblock(PCBQueue* &blocked,PCBQueue* &ready);

//finds a PCB via user-entered process name and changes state to suspended
void suspend(PCBQueue* &blocked,PCBQueue* &ready);

//finds a PCB via user-entered process name and changes state to not suspended
void resume(PCBQueue* &blocked,PCBQueue* &ready);

//finds a PCB via user-entered process and changes priority to user-defined priority if valid
void setPriority(PCBQueue* &blocked,PCBQueue* &ready);

//shows information from a single PCB requested by user
void showPCB(PCBQueue* blocked,PCBQueue* ready);

//shows all PCBs from both queues
void showAll(PCBQueue* blocked,PCBQueue* ready);

//shows all PCBs in ready queue
//void showReady(PCBQueue* ready);

//shows all PCBs in blocked queue
void showOneQueue(PCBQueue* queueToPrint);

#endif // Assignment2_H
