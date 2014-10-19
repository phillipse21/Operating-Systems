#ifndef Assignment1_H
#define Assignment1_H

#include "libraries.h"


class timeAndDate
{
public:
    timeAndDate(time_t initialTime,tm * timeInfo);
    void setTime(int hour, int minute);
    void setFullDate(int day, int month, int year);
    void setHour(int hour);
    void setMinute(int minute);
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    void setSecond(int second);
    time_t getHour();
    time_t getMinute();
    time_t getDay();
    time_t getMonth();
    time_t getYear();
    time_t getSecond();
private:
    time_t date;
    time_t month;
    time_t year;
    time_t hour;
    time_t minute;
    time_t second;
};


//print welcome screen
void printWelcomeScreen();

//print opening menu
int printOpeningMenu(timeAndDate clock);

//increments variables from timeAndDate object if needed
void incrementTime(timeAndDate clock,tm * &timeInfo,time_t initialTime);

//prints time variables from timeAndDate object
void printTime(timeAndDate clock);

//prints date variables from timeAndDate object
void printDate(timeAndDate programClock);

//asks if user would like to manually set the time
void userSetTime(timeAndDate &programClock);

//asks if user would like to manually set the date
void userSetDate(timeAndDate &programClock);

//print out directory files
void printDirectoryFiles(timeAndDate &programClock);

//void print help window
void printHelpScreen(timeAndDate &programClock);

#endif
