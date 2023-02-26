#include "SemLista.h"
#include "KeSem.h"
#include "Lista.h"
#include <iostream.h>

void SemLista::dodajSem(KernelSem* sem) {
	Field* novo = new Field;
	novo->field = sem;
	novo->next = 0;
	if (head == 0) {
		head = tail = novo;
	}
	else {
		tail->next = novo;
		tail = novo;
	}
}

void SemLista::izbaciSem(KernelSem* sem) {
	Field* pom = head;
	Field* pret = 0;
	if(head == tail){
		delete head;
		head = tail = 0;
	}
	while (pom != 0) {
		if(pom->field->getId() == sem->getId()) {
			if(pret == 0) head = head->next;
			else pret->next = pom->next;
			if (tail == pom) tail = pret;
			delete pom;
		}
		pret = pom;
		pom = pom->next;
	}
}

void SemLista::obavesti(){
	Field* pom = head;
	while (pom != 0) {
		pom->field->blokirane->obavesti();
		pom = pom->next;
	}
}
