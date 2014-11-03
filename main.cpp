#include "libraries.h"

using namespace std;

int main()
{
    bool endProgram = false;
    int userChoice = 0;
    vector <string> memoryTable;
    vector <Spans*> spanTable;
    initializeMemoryTable(memoryTable);

    time_t initialTime;
    struct tm * timeInfo;
    time(&initialTime);
    timeInfo = localtime(&initialTime);

    PCBQueue *readyQueue = new PCBQueue;
    readyQueue->getHeadNodePtr()->setRunningReadyBlocked(2);//ready
    readyQueue->getHeadNodePtr()->setSuspended(false);
    readyQueue->getTailNodePtr()->setRunningReadyBlocked(2);
    readyQueue->getTailNodePtr()->setSuspended(false);

    PCBQueue *blockedQueue = new PCBQueue;
    blockedQueue->getHeadNodePtr()->setRunningReadyBlocked(3);//blocked
    blockedQueue->getHeadNodePtr()->setSuspended(false);
    blockedQueue->getTailNodePtr()->setRunningReadyBlocked(3);
    blockedQueue->getTailNodePtr()->setSuspended(false);

    printWelcomeScreen();

    timeAndDate programClock(initialTime,timeInfo);
    programClock.setMonth(programClock.getMonth()+1);
    programClock.setYear(programClock.getYear()+1900);

//    MemoryTable* FirstFitTable = new MemoryTable;
  //  MemoryTable* NextFitTable = new MemoryTable;
   // MemoryTable* bestFitTable = new MemoryTable;
   // MemoryTable* worstFitTable = new MemoryTable;

    while(endProgram == false)
    {
        incrementTime(programClock,timeInfo,initialTime);
        printDate(programClock);
        printTime(programClock);

        userChoice = printOpeningMenu(programClock);
        switch(userChoice)
        {
            case(1)://set time
            {
                userSetTime(programClock);
                break;
            }
            case(2)://set calendar
            {
                userSetDate(programClock);
                break;
            }
            case(3)://print directory file
            {
                printDirectoryFiles(programClock);
                break;
            }
            case(4)://SJF
            {
                shortestJobFirst(readyQueue,memoryTable);//,FirstFitTable,NextFitTable,bestFitTable,worstFitTable);
//                createPCB(readyQueue,blockedQueue);
                break;
            }
            case(5)://FIFO
            {
                firstInFirstOut(readyQueue,timeInfo,initialTime,memoryTable,spanTable);//FirstFitTable,NextFitTable,bestFitTable,worstFitTable);
                break;
            }
            case(6)://STCF
            {
                shortestTimeToCompletionFirst(readyQueue,timeInfo,initialTime,memoryTable);//,FirstFitTable,NextFitTable,bestFitTable,worstFitTable);
                break;
            }
            case(7)://FPPS
            {
                fixedPriorityPreEmptiveScheduling(readyQueue,timeInfo,initialTime,memoryTable);//,FirstFitTable,NextFitTable,bestFitTable,worstFitTable);
                break;
            }
            case(8)://RR
            {
                //
                break;
            }
            case(9)://MLFQ
            {
                //
                break;
            }
            case(10)://LS
            {
                //
                break;
            }
            case(11)://suspend
            {
                suspend(blockedQueue,readyQueue);
                break;
            }
            case(12)://resume
            {
                resume(blockedQueue,readyQueue);
                break;
            }
            case(13)://set priority
            {
                setPriority(blockedQueue,readyQueue);
                break;
            }
            case(14)://show PCB
            {
                showPCB(blockedQueue,readyQueue);
                break;
            }
            case(15)://show all
            {
                showAll(blockedQueue,readyQueue);
                break;
            }
            case(16)://show ready
            {
                showOneQueue(readyQueue);
            }
            case(17)://show blocked
            {
                showOneQueue(blockedQueue);
                break;
            }
            case(18):
            {
                printHelpScreen(programClock);
                break;
            }
            case(19):
            {
                cout << "Are you sure you want to exit?" << endl
                 << "1 - Yes" << endl
                 << "2 - No" << endl;
                cin >> userChoice;

                if(userChoice != 1 && userChoice != 2)
                {
                    cout << "Error 012: Please enter a 1 or 2" << endl;
                    printOpeningMenu(programClock);
                    break;
                }
                else if(userChoice == 2)
                {
                    printOpeningMenu(programClock);
                    break;
                }
                else
                    return 0;
            }
        }

    }
    return 0;
}
