#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Semaphor.h"

extern char lockFlag;

#define brVektora 256
typedef void interrupt (*pInterrupt) (...);
typedef unsigned char IVTNo;

class IVTEntry {
public:
	static IVTEntry* entries[brVektora];
	static pInterrupt stareRutine[brVektora];

	Semaphore sem;
	IVTNo brUlaza;
	pInterrupt old;
	IVTEntry(int ent, pInterrupt rutina);
	~IVTEntry();

	void signal();
	void wait() { sem.wait(0); }
	void pozivStare() { (*old)(); }
};

#endif /* IVTENTRY_H_ */
