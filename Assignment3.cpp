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

    system("CLS");

    PCBStruct* traversePtr = readyQueue->getHeadNodePtr()->getNextPtr();
    while(traversePtr->getNextPtr() != readyQueue->getTailNodePtr())
    {
        cout << traversePtr->getProcessName();
        cout << ":   " << traversePtr->getTimeRemaining() << endl;
        traversePtr = traversePtr->getNextPtr();
    }
    cout << endl << endl << endl;
    getchar();

    ReadytoRunning(readyQueue);
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

void ReadytoRunning(PCBQueue* &readyQueue)
{
    PCBStruct* traversePtr = readyQueue->getHeadNodePtr()->getNextPtr();
    PCBStruct* nextPtr = NULL;
    int timeCounter = traversePtr->getTimeRemaining();

    while(traversePtr != readyQueue->getTailNodePtr())
    {
        timeCounter = traversePtr->getTimeRemaining();
        for(int i = traversePtr->getTimeRemaining(); i > 0; i--)
        {
            timeCounter--;
            traversePtr->setTimeRemaining(timeCounter);
            Sleep(1000);
            printWithTimeRemaining(readyQueue);
        }
        nextPtr = traversePtr->getNextPtr();
        readyQueue->getHeadNodePtr()->setNextPtr(nextPtr);
        nextPtr->setPrevPtr(readyQueue->getHeadNodePtr());

        traversePtr->setNextPtr(NULL);
        traversePtr->setPrevPtr(NULL);
        traversePtr = nextPtr;
    }
}

void printWithTimeRemaining(PCBQueue* readyQueue)
{
    system("CLS");
    PCBStruct* traversePtr = readyQueue->getHeadNodePtr();
    while(traversePtr != readyQueue->getTailNodePtr())
    {
        cout << traversePtr->getProcessName() << ": "
             << traversePtr->getTimeRemaining() << endl;
        traversePtr = traversePtr->getNextPtr();
    }
}

void firstInFirstOut(PCBQueue* readyQueue,tm * &timeInfo,time_t initialTime)
{
    ofstream oFile;
    oFile.open("FIFO.txt");
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
    time_t enterHour;
    time_t enterMinute;
    time_t enterSecond;
    int timeChanging = 0;

    string fileName = "";

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

            //begin analyzing line
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

            enterHour = timeInfo->tm_hour; //programClock->getHour();
            enterMinute = timeInfo->tm_min; //programClock->getMinute();
            enterSecond = timeInfo->tm_sec; //programClock->getSecond();

            oFile << newPCB->getProcessName() << " entered system at: "
                  << enterHour << ":" << enterMinute << ":" << enterSecond << endl;

            //clear variables
            name = "";
            category = ' ';
            priority = 0;
            memory = 0;
            timeRemaining = 0;
            timeOfArrival = 0;
            CPUpercentage = 0;
            spaceCounter = 0;

            enterHour = timeInfo->tm_hour;
            enterMinute = timeInfo->tm_min;
            enterSecond = timeInfo->tm_sec;

            readyQueue->addToEnd(newPCB);
         }//end of while loop

        while(readyQueue->getHeadNodePtr()->getNextPtr() != readyQueue->getTailNodePtr())
        {
            ReadytoRunning(readyQueue);
            printWithTimeRemaining(readyQueue);

            //if process is finished
            if(readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining() == 0)
            {
                oFile << readyQueue->getHeadNodePtr()->getNextPtr()->getProcessName()
                      << " was completed at "
                      << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
                PCBStruct* newFirst = readyQueue->getHeadNodePtr()->getNextPtr()->getNextPtr();

                readyQueue->getHeadNodePtr()->getNextPtr()->setNextPtr(NULL);
                readyQueue->getHeadNodePtr()->getNextPtr()->setPrevPtr(NULL);

                newFirst->setPrevPtr(readyQueue->getHeadNodePtr());
                readyQueue->getHeadNodePtr()->setNextPtr(newFirst);
            }
        }
    }
}

