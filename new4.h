#ifndef new4_H
#define new4_H

#include "libraries.h"

class Spans
{
    public:
        Spans(int beginning, int ending, bool freeOrTaken);
        void setBeginning(int beginning);
        void setEnding(int ending);
        void setName(string name);
        int getBeginning();
        int getEnding();
        bool getFree();
        string getName();
    private:
        string name;
        bool free;
        int beginning;
        int ending;
};

void showMemoryTable(PCBStruct *newProcess,vector <string> memoryTable,vector <Spans*> spanVector);

void organizeVector(vector <Spans*> vectorToOrganize);

void matchVectors(vector <string> &memoryTable, vector <Spans*> spansVector);

void initializeMemoryTable(vector <string> &memoryTable);

void resetSpanVector(vector <Spans*> &spanVector);

void removeNULLsFromVector(vector <Spans*> spanVector);

void findSpans(vector <string> &memoryTable, vector <Spans*> &SpansVector);

//joins contigious spans together
void coalescing(vector <Spans> &spansVector);

//joins all contiguious spans together at end of table
void condensing(vector <Spans> &spanVector);

void compareSpacesNeededToSpan(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector);

bool firstFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector);

void nextFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector);

void bestFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector, vector<int> differenceVector);

void worstFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector, vector<int> differenceVector);

#endif
