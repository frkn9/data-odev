/* @Author
Student Name: 
Student ID : 
Date: 
*/


#include <iostream>
#include <stdio.h>
#include "ProcessRep.h"
class FIFORep 
{
    /*
        The class construct a FIFO queue.
    */

private:
    ProcessRep* mpHead;
    ProcessRep* mpTail;
public:
    FIFORep();
    FIFORep(ProcessRep*);
    ~FIFORep();

    void setHead(ProcessRep*);
    ProcessRep* getHead();

    void setTail(ProcessRep*);
    ProcessRep* getTail();

    void queue(ProcessRep*);
    ProcessRep* dequeue();

    ProcessRep* searchID(int);
    void printFIFO();
};

FIFORep::FIFORep()
{
    
    /*
        YOUR CODE HEAR
    */

    //initially both mphead and mptail are null
    mpHead = NULL;
    mpTail = NULL;
    
}

FIFORep::FIFORep(ProcessRep* head)
{
    /*
        YOUR CODE HEAR
    */
                
    //set mpHead, assign NULL to mpHead's next just in case the passed argument had its next pointer
    mpHead = head;
    mpHead->setNext(NULL);
}


FIFORep::~FIFORep()
{
    
    while(mpHead != NULL) {
        delete dequeue();
    }
}

void FIFORep::setHead(ProcessRep* head)
{
    /*
        YOUR CODE HEAR
    */
    //if FIFO is empty, just assign mpHead and set its next to NULL, 
    if(mpHead == NULL) {    
        mpHead = head;
        mpHead->setNext(NULL);
    }
    //since head is to be overwritten, I copied the old mpHead's address to the pointer old, updated mpHead with the passed argument,
    //set new mpHead's next to old mpHead's next for the new mpHead to not point to the element
    //just after the head, instead of somewhere random, then deleted the old Head 
    ProcessRep* old = mpHead;
    mpHead = head;
    mpHead->setNext(old->getNext());
    delete old;
}

ProcessRep* FIFORep::getHead()
{
    /*
        YOUR CODE HEAR
    */
    return mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    /*
        YOUR CODE HEAR
    */
    if(mpTail == NULL) {
        mpTail = tail;
    }

    //like head, the old mpTail is to be overwritten so I saved the address of old mpTail in pointer old. 
    //updated mpTail with the new tail, set v1 to point to the node just before tail, made its next point to the now updated mpTail.
    //after that deleted the old mpTail  
    ProcessRep* old = mpTail;
    mpTail = tail;
    ProcessRep* v1 = mpHead;
    while(v1->getNext()->getNext() != NULL) {
        v1 = v1->getNext();
    }
    v1->setNext(mpTail);
    delete old;

    
}

ProcessRep* FIFORep::getTail()
{
    /*
        YOUR CODE HEAR
    */
    return mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    /*
        The function add a process to the tail of the fifo.
    */
    /*
        YOUR CODE HEAR
    */

    //if fifo empty assign head.
    if(mpHead == NULL) {
        mpHead = p;
        mpHead->setNext(NULL);
        mpTail = NULL;
        return;
    }
    //if fifo has only one node assign tail
    else if(mpTail == NULL) {
        mpTail = p;
        mpTail->setNext(NULL);
        mpHead->setNext(mpTail);
        return;
    }
    //if fifo has at least two nodes, set mpTails's next to the node to be queued, then make mpTail point to the new tail
    else {
        mpTail->setNext(p);
        mpTail = p;
        p->setNext(NULL);
    }
        
    

    

}

ProcessRep* FIFORep::dequeue()
{   
    /*
        The function remove a process from the head of the fifo and returns it.
    */   
    /*
        YOUR CODE HEAR
    */
    ProcessRep* old = mpHead;       //stores the address of the head to be returned

    //if only one element make list empty and return old
    if(mpHead->getNext() == NULL) {
        mpHead = NULL;
        mpTail = NULL;
        return old;
    }

    //if only two elements return assign mpTail to mpHead, then return old
    if(mpHead->getNext()->getNext() == NULL) {
        mpHead = mpTail;
        mpTail = NULL;
        old->setNext(NULL);         //I set old's next to null before returning to avoid bugs such as infinite loops
        return old;
    }

    //if more than two elements make mpHead point to old's next.  
    mpHead = mpHead->getNext();
    old->setNext(NULL);
    return old;
    
    
}

ProcessRep* FIFORep::searchID(int id)
{   
    /*
        The function search a process by id and returns it if it exist otherwise returns NULL.
    */ 
    /*
        YOUR CODE HEAR
    */
    ProcessRep* v;
    v = mpHead;
    //copied mpHead to another pointer and advanced until it found the process id
    while(v->getProcessID() != id && v != NULL) {
        v = v->getNext();
    }
    return v;
}

void FIFORep::printFIFO()
{
    /*
        The function prints the proceses in the queue starting from Head to tail.
    */
    /*
        YOUR CODE HEAR
    */
    ProcessRep* v = mpHead;
    while(v != NULL) {
        cout << v->getProcessType() << v->getProcessID() << " " << v->startTime << " " << v->endTime << " ";
        v = v->getNext();
    }
}