void shortestTimeToCompletionFirst(PCBQueue* readyQueue,tm * &timeInfo,time_t initialTime)
{
    ofstream oFile;
    oFile.open("STCF.txt");
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
    time_t enterHour;
    time_t enterMinute;
    time_t enterSecond;
    int timeChanging = 0;

    string fileName = "";

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

            //begin analyzing line
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

            enterHour = timeInfo->tm_hour; //programClock->getHour();
            enterMinute = timeInfo->tm_min; //programClock->getMinute();
            enterSecond = timeInfo->tm_sec; //programClock->getSecond();

            oFile << newPCB->getProcessName() << " entered system at: "
                  << enterHour << ":" << enterMinute << ":" << enterSecond << endl;

            //clear variables
            name = "";
            category = ' ';
            priority = 0;
            memory = 0;
            timeRemaining = 0;
            timeOfArrival = 0;
            CPUpercentage = 0;
            spaceCounter = 0;

            enterHour = timeInfo->tm_hour;
            enterMinute = timeInfo->tm_min;
            enterSecond = timeInfo->tm_sec;

            whereToAddSTCF(readyQueue,newPCB,oFile,timeInfo,initialTime);

            //changing timeRemaining of firstProcess
            timeChanging = readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining();
            timeChanging--;
            readyQueue->getHeadNodePtr()->getNextPtr()->setTimeRemaining(timeChanging);
            Sleep(1000);

            //if process is finished
            if(readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining() == 0)
            {
                oFile << readyQueue->getHeadNodePtr()->getNextPtr()->getProcessName()
                      << " was completed at "
                      << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
                PCBStruct* newFirst = readyQueue->getHeadNodePtr()->getNextPtr()->getNextPtr();

                readyQueue->getHeadNodePtr()->getNextPtr()->setNextPtr(NULL);
                readyQueue->getHeadNodePtr()->getNextPtr()->setPrevPtr(NULL);

                newFirst->setPrevPtr(readyQueue->getHeadNodePtr());
                readyQueue->getHeadNodePtr()->setNextPtr(newFirst);
            }

            printWithTimeRemaining(readyQueue);
         }//end of while loop

        while(readyQueue->getHeadNodePtr()->getNextPtr() != readyQueue->getTailNodePtr())
        {
            ReadytoRunning(readyQueue);
            printWithTimeRemaining(readyQueue);
        }
    }
}

void whereToAddSTCF(PCBQueue* &readyQueue, PCBStruct* newPCB,ofstream &oFile,tm * &timeInfo,time_t initialTime)
{
    if(readyQueue->getHeadNodePtr()->getNextPtr() == readyQueue->getTailNodePtr())
    {
        newPCB->setRunningReadyBlocked(1);//running
        oFile << newPCB->getProcessName() << " began running at "
              << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
        readyQueue->addNodeToHead(newPCB);
        return;
    }
    else
    {
        //if incoming PCB takes less time than currently running PCB
        if(newPCB->getTimeRemaining() < readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining())
        {
            newPCB->setRunningReadyBlocked(1);//running
            readyQueue->getHeadNodePtr()->getNextPtr()->setRunningReadyBlocked(2);//ready

            oFile << newPCB->getProcessName() << " began running at "
                  << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;


            oFile << readyQueue->getHeadNodePtr()->getNextPtr()->getProcessName() << " became ready at "
                  << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;

            readyQueue->addNodeBefore(newPCB,readyQueue->getHeadNodePtr()->getNextPtr());
            return;
        }
        else
        {
            PCBStruct* traversePtr = readyQueue->getHeadNodePtr()->getNextPtr();
            while(newPCB->getTimeRemaining() > traversePtr->getTimeRemaining())
            {
                traversePtr = traversePtr->getNextPtr();
                if(traversePtr == readyQueue->getTailNodePtr())
                {
                    newPCB->setRunningReadyBlocked(2);//ready

                    oFile << newPCB->getProcessName() << " became ready at "
                          << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
                    readyQueue->addToEnd(newPCB);
                    return;
                }
            }
            newPCB->setRunningReadyBlocked(2);//ready

            oFile << newPCB->getProcessName() << " became ready at "
                  << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;

            readyQueue->addNodeBefore(newPCB,traversePtr);
            return;
        }
    }
}


