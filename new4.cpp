#include "libraries.h"

Spans::Spans(int beginning, int ending,bool freeOrTaken)
{
    this -> beginning = beginning;
    this -> ending = ending;
    this -> free = freeOrTaken;
    this -> name = "-";
}

void Spans::setBeginning(int beginning)
{
    this->beginning = beginning;
}

void Spans::setEnding(int ending)
{
    this->ending = ending;
}

void Spans::setName(string name)
{
    this ->name = name;
}

int Spans::getBeginning()
{
    return beginning;
}

int Spans::getEnding()
{
    return ending;
}

bool Spans::getFree()
{
    return free;
}

string Spans::getName()
{
    return name;
}

void showMemoryTable(PCBStruct* newProcess,vector <string> memoryTable,vector <Spans*> spanVector)
{/*
    int sizeOfTable = memoryTable.size();
    int sizeOfVector = spanVector.size();

    //make vector of taken spans
    vector <Spans*> takenVector;
    int beginning = -1;
    int ending = -1;
    bool Bfound = false;
    bool Efound = false;
    bool allFree = true;

    for(int i = 0; i < sizeOfTable; i++)
    {
        if(i == sizeOfTable-1 && allFree != true)
        {
            ending = sizeOfTable;
            Spans *newSpan = new Spans(beginning,ending,false);
            newSpan->setName(newProcess->getProcessName());
            spanVector.push_back(newSpan);
            Bfound = false;
            Efound = false;
        }
        else if(memoryTable[i] != "free" && Bfound == false)
        {
            beginning = i;
            Bfound = true;
        }
        else if(memoryTable[i] == "free" && Efound == false)
        {
            allFree = false;
            ending = i;
            Spans *newSpan = new Spans(beginning,ending,false);
            newSpan->setName(newProcess->getProcessName());
            spanVector.push_back(newSpan);
            Efound = false;
            Bfound = false;
        }
    }

    int sizeOfTakenVector = takenVector.size();

    cout << "size taken: " << sizeOfTakenVector << endl;

    vector <Spans*> printVector;

    Spans* currentFree = NULL;
    Spans* currentTaken = NULL;
    for(int b = 0; b < sizeOfVector; b++)
    {
        currentFree = spanVector[b];
        printVector.push_back(currentFree);
    }
    for(int c = sizeOfVector; c < (sizeOfVector+sizeOfTakenVector); c++)
    {
        currentFree = spanVector[c];
        printVector.push_back(currentFree);
    }

    organizeVector(printVector);

 //   sizeOfVector = printVector.size();
//    Spans *current = NULL;
    for(int i = 0; i < sizeOfVector; i++)
    {
        current = memoryTable[i];
        cout << current->getBeginning() << "-" << current->getEnding() << ": ";
        if(current->getFree() == false)
            cout << "\t" << current->getName() << endl;
        else
            cout << "free" << endl;
    }*/
    system("CLS");
    for(int i = 0; i < memoryTable.size();i++)
    {
        if(i == 0 || memoryTable[i] != memoryTable[i-1])
        {
            cout << i << "-";
        }
        else if(i == memoryTable.size()-1 || memoryTable[i] != memoryTable[i+1])
        {
            cout << i << ": " << memoryTable[i] << endl;
        }
    }
}

void organizeVector(vector <Spans*> vectorToOrganize)
{
    int sizeOfVector = vectorToOrganize.size();
    Spans* smaller = NULL;
    Spans* currentSpan = NULL;
    Spans* nextSpan = NULL;

    for(int i = 0; i < sizeOfVector; i++)
    {
        currentSpan = vectorToOrganize[i];
        nextSpan = vectorToOrganize[i];
        for(int x = 0; x < sizeOfVector; x++)
        {
            if(nextSpan->getBeginning() < currentSpan->getBeginning())
            {
                smaller = nextSpan;
                vectorToOrganize[x+1] = vectorToOrganize[x];
                vectorToOrganize[x] = smaller;
            }
        }
    }
}

void matchVectors(vector <string> &memoryTable, vector <Spans*> spansVector)
{
    int sizeOfTable = memoryTable.size();
    int sizeOfVector = spansVector.size();
    Spans* current = NULL;

    for(int i = 0; i < sizeOfVector; i++)
    {
        current = spansVector[i];
        for(int x = current->getBeginning(); x <= current->getEnding(); x++)
        {
            memoryTable[x] = current->getName();
        }
    }
}

