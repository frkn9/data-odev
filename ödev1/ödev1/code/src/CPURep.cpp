/* @Author
Student Name: 
Student ID : 
Date: 
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    /*
        YOUR CODE HEAR
    */
    mFinishedProcess = new FIFORep;
}

CPURep::~CPURep()
{
    while(mFinishedProcess->getHead() != NULL) {
        delete mFinishedProcess->dequeue();
    }
    delete mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    /*
        YOUR CODE HEAR
    */

    //Pushes mpRunningProcess to mFinishedProcess when remainingTime is zero. endTime had to be 
    //incremented because main.cpp executes printProcess before executing schedule 
    p->remainingTime -= 1;
        if(p->remainingTime == 0) {
            p->endTime = ++time;    
            mFinishedProcess->queue(p);
            return NULL;
        } 
    
    return NULL;
}

FIFORep* CPURep::getFinishedProcess()
{
    /*
        YOUR CODE HEAR
    */
    return mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    /*
        YOUR CODE HEAR
    */
    mFinishedProcess = finishedProcess;
}