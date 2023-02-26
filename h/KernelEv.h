#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "IVTEntry.h"

class KernelEv {

	IVTNo ivtNo;

public:
	KernelEv(IVTNo i) : ivtNo(i){}

	void wait(){
		IVTEntry::entries[ivtNo]->wait();
	}
	void signal(){
		IVTEntry::entries[ivtNo]->signal();
	}
};



#endif /* KERNELEV_H_ */
