#ifndef PCB_h_
#define PCB_h_

#include "thread.h"

class Thread;
class Lista;
class Semaphore;

extern void interrupt timer(...);
extern void interrupt _block(...);
extern void main();

 struct cnt_buf {
	 unsigned ss;
	 unsigned sp;
 };

class PCB {

	 static PCB* running;
	 static ID broj_niti;
	 static int broj_aktivnih;
	 static Lista lista;

	 const ID id;
	 int kraj;
	 unsigned* stack;
	 Thread* myThread;
	 cnt_buf* context;
	 Time timeSlice, kvant;
	 int returnValue;
	 Semaphore* sem;

	 PCB(StackSize, Thread*, Time);
	 ~PCB();

	 static void pokret();
	 Time& menjajKvant() { return kvant; }
	 const Time getKvant() { return timeSlice; }

	 friend class Lista;
	 friend class Thread;
	 friend class KernelSem;
	 friend void main();
	 friend void interrupt timer(...);
	 friend void interrupt _block(...);

 public:
 	const ID getId() { return id; }
 	int getKraj() const { return kraj; }
 	static void setKraj();
 	static void resetReturnValue ();
 	static int getReturnValue ();
 };

#endif /* PCB_H_ */