void initializeMemoryTable(vector <string> &memoryTable)
{
    int sizeOfTable = 1024;

    for(int i = 0; i < sizeOfTable; i++)
    {
        memoryTable.push_back("free");
    }
}

void resetSpanVector(vector <Spans*> &spanVector)
{
    int sizeOfVector = spanVector.size();
    for(int i = sizeOfVector; i > 0; i--)
    {
        spanVector.pop_back();
    }
}

void removeFromMemoryTable(vector <string> &memoryTable, string processName)
{
    int sizeOfTable = memoryTable.size();
    for(int i = 0; i < sizeOfTable;i++)
    {
        if(memoryTable[i] == processName)
            memoryTable[i] = "free";
    }
}

void removeNULLsFromVector(vector <Spans*> spanVector)
{
    for(int i = 0; i < spanVector.size();i++)
    {
        if(spanVector[i] == NULL)
        {
            for(int x = i+1; x < spanVector.size();x++)
            {
                spanVector[x - 1] = spanVector[x];
            }
        }
    }
}

void findSpans(vector <string> &memoryTable,vector <Spans*> &spanVector)
{
    resetSpanVector(spanVector);

    int sizeofTable = memoryTable.size();
    int beginning = -1;
    int ending = -1;
    bool Bfound = false;
    bool Efound = false;
    bool allFree = true;

    for(int i = 0; i < sizeofTable; i++)
    {
        if(i == sizeofTable-1 && allFree == true)
        {
            ending = sizeofTable;
            Spans *newSpan = new Spans(beginning,ending,true);
            newSpan->setName("free");
            spanVector.push_back(newSpan);
            Bfound = false;
            Efound = false;
        }
        else if(memoryTable[i] == "free" && Bfound == false)
        {
            beginning = i;
            Bfound = true;
        }
        else if(memoryTable[i] != "free" && Efound == false)
        {
            allFree = false;
            ending = i-1;
            Spans *newSpan = new Spans(beginning,ending,false);
            newSpan->setName("free");
            spanVector.push_back(newSpan);
            Bfound = false;
            Efound = false;
        }
    }

    cout << "size: " << spanVector.size() << endl;
/*
    Spans* current = NULL;
    for(int x = 0; x < signed(spanVector.size());x++)
    {
        current = spanVector[x];
        cout << current->getName() << "\tBeginning: " << current->getBeginning() << "  Ending: " << current->getEnding() << endl;
    }*/
    Sleep(3000);
}

//joins contigious spans together
void coalescing(vector <Spans*> spansVector)
{
    int firstBeginning = 0;
    int firstEnding = 0;
    int secondBeginning = 0;
    int secondEnding = 0;

    Spans* current = NULL;
    Spans* next = NULL;
    for(int i = 0; i < spansVector.size();i++)
    {
        current = spansVector[i];
        next = spansVector[i+1];
        firstBeginning = current->getBeginning();
        firstEnding = current->getEnding();
        secondBeginning = next->getBeginning();
        secondEnding = next->getEnding();

        if(firstEnding+1 == secondBeginning)
        {
            spansVector[i] = NULL;
            spansVector[i+1] = NULL;

            Spans* newSpan = new Spans(firstBeginning,firstEnding,true);
            newSpan->setBeginning(firstBeginning);
            newSpan->setEnding(secondEnding);

            spansVector[i] = newSpan;
            removeNULLsFromVector(spansVector);
        }
    }

}

//joins all contiguious spans together at end of table
void condensing(vector <Spans*> spanVector, vector <string> memoryTable)
{
    coalescing(spanVector);
    int totalFreeSpaces = 0;
    int difference = 0;

    Spans* current = NULL;
    for(int i = 0; i < spanVector.size(); i++)
    {
        current = spanVector[i];
        difference = current->getEnding() - current->getBeginning() + 1;
        totalFreeSpaces = totalFreeSpaces + difference;
    }

    //move everything in memory table up if the address above it is free
    for(int a = 1; a < memoryTable.size();a++)
    {
        if(memoryTable[a-1] == "free")
        {
            memoryTable[a -1] = memoryTable[a];
            memoryTable[a] = "free";
        }
    }

    for(int b = memoryTable.size()-totalFreeSpaces; b < totalFreeSpaces; b++)
    {
        memoryTable[b] = "free";
    }

    Spans* newSpan = new Spans(memoryTable.size()-totalFreeSpaces,totalFreeSpaces,free);

    newSpan->setBeginning(memoryTable.size()-totalFreeSpaces);
    newSpan->setEnding(totalFreeSpaces);

    resetSpanVector(spanVector);

    spanVector.push_back(newSpan);
}

