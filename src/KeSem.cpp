#include "KeSem.h"
#include "Schedule.h"
#include <iostream.h>
#include "Lista.h"
#include "Semaphor.h"
#include "SemLista.h"

SemLista KernelSem::semafori;
int KernelSem::broj_semafora = 1;
extern char lockFlag;

KernelSem::KernelSem(int v){
	ID = broj_semafora++;
	value = v;
	maxT = trenT = 0;
	semafori.dodajSem(this);
	blokirane = new Lista();
}

int KernelSem::wait (Time maxTimeToWait){
	lockFlag = 0;
	PCB::resetReturnValue();
	maxT = trenT = maxTimeToWait;
	if(--value < 0) block(maxTimeToWait);
	lockFlag = 1;
	return PCB::getReturnValue();
}

int KernelSem::signal(int n) {
	lockFlag = 0;
	int povr;
	if (n < 0) povr = n;
	if (n == 0) {
		if (value++ < 0) {
			deblock();
			//dispatch();
		}
		povr = 0;
	}
	if (n > 0) {
		int i, br = 0, j;
		for (i = 0; i < n; i++) {
			j = deblock();
		    br += j || j;
		}
		value += n;
		povr = br;
	}
	lockFlag = 1;
	return povr;
}


void KernelSem::block(int time){
	blokirane->dodajNit(PCB::running, time, this);
	                           //poziv prekidne rutine za block
	asm int 11110001b;
}

int KernelSem::deblock(){    // nit je odblokirana signalom
	lockFlag = 0;
    PCB* pom = blokirane->izbaciOdredjenu(this->ID);
    if (pom != 0) Scheduler::put(pom);
	lockFlag = 1;
    return (int)pom;
}

KernelSem::~KernelSem() {
	//delete blokirane;
	semafori.izbaciSem(this);
	delete blokirane;
}
