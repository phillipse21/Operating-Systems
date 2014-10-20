#include "libraries.h"

using namespace std;

int main()
{
    bool endProgram = false;
    int userChoice = 0;

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
            case(4)://create PCB
            {
                shortestJobFirst(readyQueue);
//                createPCB(readyQueue,blockedQueue);
                break;
            }
            case(5)://delete PCB
            {
       //         deletePCB(blockedQueue,readyQueue);
                break;
            }
            case(6)://Block
            {
         //       block(blockedQueue,readyQueue);
                break;
            }
            case(7)://unblock
            {
           //     unblock(blockedQueue,readyQueue);
                break;
            }
            case(8)://suspend
            {
                suspend(blockedQueue,readyQueue);
                break;
            }
            case(9)://resume
            {
                resume(blockedQueue,readyQueue);
                break;
            }
            case(10)://set priority
            {
                setPriority(blockedQueue,readyQueue);
                break;
            }
            case(11)://show PCB
            {
                showPCB(blockedQueue,readyQueue);
                break;
            }
            case(12)://show all
            {
                showAll(blockedQueue,readyQueue);
                break;
            }
            case(13)://show ready
            {
                showBlocked(readyQueue);
            }
            case(14)://show blocked
            {
                showBlocked(blockedQueue);
                break;
            }
            case(15):
            {
                printHelpScreen(programClock);
                break;
            }
            case(16):
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
