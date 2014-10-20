#include "libraries.h"

timeAndDate::timeAndDate(time_t initialTime,tm * timeInfo)
{
    date = timeInfo->tm_mday;
    month = timeInfo->tm_mon;
    year = timeInfo->tm_year;
    hour = timeInfo->tm_hour;
    minute = timeInfo->tm_min;
    second = timeInfo->tm_sec;

    if(hour > 12)
        hour = hour - 12;

    mktime(timeInfo);
}

//set full time
void timeAndDate::setTime(int hour, int minute)
{
    this -> hour = hour;
    this -> minute = minute;
}

//set full date
void timeAndDate::setFullDate(int day, int month, int year)
{
    this -> date = day;
    this -> month = month;
    this -> year = year;
}

//set hour
void timeAndDate::setHour(int hour)
{
    this -> hour = hour;
}

//set minute
void timeAndDate::setMinute(int minute)
{
    this -> minute = minute;
}

//set day
void timeAndDate::setDay(int day)
{
    this -> date = day;
}

//set month
void timeAndDate::setMonth(int month)
{
    this -> month = month;
}

//set year
void timeAndDate::setYear(int year)
{
    this -> year = year;
}

void timeAndDate::setSecond(int second)
{
    this -> second = second;
}

//return hour
time_t timeAndDate::getHour()
{
    return hour;
}

//return minute
time_t timeAndDate::getMinute()
{
    return minute;
}

//return day
time_t timeAndDate::getDay()
{
    return date;
}

//return month
time_t timeAndDate::getMonth()
{
    return month;
}

//return year
time_t timeAndDate::getYear()
{
    return year;
}

time_t timeAndDate::getSecond()
{
    return second;
}


//print welcome screen
void printWelcomeScreen()
{
    cout << "Welcome to" << endl
         << " Sygyzy" << endl
         << "  0.1  " << endl << endl
         << "Press enter to continue" << endl;

    getchar();
    system("CLS");
}

//print opening menu
int printOpeningMenu(timeAndDate clock)
{
    //printTime(clock);

    //system("CLS");
    int userChoice = 0;

    cout << "Select an option below by entering the corresponding number" << endl
         << "1 - Change time" << endl
         << "2 - Change date" << endl
         << "3 - Print directories" << endl
         << "4 - SJF" << endl
         << "5 - FIFO" << endl
         << "6 - STCF" << endl
         << "7 - FPPS" << endl
         << "8 - RR" << endl
         << "9 - MLFQ" << endl
         << "10 - Lottery Scheduling" << endl
       //  << "4 - Suspend" << endl
        // << "5 - Resume" << endl
        // << "6 - Set priority" << endl
      //   << "7 - Show PCB" << endl
    //     << "8 - Show all" << endl
  //       << "9 - Show ready" << endl
//         << "10 - Show blocked" << endl
         << "11 - Help" << endl
         << "12 - Exit" << endl;
    cin >> userChoice;

    if(userChoice < 1 || userChoice > 12)
    {
        cout << "Error 016: Please select 1,2,3,4,5,6,7,8,9,10,11,12" << endl;
        printOpeningMenu(clock);
    }
    else
        return userChoice;
}

//increments variables from timeAndDate object if needed
void incrementTime(timeAndDate clock,tm * &timeInfo,time_t initialTime)
{
    time(&initialTime);
    timeInfo = localtime(&initialTime);
    clock.setMinute(timeInfo->tm_min);
    clock.setHour(timeInfo->tm_hour);
    clock.setDay(timeInfo->tm_hour);
    clock.setMonth(timeInfo->tm_mon);
    clock.setYear(timeInfo->tm_year);
    clock.setSecond(timeInfo->tm_sec);

}
//prints time variables from timeAndDate object
void printTime(timeAndDate clock)
{
    if(clock.getHour() > 12)
        clock.setHour(clock.getHour()-12);


    if(clock.getMinute() > 9)
    {
        cout << clock.getHour() << ":" << clock.getMinute() << ":" << clock.getSecond() << endl;
    }
    else
    {
       cout << clock.getHour() << ":0" << clock.getMinute() << ":" << clock.getSecond() << endl;
    }
}

//prints date variables from timeAndDate object
void printDate(timeAndDate programClock)
{
    cout << programClock.getMonth() << "/" << programClock.getDay() << "/" << programClock.getYear() << endl;
}

