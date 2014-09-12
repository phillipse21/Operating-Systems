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

    printWelcomeScreen();

    timeAndDate programClock(initialTime,timeInfo);
    programClock.setMonth(programClock.getMonth()+1);
    programClock.setYear(programClock.getYear()+1900);

    //printTime(programClock);

    while(endProgram == false)
    {
        incrementTime(programClock,timeInfo,initialTime);
        printDate(programClock);
        printTime(programClock);

        userChoice = printOpeningMenu(programClock);
        if(userChoice == 1)
            userSetTime(programClock);
        else if(userChoice == 2)
            userSetDate(programClock);
        else if(userChoice == 3)
            printDirectoryFiles(programClock);
        else if(userChoice == 4)
            printHelpScreen(programClock);
        else if(userChoice == 5)
        {
            cout << "Are you sure you want to exit?" << endl
                 << "1 - Yes" << endl
                 << "2 - No" << endl;
            cin >> userChoice;

            if(userChoice != 1 && userChoice != 2)
            {
                cout << "Error 012: Please enter a 1 or 2" << endl;
                printOpeningMenu(programClock);
            }
            else if(userChoice == 2)
                printOpeningMenu(programClock);
            else
            {
                return 0;
            }
        }
        else
            printOpeningMenu(programClock);
    }


    return 0;
}
