#ifndef Assignment2_H
#define Assignment2_H

#include "libraries.h"

using namespace std;

class PCBStruct
{
    public:
        void setProcessName(string name);
        void setAppOrSystem(char aOrS);
        void setPriority(int priority);
        void setRunningReadyBlocked(int state);
        void setSuspended(bool suspended);
        void setMemoryNeeded(int memoryNeeded);
        void setNextPtr(PCBStruct *nextPtr);
        void setPrevPtr(PCBStruct *prevPtr);
        string getProcessName();
        char getAppOrSystem();
        int getPriority();
        int getRunningReadyBlocked();
        bool getSuspended();
        int getMemoryNeeded();
        PCBStruct* getNextPtr();
        PCBStruct* getPrevPtr();
    private:
        string processName;
        char appOrSystem;
        int priority;
        int runningReadyBlocked;
        bool suspended;
        int memoryNeeded;
        PCBStruct* nextPtr;
        PCBStruct* prevPtr;
};

class PCBQueue
{
    public:
        void findNumOfNodes();
        void setHeadNodePtr(PCBStruct *headNode);
        void setTailNodePtr(PCBStruct *tailNode);
        int getNumOfNodes();
        PCBStruct* getHeadNodePtr();
        PCBStruct* getTailNodePtr();
        void createNewPCB();
        void addNodeToBeginning();
    private:
        int numOfNodes;
        PCBStruct *headNodePtr;
        PCBStruct *tailNodePtr;
};


//create new node
PCBStruct* createNewPCB();

//find PCB before tailnode
PCBStruct* findLastPCB(PCBStruct *headNode, PCBStruct *tailNode);

//add new node to headnode
void addToBeginningOfList(PCBStruct *&headNode, PCBStruct *&tailNode);

//add new node to headnode
void addToBeginningOfList(PCBStruct *&headNode, PCBStruct *&tailNode)

#endif // Assignment2_H
