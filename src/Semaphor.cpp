#include "KeSem.h"
#include "Semaphor.h"

Semaphore::Semaphore (int init) {

	myImpl = new KernelSem(init);
}

Semaphore::~Semaphore () {
	delete myImpl;
}

int Semaphore::val () const {
	return myImpl->val();
}

int Semaphore::wait (Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n) {
	return myImpl->signal(n);
}

