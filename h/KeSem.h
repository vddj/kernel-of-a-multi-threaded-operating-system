#ifndef KERNELSEM_H_
#define KERNELSEM_H_

#include "PCB.h"

class Lista;
class SemLista;

class KernelSem {

	static SemLista semafori;
	Lista* blokirane;
	static int broj_semafora;
	int ID;
	int value;
	char maxT, trenT;

	void block(int time);
	int deblock();

	friend class Lista;
	friend class SemLista;
	friend void interrupt timer(...);
	friend void interrupt _block(...);

public:
	KernelSem(int v);
	int val () const { return value; }
	int wait (Time maxTimeToWait);
	int signal(int n=0);
	int getId() {return ID;}
	void addValue(int n) {value += n;}
	~KernelSem();
};

#endif /* KERNELSEM_H_ */