//asks if user would like to manually set the time
void userSetTime(timeAndDate &programClock)
{
    int userChoice = 0;
    int userHour = 0;
    int userMin = 0;

    cout << "Would you like to reset the whole clock,the hour, or the minutes?" << endl
         << "1 - whole clock" << endl
         << "2 - hour" << endl
         << "3 - minutes ";
    cin >> userChoice;
    cout << endl;

    if(userChoice != 1 && userChoice != 2 && userChoice != 3)
    {
        cout << endl << "Error 003: Please select 1,2, or 3" << endl;
        userSetTime(programClock);
    }

    switch(userChoice)
    {
        case(1):
        {
            cout << "What would you like to set the hour to? ";
            cin >> userHour;
            cout << endl;

            if(userHour <= 0 || userHour > 12)
            {
                cout << endl << "Error 001: Hour cannot be set to any number less than 1 or greater than 12" << endl;
                userSetTime(programClock);
            }
            else
            {
                programClock.setHour(userHour);
            }

            cout << "What would you like to set the minutes to? ";
            cin >> userMin;
            cout << endl;

            if(userMin > 59)
            {
                cout << endl << "Error 002: Minutes cannot be set to any number less than 0 or greater than 59" << endl;
                userSetTime(programClock);
            }
            else
            {
                programClock.setMinute(userMin);
                break;
            }
            break;
        }
        case(2):
        {
            cout << "What would you like to set the hour to? ";
            cin >> userHour;
            cout << endl;

            if(userHour <= 0 || userHour > 12)
            {
                cout << endl << "Error 001: Hour cannot be set to any number less than 1 or greater than 12" << endl;
                userSetTime(programClock);
            }
            else
            {
                programClock.setHour(userHour);
                break;
            }
            break;
        }
        case(3):
        {
            cout << "What would you like to set the minutes to? ";
            cin >> userMin;
            cout << endl;

            if(userMin > 59)
            {
                cout << endl << "Error 002: Minutes cannot be set to any number less than 0 or greater than 59" << endl;
                userSetTime(programClock);
            }
            else
            {
                programClock.setMinute(userMin);
                break;
            }
            break;
        }
        break;
    }

    return;
}

