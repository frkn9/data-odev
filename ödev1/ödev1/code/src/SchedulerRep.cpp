/* @Author
Student Name: 
Student ID : 
Date: 
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
/*
    YOUR CODE HEAR
*/
    for(int i = 0; i < 3; i++) {
        this->mpProcessFIFO[i] = new FIFORep;
    }
    pCpuObj = new CPURep;
    totalTime = 0;
    mpRunningProcess = NULL;
    timeSliceCount = -1;
}
SchedulerRep::~SchedulerRep()
{
    for(int i = 0; i < 3; i++) {
        while(mpProcessFIFO[i]->getHead() != NULL) {
            delete mpProcessFIFO[i]->dequeue();
        }
    }
    delete pCpuObj;
}

FIFORep* SchedulerRep::getProcessFIFO(int index)
{
/*
    YOUR CODE HEAR
*/
    return mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
/*
    YOUR CODE HEAR
*/
    mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
/*
    YOUR CODE HEAR
*/
    mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
/*
    YOUR CODE HEAR
*/
    return mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
/*
    YOUR CODE HEAR
*/
    
    if(p->getProcessType() == "A") {
        mpProcessFIFO[0]->queue(p);
    }
    else if(p->getProcessType() == "B") {
        mpProcessFIFO[1]->queue(p);
    }
    else if(p->getProcessType() == "C") {
        mpProcessFIFO[2]->queue(p);
    }

    return;
}

ProcessRep* SchedulerRep::popProcess()
{
/*
    YOUR CODE HEAR
*/
    if(mpProcessFIFO[0]->getHead() != NULL)                      
        return mpProcessFIFO[0]->dequeue();
    else if(mpProcessFIFO[1]->getHead() != NULL)
        return mpProcessFIFO[1]->dequeue();
    else if(mpProcessFIFO[2]->getHead() != NULL)
        return mpProcessFIFO[2]->dequeue();
    
    return NULL;        

}

bool SchedulerRep::checkTimeSlice()
{   
/*
    YOUR CODE HEAR
*/
    if(timeSliceCount == 0)
        return true;
    else 
        return false;

}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
/*
    YOUR CODE HEAR
*/
    pCpuObj->runCPU(p, totalTime);
    return p;
}
void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.


    */
    /*
        YOUR CODE HEAR
    */

    ProcessRep* v = new ProcessRep(type, id, arrivalTime, processTime);
//when new job has arrived immediately push to the mpProcessFIFO    
    pushProcess(v);             
    

       
    if(totalTime == 0) {                                        //Runs on the first cycle of the program and never runs again. 
        mpRunningProcess = popProcess();                        //Immediately pop new job and assign mpRunningProcess to it

        if(mpRunningProcess->startTime == -1)  {
                mpRunningProcess->startTime = totalTime;        //Since default starttime and end time are -1. if the mpRunningProcess
            }                                                   //has never been run, assign its starttime the current totaltime.
        
        if(mpRunningProcess->getProcessType() == "A") {     
                timeSliceCount = 2;                             //if process type is A, timeSliceCount is 2, if B, 4, if C, 8 
        }                                                       //so they only run their respective amount of times before  
        else if(mpRunningProcess->getProcessType() == "B") {    //getting pushed back to the waiting list
            timeSliceCount = 4;
        }
        else if(mpRunningProcess->getProcessType() == "C") {
            timeSliceCount = 8;
        }

        pCpuObj->runCPU(mpRunningProcess, totalTime);
        timeSliceCount--;                                   
        totalTime++;                                            //decrease time slice count and increase totaltime by 1 
        return;                                                 //immediately after running the cpu
    }
    
//For when a job has completed.                   
    if(mpRunningProcess->remainingTime == 0) {                           

        mpRunningProcess = popProcess();
        

        if(mpRunningProcess->startTime == -1)  {
            mpRunningProcess->startTime = totalTime;
        }

        if(mpRunningProcess->getProcessType() == "A") {         //
            timeSliceCount = 2;                                 //
        }                                                       //
        else if(mpRunningProcess->getProcessType() == "B") {    //this chunk of code is seen repeatedly on the program and only 
            timeSliceCount = 4;                                 //executes when the mpRunningProcess has just changed.
        }                                                       //
        else if(mpRunningProcess->getProcessType() == "C") {    //
            timeSliceCount = 8;
        }

        pCpuObj->runCPU(mpRunningProcess, totalTime);
        timeSliceCount--;
        totalTime++;
        return;
    }

//For when the quantum time drops to zero    
//Pushing newly arrived job first so FIFO will return it first.   
    if(timeSliceCount == 0) {                               
        pushProcess(mpRunningProcess);                      
        mpRunningProcess = popProcess();

//If the newly popped mpRunningProcess has never been run, assign its startTime the current totalTime
        if(mpRunningProcess->startTime == -1) {             
            mpRunningProcess->startTime = totalTime;        
        }

        if(mpRunningProcess->getProcessType() == "A") {
            timeSliceCount = 2;
        }
        else if(mpRunningProcess->getProcessType() == "B") {
            timeSliceCount = 4;
        }
        else if(mpRunningProcess->getProcessType() == "C") {
            timeSliceCount = 8;
        }

        pCpuObj->runCPU(mpRunningProcess, totalTime);
        timeSliceCount--;
        totalTime++;
        return;
    }
    