void fixedPriorityPreEmptiveScheduling(PCBQueue* readyQueue,tm * &timeInfo, time_t initialTime)
{
    ofstream oFile;
    oFile.open("FPPS.txt");
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
    time_t enterHour;
    time_t enterMinute;
    time_t enterSecond;
    int timeChanging = 0;

    string fileName = "";

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

            //begin analyzing line
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

            enterHour = timeInfo->tm_hour; //programClock->getHour();
            enterMinute = timeInfo->tm_min; //programClock->getMinute();
            enterSecond = timeInfo->tm_sec; //programClock->getSecond();

            oFile << newPCB->getProcessName() << " entered system at: "
                  << enterHour << ":" << enterMinute << ":" << enterSecond << endl;

            //clear variables
            name = "";
            category = ' ';
            priority = 0;
            memory = 0;
            timeRemaining = 0;
            timeOfArrival = 0;
            CPUpercentage = 0;
            spaceCounter = 0;

            enterHour = timeInfo->tm_hour;
            enterMinute = timeInfo->tm_min;
            enterSecond = timeInfo->tm_sec;

            whereToAddFPPS(readyQueue,newPCB,oFile,timeInfo,initialTime);

            //changing timeRemaining of firstProcess
            timeChanging = readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining();
            timeChanging--;
            readyQueue->getHeadNodePtr()->getNextPtr()->setTimeRemaining(timeChanging);
            Sleep(1000);

            //if process is finished
            if(readyQueue->getHeadNodePtr()->getNextPtr()->getTimeRemaining() == 0)
            {
                oFile << readyQueue->getHeadNodePtr()->getNextPtr()->getProcessName()
                      << " was completed at "
                      << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
                PCBStruct* newFirst = readyQueue->getHeadNodePtr()->getNextPtr()->getNextPtr();

                readyQueue->getHeadNodePtr()->getNextPtr()->setNextPtr(NULL);
                readyQueue->getHeadNodePtr()->getNextPtr()->setPrevPtr(NULL);

                newFirst->setPrevPtr(readyQueue->getHeadNodePtr());
                readyQueue->getHeadNodePtr()->setNextPtr(newFirst);
            }

            printWithTimeRemaining(readyQueue);
         }//end of while loop

        while(readyQueue->getHeadNodePtr()->getNextPtr() != readyQueue->getTailNodePtr())
        {
            ReadytoRunning(readyQueue);
            printWithTimeRemaining(readyQueue);
        }
    }
}

void whereToAddFPPS(PCBQueue* &readyQueue, PCBStruct* newPCB,ofstream& oFile, tm * &timeInfo,time_t initialTime)
{
    if(readyQueue->getHeadNodePtr()->getNextPtr() == readyQueue->getTailNodePtr())
    {
        newPCB->setRunningReadyBlocked(1);//running
        oFile << newPCB->getProcessName() << " began running at "
              << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
        readyQueue->addNodeToHead(newPCB);
        return;
    }
    else
    {
        //if incoming PCB has higher priority than currently running PCB
        if(newPCB->getPriority() < readyQueue->getHeadNodePtr()->getNextPtr()->getPriority())
        {
            newPCB->setRunningReadyBlocked(1);//running
            readyQueue->getHeadNodePtr()->getNextPtr()->setRunningReadyBlocked(2);//ready

            oFile << newPCB->getProcessName() << " began running at "
                  << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;


            oFile << readyQueue->getHeadNodePtr()->getNextPtr()->getProcessName() << " became ready at "
                  << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;

            readyQueue->addNodeBefore(newPCB,readyQueue->getHeadNodePtr()->getNextPtr());
            return;
        }
        else
        {
            PCBStruct* traversePtr = readyQueue->getHeadNodePtr()->getNextPtr();
            while(newPCB->getPriority() > traversePtr->getPriority())
            {
                traversePtr = traversePtr->getNextPtr();
                if(traversePtr == readyQueue->getTailNodePtr())
                {
                    newPCB->setRunningReadyBlocked(2);//ready

                    oFile << newPCB->getProcessName() << " became ready at "
                          << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;
                    readyQueue->addToEnd(newPCB);
                    return;
                }
            }
            newPCB->setRunningReadyBlocked(2);//ready

            oFile << newPCB->getProcessName() << " became ready at "
                  << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << endl;

            readyQueue->addNodeBefore(newPCB,traversePtr);
            return;
        }
    }
}