//asks if user would like to manually set the date
void userSetDate(timeAndDate &programClock)
{
    int userChoice = 0;
    int userDay = 0;
    int userMonth = 0;
    int userYear = 0;
    bool leapYear = false;

    //determine if year is a leap year
    if(programClock.getYear() % 4 == 0)
    {
        if(programClock.getYear() % 400 == 0 && programClock.getYear() % 100 == 0)
        {
            leapYear = false;
        }
        else
        {
            leapYear = true;
        }
    }
    else
    {
        leapYear = false;
    }

    cout << "Would you like to set the day, the month, the year, or all three? " << endl
         << "1 - day" << endl
         << "2 - month" << endl
         << "3 - year" << endl;
         //<< "4 - day,month,and year ";
    cin >> userChoice;
    cout << endl;

    if(userChoice != 1 && userChoice != 2 && userChoice != 3)// && userChoice != 4)
    {
        cout << endl << "Error 004: Value cannot equal anything other than 1,2,3" << endl;//, or 4" << endl;
        userSetDate(programClock);
        return;
    }
    else
    {
        switch(userChoice)
        {
            case(1):
            {
                cout << "What would you like to set the day to? ";
                cin >> userDay;
                cout << endl;

                if(userDay < 1)
                {
                    cout << endl << "Error 006: Date cannot be less than 1" << endl;
                    userSetDate(programClock);
                    return;
                }

                if(leapYear == true && programClock.getMonth() == 2 && userDay > 29)
                {
                    cout << endl << "Error 005: According to the month and year the calendar is currently set to" << endl
                         << "           it is February and a leap year. If this is true the date cannot be greater than 29" << endl;
                    userSetDate(programClock);
                    return;
                }
                else if(leapYear == false && programClock.getMonth() == 2 && userDay > 28)
                {
                    cout << endl << "Error 007: According to the month the calendar is currently set to it is February." << endl
                         << "           If this is true the date cannot be greater than 28" << endl;
                    userSetDate(programClock);
                    return;
                }

                if(userDay > 30)
                {
                    if(programClock.getMonth() == 9 || programClock.getMonth() == 4 ||
                    programClock.getMonth() == 6 || programClock.getMinute() == 11)
                    {
                        cout << endl << "Error 008: The month the calendar is currently set to only has 30 days." << endl;
                        userSetDate(programClock);
                        return;
                    }
                    else
                    {
                        if(userDay > 31)
                        {
                            cout << endl << "Error 009: The month the calender is currently set to only has 31 days. " << endl;
                            userSetDate(programClock);
                            return;
                        }
                        else
                        {
                            programClock.setDay(userDay);
                            break;
                        }
                    }
                }
                else
                {
                    programClock.setDay(userDay);
                }
            break;
        }

            case(2):
            {
                cout << "What would you like to set the month to? " << endl
                     << "1 - January" << endl
                     << "2 - February " << endl
                     << "3 - March" << endl
                     << "4 - April" << endl
                     << "5 - May" << endl
                     << "6 - June" << endl
                     << "7 - July" << endl
                     << "8 - August" << endl
                     << "9 - September" << endl
                     << "10 - October" << endl
                     << "11 - November" << endl
                     << "12 - December " << endl;
                cin >> userMonth;
                cout << endl;

                if(userMonth < 1 || userMonth > 12)
                {
                    cout << endl << "Error 010: Month cannot be set to any number not between 1 and 12" << endl;
                    userSetDate(programClock);
                    return;
                }
                else
                {
                    switch(userMonth)
                    {
                        case(1):
                        {
                            programClock.setMonth(1);
                            break;
                        }
                        case(2):
                        {
                            programClock.setMonth(2);
                            if(leapYear == false && programClock.getDay()==29)
                            {
                                cout << "February(2) only has 28 days this year. Changing date to 28..." << endl;
                                programClock.setDay(28);
                                break;
                            }
                            break;

                        }
                        case(3):
                        {
                            programClock.setMonth(3);
                            break;
                        }
                        case(4):
                        {
                            programClock.setMonth(4);
                            if(programClock.getDay() > 30)
                            {
                                cout << "April(4) only has 30 days. Changing date to 30..." << endl;
                                programClock.setDay(30);
                                break;
                            }
                            break;

                        }
                        case(5):
                        {
                            programClock.setMonth(5);
                            break;
                        }
                        case(6):
                        {
                            programClock.setMonth(6);
                            if(programClock.getDay() > 30)
                            {
                                cout << "June(6) only has 30 days. Changing date to 30..." << endl;
                                programClock.setDay(30);
                                break;
                            }
                            break;

                        }
                        case(7):
                        {
                            programClock.setMonth(7);
                            break;
                        }
                        case(8):
                        {
                            programClock.setMonth(8);
                            break;
                        }
                        case(9):
                        {
                            programClock.setMonth(9);
                            if(programClock.getDay() > 30)
                            {
                                cout << "September(9) only has 30 days. Changing date to 30..." << endl;
                                programClock.setDay(30);
                                break;
                            }
                            break;
                        }
                        case(10):
                        {
                            programClock.setMonth(10);
                            break;
                        }
                        case(11):
                        {
                            programClock.setMonth(11);
                            if(programClock.getDay() > 30)
                            {
                                cout << "November(11) only has 30 days. Changing date to 30..." << endl;
                                programClock.setDay(30);
                                break;
                            }
                            break;

                        }
                        case(12):
                        {
                            programClock.setMonth(12);
                            break;
                        }
                    }
                }
                break;
            }
            case(3):
            {
                cout << "What would you like to set year to? ";
                cin >> userYear;
                cout << endl;

                if(userYear < 0)
                {
                    cout << endl << "Error 011: Year cannot be negative" << endl;
                    userSetDate(programClock);
                    return;
                }
                else
                {
                    programClock.setYear(userYear);

                    //determine if year is a leap year
                    if(programClock.getYear() % 4 == 0)
                    {
                        if(programClock.getYear() % 400 == 0 && programClock.getYear() % 100 == 0)
                        {
                            leapYear = false;
                        }
                        else
                        {
                            leapYear = true;
                        }
                    }
                    else
                    {
                        leapYear = false;
                    }

                    if(leapYear == false && programClock.getMonth() == 2 && programClock.getDay() == 29)
                    {
                        cout << "This year is not a leap year. Changing day to 28..." << endl;
                        programClock.setDay(28);
                        break;
                    }
                    break;
                }
            }
            break;
        }
    }// end of main else
}