bool firstFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector)
{
    int spacesNeeded = newProcess->getMemoryNeeded();
    int sizeOfTable = memoryTable.size();
    int sizeOfVector = spanVector.size();
    int difference = 0;
    int range = 0;
    int counter = 0;

    Spans* currentSpan = NULL;
    for(int a = 0; a < sizeOfVector; a++)
    {
        currentSpan = spanVector[a];
        difference = currentSpan->getEnding() - currentSpan->getBeginning() + 1;
        range = currentSpan->getBeginning() + spacesNeeded;
      //  cout << "needed: " << spacesNeeded << "\tdifference: " << difference << endl;
        if(difference >= spacesNeeded)
        {
            counter = currentSpan->getBeginning();
            currentSpan->setName(newProcess->getProcessName());
            cout << "255" << endl;
            for(int i = currentSpan->getBeginning(); i < range; i++)
            {
                memoryTable[i] = newProcess->getProcessName();
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //cout << "259" << endl << endl << endl;
 //   showMemoryTable(newProcess,memoryTable,spanVector);

}

void nextFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector)
{
    findSpans(memoryTable,spanVector);

    int spacesNeeded = newProcess->getMemoryNeeded();
    int difference = 0;
    int range = 0;

    Spans* current = NULL;
    for(int i = 0; i < spanVector.size();i++)
    {
        current = spanVector[i];
        difference = current->getEnding() - current->getBeginning() + 1;
        if(difference >= spacesNeeded)
        {
            range = current->getBeginning() + spacesNeeded;
            for(int x = current->getBeginning(); x <= spacesNeeded; x++)
            {
                memoryTable[x] = newProcess->getProcessName();
            }
        }
    }

    findSpans(memoryTable,spanVector);
}

void compareSpacesNeededToSpan(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector)
{
    int spacesNeeded = newProcess->getMemoryNeeded();
    int spacesDifference = 0;
    int spacesInSpan = 0;
    vector<int> spacesDifferenceVector;

    Spans* current = NULL;
    for(int i = 0; i < spanVector.size();i++)
    {
        current = spanVector[i];
        spacesInSpan = current->getEnding() - current->getBeginning() + 1;
        if(spacesInSpan > spacesNeeded)
        {
            spacesDifference = spacesInSpan-spacesNeeded;
            spacesDifferenceVector.push_back(spacesDifference);
        }
        else
        {
            spacesDifferenceVector.push_back(-1);
        }
    }

    bestFit(newProcess,memoryTable,spanVector,spacesDifferenceVector);

    worstFit(newProcess,memoryTable,spanVector,spacesDifferenceVector);

}

void bestFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector, vector<int> differenceVector)
{
    int spacesNeeded = newProcess->getMemoryNeeded();
    int smallest = differenceVector[0];
    int range = 0;
    int index = 0;
    Spans* smallestSpan = NULL;

    for(int i = 1; i < differenceVector.size();i++)
    {
        if(differenceVector[i] < smallest)
            smallest = differenceVector[i];
            smallestSpan = spanVector[i];
            index = i;

    }

    range = smallestSpan->getBeginning() + spacesNeeded;

    for(int x = smallestSpan->getBeginning(); x < range; x++)
    {
        memoryTable[x] = newProcess->getProcessName();
    }
}

void worstFit(PCBStruct *newProcess,vector <string> &memoryTable,vector <Spans*> &spanVector, vector<int> differenceVector)
{
    int spacesNeeded = newProcess->getMemoryNeeded();
    int biggest = differenceVector[0];
    int range = 0;
    int index = 0;
    Spans* biggestSpan = NULL;

    for(int i = 1; i < differenceVector.size();i++)
    {
        if(differenceVector[i] > biggest)
            biggest = differenceVector[i];
            biggestSpan = spanVector[i];
            index = i;
    }

    range = biggestSpan->getBeginning() + spacesNeeded;

    for(int x = biggestSpan->getBeginning(); x < range; x++)
    {
        memoryTable[x] = newProcess->getProcessName();
    }
}

