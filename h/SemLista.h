/*
 * SemLista.h
 *
 *  Created on: Sep 12, 2020
 *      Author: OS1
 */

#ifndef SEMLISTA_H_
#define SEMLISTA_H_

class KernelSem;

struct Field {
	KernelSem* field;
	Field* next;
};

class SemLista {
	Field *head, *tail;
public:
	SemLista(): head(0), tail(0){}

	void dodajSem(KernelSem* sem);
	void izbaciSem(KernelSem* sem);
	void obavesti();
};


#endif /* SEMLISTA_H_ */