//If for example new job's process type is B, its ascii value will be 66 and mpRunningProcess's process ype is C,     
//its ascii value will be 67. This code checks if the newly arrived job's letter 
//has a lower ascii number, and if it does changes the mpRunningProcess   
    if(v->getProcessType()[0] < mpRunningProcess->getProcessType()[0]) {    
        pushProcess(mpRunningProcess);                                       
        mpRunningProcess = popProcess();                                    
                                                                           
        if(mpRunningProcess->startTime == -1) {                       
            mpRunningProcess->startTime = totalTime;                     
        }                                                             
                                                                                

        if(mpRunningProcess->getProcessType() == "A") {
            timeSliceCount = 2;
        }
        else if(mpRunningProcess->getProcessType() == "B") {
            timeSliceCount = 4;
        }
        else if(mpRunningProcess->getProcessType() == "C") {
            timeSliceCount = 8;
        }

        pCpuObj->runCPU(mpRunningProcess, totalTime);
        timeSliceCount--;
        totalTime++;
        return;
    }


//Just executes the job if mpRunningProcess is not to be changed.                       
    pCpuObj->runCPU(mpRunningProcess, totalTime);           
    timeSliceCount--;
    totalTime++;

//I had to write this part since the main function runs PrintProcess before running schedule and 
//in some cases mpRunningProcess has to be updated one cycle earlier than normal
    if(mpRunningProcess->remainingTime == 0) {               
                                                            
        mpRunningProcess = popProcess();                    

        if(mpRunningProcess->startTime == -1)  {
            mpRunningProcess->startTime = totalTime;
        }

        
        if(mpRunningProcess->getProcessType() == "A") {
            timeSliceCount = 2;
        }
        else if(mpRunningProcess->getProcessType() == "B") {
            timeSliceCount = 4;
        }
        else if(mpRunningProcess->getProcessType() == "C") {
            timeSliceCount = 8;
        }
    }
    return;
}


void SchedulerRep::schedule(ProcessRep* p)
{   
    /*  
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice 
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run. 
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will 
                be put back to the queue first.


    */
/*
    YOUR CODE HEAR
*/
//Cases where mpRunningProcess is to be changed are the same as the codes above
    if(mpRunningProcess!= NULL) {                       
        if(mpRunningProcess->remainingTime == 0) {      
                                                        
            mpRunningProcess = popProcess();

            if(mpRunningProcess->startTime == -1)  {
                mpRunningProcess->startTime = totalTime;
            }

            if(mpRunningProcess->getProcessType() == "A") {
                timeSliceCount = 2;
            }
            else if(mpRunningProcess->getProcessType() == "B") {
                timeSliceCount = 4;
            }
            else if(mpRunningProcess->getProcessType() == "C") {
                timeSliceCount = 8;
            }

            pCpuObj->runCPU(mpRunningProcess, totalTime);
            timeSliceCount--;
            totalTime++;
            return;
        }
    }

    if(mpRunningProcess != NULL) {
        if(timeSliceCount == 0) {                       //Same with above
            pushProcess(mpRunningProcess);
            mpRunningProcess = popProcess();

            if(mpRunningProcess->startTime == -1) {
                mpRunningProcess->startTime = totalTime;
            }
            if(mpRunningProcess->getProcessType() == "A") {
                timeSliceCount = 2;
            }
            else if(mpRunningProcess->getProcessType() == "B") {
                timeSliceCount = 4;
            }
            else if(mpRunningProcess->getProcessType() == "C") {
                timeSliceCount = 8;
            }
            pCpuObj->runCPU(mpRunningProcess, totalTime);
            timeSliceCount--;
            totalTime++;
            return;
        }
    }
    
    //When mpRunningProcess not to be changed
    if(mpRunningProcess != NULL){                           
        pCpuObj->runCPU(mpRunningProcess, totalTime);
        totalTime++;
        timeSliceCount--;


        
        if(mpRunningProcess->remainingTime == 0) {

            //At the end of the program the last ran job would show up on RP: list so I had to assign null to mpRunningProcess
            //just before the program ends.
            if(mpProcessFIFO[0]->getHead() == NULL && mpProcessFIFO[1]->getHead() == NULL && mpProcessFIFO[2]->getHead() == NULL) {
                mpRunningProcess = NULL;     
                return;                      
            }
        
            mpRunningProcess = popProcess();

            if(mpRunningProcess->startTime == -1) {
                    mpRunningProcess->startTime = totalTime;
                }

            if(mpRunningProcess->getProcessType() == "A") {
                timeSliceCount = 2;
            }
            else if(mpRunningProcess->getProcessType() == "B") {
                timeSliceCount = 4;
            }
            else if(mpRunningProcess->getProcessType() == "C") {
                timeSliceCount = 8;
            }
        }    
        return;
    }
}