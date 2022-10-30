/* @Author
Student Name: 
Student ID : 
Date: 
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   
    /*
        YOUR CODE HEAR
    */
    this->mpNext = NULL;
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;         //process arriving time
    this->mProcessTime = processTime;
    this->remainingTime = processTime;          //process time kaç kere gpu yu kullancagı. reamining time buraya kopyalandı ve güncellenecek 
    this->startTime = -1;                       //default             
    this->endTime = -1;                         //default
}

ProcessRep::~ProcessRep()
{
}

ProcessRep* ProcessRep::getNext()
{
    /*
        YOUR CODE HEAR
    */
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    /*
        YOUR CODE HEAR
    */
    this->mpNext = next;
}

string ProcessRep::getProcessType()
{
    /*
        YOUR CODE HEAR
    */
    return this->mProcessType; 
}

void ProcessRep::setProcessType(string processType)
{
    /*
        YOUR CODE HEAR
    */
    this->mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    /*
        YOUR CODE HEAR
    */
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    /*
        YOUR CODE HEAR
    */
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    /*
        YOUR CODE HEAR
    */
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    /*
        YOUR CODE HEAR
    */
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    /*
        YOUR CODE HEAR
    */
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    /*
        YOUR CODE HEAR
    */
    this->mProcessTime = ProcessTime;
}