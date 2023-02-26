#include "Lista.h"
#include <iostream.h>
#include "Schedule.h"

extern char lockFlag;

Thread* Lista::getById(ID n) {
	Polje* pom = head;
	while (pom != 0) {
		if(pom->polje->getId() == n) return pom->polje->myThread;
		pom = pom->next;
	}
	return 0;
}

void Lista::dodajNit(PCB* nit, int t, KernelSem* id){
	Lista::dodajNit(nit);
	tail->time = t;
	tail->sem = id;
	//ispis();
}

void Lista::dodajNit(PCB* nit) {
	Polje* novo = new Polje;
	novo->polje = nit;
	novo->next = 0;
	if (head == 0) {
		head = tail = novo;
	}
	else {
		tail->next = novo;
		tail = novo;
	}
}

PCB* Lista::izbaciNit(PCB* nit) {
	Polje* pom = head;
	Polje* pret = 0;
	PCB* povr = 0;
	if(head == tail){
		povr = head->polje;
		delete head;
		head = tail = 0;
		return povr;
	}
	while (pom != 0) {
		if(pom->polje->getId() == nit->getId()) {
			povr = pom->polje;
			if(pret == 0) head = head->next;
			else pret->next = pom->next;
			if (tail == pom) tail = pret;
			delete pom;
			return povr;
		}
		pret = pom;
		pom = pom->next;
	}
	return 0;
}

PCB* Lista::izbaciPrvu(){
	PCB* pom = 0;
	if (head == 0) return 0;
	else {
		pom = head->polje;
		Polje* p = head;
		if(head == tail) head = tail = 0;
		else head = head->next;
		delete p;
	}
	return pom;
}

PCB* Lista::izbaciOdredjenu(int n) {
	Polje* pom = head;
	if (pom == 0) return 0;
	while (pom->sem->getId() != n) pom = pom->next;
	if (pom == 0) return 0;
	return izbaciNit(pom->polje);
}

Lista::~Lista(){
	Polje* pom;
	while (head != 0) {
		pom = head;
		head = head->next;
		delete pom;
	}
}

void Lista::obavesti(){
		Polje* pom = head;
		while (pom != 0) {
			if (pom->time != 0)
				if (--(pom->time) == 0) {
					pom->sem->addValue(1);
					Polje* privrem = pom->next;
					PCB* pcbVr = izbaciNit(pom->polje);
					if (pcbVr) {
						pcbVr->returnValue = 0;
						Scheduler::put(pcbVr);
					}
					pom = privrem;
					continue;
				}
			pom = pom->next;
		}
	}

void Lista::ispis(){
	lockFlag = 0;
	Polje* pom = Lista::head;
	while (pom != 0) {
			//cout << "  nit: " << pom->polje->getId() << " sem: " << pom->sem->;
			pom = pom->next;
		}
	cout << endl;
	lockFlag = 1;
}