//print out directory files
void printDirectoryFiles(timeAndDate &programClock)
{
    //const string PATH = "C:\Users\Ashley\Documents\Data Structures";

    DIR *directPtr;
    struct dirent *entry;

    if(directPtr = opendir("C:\\Users\\Ashley\\Documents\\Data Structures\\Sygyzy0.1"))
    {
        while(entry = readdir(directPtr))
        {
            cout << entry->d_name << endl;
        }
        closedir(directPtr);
    }

    cout << endl << endl;
    cout << "Press enter to return to main menu" << endl;
    getchar();
    printOpeningMenu(programClock);
}

//void print help window
void printHelpScreen(timeAndDate &programClock)
{
    system("CLS");

    int userChoice = 0;

    cout << "Select the command you need help with by entering the corresponding number" << endl
         << "1 - Changing the time" << endl
         << "2 - Changing the date" << endl
         << "3 - Printing the files in the directory" << endl
         //<< "4 - CreatePCB " << endl
         //<< "5 - DeletePCB" << endl
         //<< "6 - Block" << endl
         //<< "7 - Unblock" << endl
         << "4 - Suspend" << endl
         << "5 - Resume" << endl
         << "6 - Set priority" << endl
         << "7 - Show PCB" << endl
         << "8 - Show all" << endl
         << "9 - Show ready" << endl
         << "10 - Show blocked" << endl
         << "11 - Back to main menu ";
    cin >> userChoice;

    if(userChoice < 1 || userChoice > 16)
    {
        cout << "Error 017: Value cannot equal anything other than 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15" << endl;
        printHelpScreen(programClock);
    }
    else
    {
        switch(userChoice)
        {
            case(1):
            {
                cout << "This command can be used if the time shown at the top of the menu " << endl
                 << "is not correct. Option 1 is selected if both the hour and minutes " << endl
                 << "displayed are incorrect, option 2 is selected if only the hour is " << endl
                 << "incorrect, and option 3 is selected if the minutes are incorrect " << endl
                 << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                break;
            }
            case(2):
            {
                cout << "This command is to be used if the date shown at the top of the menu " << endl
                 << "is not correct. Option 1 is selected if only the day needs to be changed, " << endl
                 << "option 2 is selected if only the month needs to be changed, option 3 is " << endl
                 << "selected if only the year needs to be changed, and option 4 is selected if" << endl
                 << "all aspects of the date need to be changed." << endl
                 << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                break;
            }
            case(3):
            {
                cout << "This command prints the name of all files used by this program to the screen " << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            /*
            case(4)://create PCB
            {
                cout << "This command allocates and assigns a new PCB with the user specified name, " << endl
                     << "class,and priority." << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(5)://delete PCB
            {
                cout << "This command allows the user to enter a process name of a PCB they wish to delete" << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;
                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(6)://Block
            {
                cout << "This command allows the user to enter the process name of a desired PCB and move it from the" << endl
                     << "ready queue and putting it in the blocked queue" << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;

            }
            case(7)://unblock
            {
                cout << "Allows the user to enter the name of a desired PCB and move it from the blocked queue and into " << endl
                     << "the ready queue." << endl
                     << "  Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                {
                    printHelpScreen(programClock);
                    break;
                }
                break;
            }
            */
            case(4)://suspend
            {
                cout << "This command allows the user to enter a process name of a desired PCB and puts said PCB into " << endl
                     << "a suspended state." << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(5)://resume
            {
                cout << "This command allows the user to change a PCB's state from suspended to not suspended." << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(6)://set priority
            {
                cout << "This command allows the user to enter a selected PCB's process name and set a new priority." << endl
                     << "The new priority must be within the range of -127 to +128." << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(7)://show PCB
            {
                cout << "This command prints all information from a user defined PCB." << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                {
                    printHelpScreen(programClock);
                    break;
                }
                break;
            }
            case(8)://show all
            {
                cout << "This command prints all information for every PCB in every list" << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(9)://show ready
            {
                cout << "This command prints all information for every PCB in the ready queue" << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                    break;
                break;
            }
            case(10)://show blocked
            {
                cout << "This command prints all information for every PCB in the blocked list" << endl
                     << "                          Enter 0 to return to previous screen" << endl;
                cin >> userChoice;

                if(userChoice == 0)
                    printHelpScreen(programClock);
                //    break;
                break;
            }
            case(11):
            {
                system("CLS");
                printOpeningMenu(programClock);
                break;
            }
        }
    }
}
