#include <dos.h>
#include "SCHEDULE.H"
#include <iostream.h>
#include "Lista.h"
#include "KeSem.h"
#include "SemLista.h"

typedef void interrupt (*pInterrupt) (...);

pInterrupt oldTimer;
volatile char zahtev = 0;
volatile char lockFlag = 1;

//extern void tick();
cnt_buf *b;
// prekidna rutina za tajmer koja sadrzi i promenu konteksta u slucaju isteka kvanta vremena
unsigned sss, ssp;
void interrupt timer(...){
    //printf("..timer prekidna rutina..\n");
	if (lockFlag == 0) goto Preskoci;
	if(zahtev) goto Label;
	if(PCB::running->getKvant() != 0)
		if(--PCB::running->menjajKvant() == 0) {
			PCB::running->menjajKvant() = PCB::running->getKvant();
            Label:
			b = PCB::running->context;
			asm {
				mov ssp, sp
				mov sss, ss
			}
			b->ss = sss;
			b->sp = ssp;

			if(PCB::running->kraj == 0)
				Scheduler::put(PCB::running);
			//else delete PCB::running;
			//cout << "pre " <<PCB::running->id << endl;
			PCB::running = Scheduler::get();  // stavljanje novog konteksta
            b = PCB::running->context;

			sss = b->ss;
			ssp = b->sp;
			asm{
				mov sp, ssp			 // restauriramo stek
				mov ss, sss
			}
			lockFlag = 1;
			//cout << "pos " <<PCB::running->id << endl;
	}
	//iuvek pozivam stari tajmer
	Preskoci:
//	tick();
	if (!zahtev) {
		//cout << "obavestii..." << endl;
		KernelSem::semafori.obavesti();
		asm int 60h;
	}
	else zahtev = 0;
}

void interrupt _block(...) {
	//printf("..block prekidna rutina..\n");
	b = PCB::running->context;
	asm {
		 mov ssp, sp
	     mov sss, ss
	}
	b->ss = sss;
	b->sp = ssp;
	//cout << "pre ;" <<PCB::running->id << endl;

	PCB::running = Scheduler::get();  // stavljanje novog konteksta
    b = PCB::running->context;

	sss = b->ss;
	ssp = b->sp;
	asm{
		mov sp, ssp			 // restauriramo stek
		mov ss, sss
	}
	lockFlag = 1;
	//cout << "pos ;" <<PCB::running->id << endl;
}
// izmena prekidne rutine za tajmer

void inic() {
	lockFlag = 0;
#ifndef BCC_BLOCK_IGNORE
	oldTimer = getvect(0x8);
	setvect(0x8, timer);
	setvect(0x60, oldTimer);
	setvect(0xf1, _block);
#endif
	lockFlag = 1;
}

void restore () {
	lockFlag = 0;
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8, oldTimer);
#endif
	lockFlag = 1;
}
