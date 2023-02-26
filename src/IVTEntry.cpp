#include "IVTEntry.h"
#include "thread.h"
#include <dos.h>
#include <iostream.h>

IVTEntry* IVTEntry::entries[brVektora];
pInterrupt IVTEntry::stareRutine[brVektora];

IVTEntry::IVTEntry(int ent, pInterrupt rutina) : sem(0){

	lockFlag = 0;
	brUlaza = ent;
    entries[ent] = this;
    old = 0;
    #ifndef BCC_BLOCK_IGNORE
        old = getvect(ent);
    	setvect(ent, rutina);
    #endif
    stareRutine[ent] = old;
    lockFlag = 1;
}

IVTEntry::~IVTEntry(){
	(*old)();
#ifndef BCC_BLOCK_IGNORE
 	setvect(brUlaza, old);
 #endif
}

void IVTEntry::signal() {
	sem.signal(0);
	dispatch();
}
