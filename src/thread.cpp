#include <stdio.h>
#include <dos.h>
#include "thread.h"
#include "SCHEDULE.h"
#include "Lista.h"
#include "Semaphor.h"

extern char zahtev;

void Thread::start(){
	Scheduler::put(this->myPCB);
}

void Thread::waitToComplete() {
	while (myPCB->getKraj() == 0) myPCB->sem->wait(0);
	//delete myPCB;
}

Thread::~Thread() {
	waitToComplete();
	delete myPCB;
}

ID Thread::getId(){
	return myPCB->getId();
}

ID Thread::getRunningId() {
	return PCB::running->getId();
}

Thread* Thread::getThreadById(ID id) {
	return PCB::lista.getById(id);
}

Thread::Thread (StackSize stackSize, Time timeSlice){
	myPCB = new PCB(stackSize, this, timeSlice);
}

void dispatch() {
	zahtev = 1;
	asm int 8h; // poziv tajmera
}
