#include <dos.h>
#include<iostream.h>
#include "Lista.h"
#include "PCB.h"
#include "Semaphor.h"

ID PCB::broj_niti = 0;
PCB* PCB::running = 0;
int PCB::broj_aktivnih = -1;
Lista PCB::lista;

extern char lockFlag;

void PCB::pokret(){
	PCB::running->myThread->run();
	lockFlag = 0;
	PCB::running->kraj = 1;
	PCB::broj_aktivnih--;
	PCB::running->sem->signal();
	//cout << "kraj " <<PCB::running->id << endl;
	lockFlag = 1;
	dispatch();
}

PCB::PCB(StackSize stackSize, Thread* myThread, Time timeSlice) :
		id (PCB::broj_niti++) {
	lockFlag = 0;
	if(stackSize>65536) stackSize = 65536;
	unsigned* st = new unsigned[stackSize];

	sem = new Semaphore(0);
	PCB::broj_aktivnih++;
	this->myThread = myThread;
	kvant = timeSlice;
	this->timeSlice = timeSlice;
	context = new cnt_buf;
	kraj = 0;
	stack = st;
	returnValue = 1;

#ifndef BCC_BLOCK_IGNORE
	context->sp = FP_OFF(st+stackSize - 12);
	context->ss = FP_SEG(st+stackSize - 12);
	stack[stackSize-1] = 0x200;
	stack[stackSize-2] = FP_SEG(PCB::pokret);
    stack[stackSize-3] = FP_OFF(PCB::pokret);
#endif

    PCB:lista.dodajNit(this);
    lockFlag = 1;
}

PCB::~PCB () {
	PCB::lista.izbaciNit(this);
    delete [] stack;
	delete [] context;
}

void PCB::setKraj() { PCB::running->kraj = 1;}
int PCB::getReturnValue () { return PCB::running->returnValue; }
void PCB::resetReturnValue () { PCB::running->returnValue = 1; }
