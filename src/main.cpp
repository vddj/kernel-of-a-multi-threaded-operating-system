#include "SCHEDULE.H"
#include "PCB.h"
#include "KeSem.h"
#include <dos.h>
#include <iostream.h>

extern void inic();
extern void restore();
extern int userMain(int argc, char* argv[]);

class KernelThread: public Thread {
public:
	KernelThread(): Thread() {}
	virtual ~KernelThread(){
		waitToComplete();
	}
};

class userMainThread: public Thread {
	int ret;
public:
	userMainThread(): Thread(), ret(0) {}
	virtual ~userMainThread(){
		waitToComplete();
	}

	int retValue() { return ret; }

	virtual void run(){
			ret = userMain(::_argc, ::_argv);
		}
};

void main() {

	KernelThread kernelNit;
	kernelNit.start();
	PCB::running = Scheduler::get();
	userMainThread userNit;
	userNit.start();
	inic();
	while(PCB::broj_aktivnih > 0);
	restore();
	PCB::setKraj();
	//return userNit.retValue();
}
