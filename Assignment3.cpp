#include "libraries.h"

void shortestJobFirst(PCBQueue* &readyQueue)
{
    string fileName = "";
    string line = "";
    vector <string> fileData;

//    cout << "Please enter a file name: ";
  //  cin >> fileName;

    ifstream iFile;
    iFile.open("sampleProcesses.txt");
    //iFile.open(fileName.c_str());

    if (iFile.fail())
    {
        cout << "Error 015: File not found" << endl;
        return;
    }
    else
    {
        while(!iFile.eof())
        {
            getline(iFile,line);
            fileData.push_back(line);
        }
        iFile.close();
    }
    fileDataToPCB(readyQueue,fileData);

}

void fileDataToPCB(PCBQueue* &readyQueue, vector <string> fileData)
{
    ofstream oFile;
    oFile.open("text.txt");
    int spaceCounter = 0;
    string line = "";
    string name = "";
    string numToConvert = "";
    char category = ' ';
    int priority = 0;
    int memory = 0;
    int timeRemaining = 0;
    int timeOfArrival = 0;
    int CPUpercentage = 0;

    for(int i = 0; i < fileData.size(); i++)
    {
        line = fileData[i];
        PCBStruct* newPCB = new PCBStruct;
        for(int x = 0; x < line.size(); x++)
        {
            if(spaceCounter == 0)//name
            {
                if(line[x] != ' ')
                {
                    name = name += line[x];
                }
                else if(line[x] == ' ')
                {
                    spaceCounter++;
                }
            }
            else if(spaceCounter == 1)//class
            {
                if(line[x] != ' ')
                {
                    category = line[x];
                }
                else if(line[x] == ' ')
                {
                    spaceCounter++;
                }
            }
            else if(spaceCounter == 2)//priority
            {
                if(line[x] != ' ')
                {
                    numToConvert = numToConvert += line[x];
                }
                else if(line[x] == ' ')
                {
                    istringstream buffer(numToConvert);
                    buffer >> priority;
                    spaceCounter++;
                    numToConvert = "";
                }
            }
            else if(spaceCounter == 3)//memory
            {
                if(line[x] != ' ')
                {
                    numToConvert = numToConvert += line[x];
                }
                else if(line[x] == ' ')
                {
                    istringstream buffer(numToConvert);
                    buffer >> memory;
                    spaceCounter++;
                    numToConvert = "";
                }
            }
            else if(spaceCounter ==4)//time remaining
            {
                if(line[x] != ' ')
                {
                    numToConvert = numToConvert += line[x];
                }
                else if(line[x] == ' ')
                {
                    istringstream buffer(numToConvert);
                    buffer >> timeRemaining;
                    spaceCounter++;
                    numToConvert = "";
                }
            }
            else if(spaceCounter == 5)//time of arrival
            {
                if(line[x] != ' ')
                {
                    numToConvert = numToConvert += line[x];
                }
                else if(line[x] == ' ')
                {
                    istringstream buffer(numToConvert);
                    buffer >> timeOfArrival;
                    spaceCounter++;
                    numToConvert = "";
                }
            }
            else//percentage of cpu
            {
                if(x != line.size())
                {
                    numToConvert = numToConvert += line[x];
                    istringstream buffer(numToConvert);
                    buffer >> CPUpercentage;
                    numToConvert = "";
                }
            }
        }
        newPCB->setProcessName(name);
        newPCB->setAppOrSystem(category);
        newPCB->setPriority(priority);
        newPCB->setMemoryNeeded(memory);
        newPCB->setTimeRemaining(timeRemaining);
        newPCB->setArrivalTime(timeOfArrival);
        newPCB->setCpuPercentage(CPUpercentage);

        name = "";
        category = ' ';
        priority = 0;
        memory = 0;
        timeRemaining = 0;
        timeOfArrival = 0;
        CPUpercentage = 0;
        spaceCounter = 0;

        if(readyQueue->getHeadNodePtr()->getNextPtr() != readyQueue->getTailNodePtr())
        {
            orderedInsert(readyQueue,newPCB);
        }
        else
        {
            readyQueue->addNodeToHead(newPCB);
        }
    }

    PCBStruct* traversePtr = readyQueue->getHeadNodePtr()->getNextPtr();
    while(traversePtr->getNextPtr() != readyQueue->getTailNodePtr())
    {
        oFile << traversePtr->getProcessName();
        oFile << ":   " << traversePtr->getTimeRemaining() << endl;
        traversePtr = traversePtr->getNextPtr();
    }
}


void intTimeRemaining(vector <int> &timeRemainingVector)
{
    int smaller = 0;
    int vectorSize = timeRemainingVector.size();

    for(int i = 0; i < vectorSize; i++)
    {
        for(int x = 0; x < vectorSize; x++)
        {
            if(timeRemainingVector[x+1] < timeRemainingVector[x])
            {
                smaller = timeRemainingVector[x+1];
                timeRemainingVector[x+1] = timeRemainingVector[x];
                timeRemainingVector[x] = smaller;
            }
        }
    }
}

void orderedInsert(PCBQueue* &readyQueue, PCBStruct* &newPCB)
{
    if(newPCB->getTimeRemaining() <= readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining())
    {
        readyQueue->addNodeToHead(newPCB);
        return;
    }
    else
    {
        PCBStruct* traversePtr = readyQueue->getHeadNodePtr()->getNextPtr();
        while(traversePtr->getNextPtr() != readyQueue->getTailNodePtr() ||
              traversePtr->getTimeRemaining() > newPCB->getTimeRemaining())
        {
            traversePtr = traversePtr->getNextPtr();
            if(traversePtr = readyQueue->getTailNodePtr())
            {
                readyQueue->addToEnd(newPCB);
                return;
            }
        }
        if(newPCB->getTimeRemaining() <= traversePtr->getTimeRemaining())
        {
            readyQueue->addNodeBefore(newPCB,traversePtr);
        }
    }
}
