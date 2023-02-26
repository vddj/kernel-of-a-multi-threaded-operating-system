#ifndef Lista_h_
#define Lista_h_

#include "KeSem.h"

class KernelSem;

struct Polje {
	PCB* polje;
	Polje* next;
	int time;
	KernelSem* sem;
};

class Lista {

	Polje *head, *tail;

public:
	Lista() : head(0), tail(0) {}
	Thread* getById(ID n);
	void dodajNit(PCB* nit);
	PCB* izbaciNit(PCB* nit);
	PCB* izbaciPrvu();
	PCB* izbaciOdredjenu(int n);
	~Lista();
	void ispis();
	void dodajNit(PCB* nit, int t, KernelSem* id);
	void obavesti();

};

#endif /* LISTA_H_ */
