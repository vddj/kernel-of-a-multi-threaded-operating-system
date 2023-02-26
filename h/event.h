#ifndef EVENT_H_
#define EVENT_H_

typedef unsigned char IVTNo;
class KernelEv;
#include "IVTEntry.h"

// MAKRO

#define PREPAREENTRY(entry, uslov) \
	void interrupt rutina##entry(...) {\
         IVTEntry::entries[##entry]->signal();\
         if (##uslov) IVTEntry::entries[##entry]->pozivStare();}\
IVTEntry routine##entry (##entry, rutina##entry);

class Event {

public:
	Event (IVTNo ivtNo);
	~Event ();
    void wait ();

protected:
	friend class KernelEv;
	void signal(); // can call KernelEv

private:
	KernelEv* myImpl;
};

#endif /* EVENT_H_ */
