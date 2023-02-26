#ifndef _thread_h_
#define _thread_h_

 typedef unsigned long StackSize;
 const StackSize defaultStackSize = 2096;
 typedef unsigned int Time; // time, x 55ms
 const Time defaultTimeSlice = 2; // default = 2*55ms
 typedef int ID;

class PCB;

class Thread {

 public:
   void start();
   void waitToComplete();
   virtual ~Thread();

   ID getId();
   static ID getRunningId();
   static Thread * getThreadById(ID id);

protected:
   friend class PCB;
   Thread (StackSize = defaultStackSize, Time = defaultTimeSlice);
   virtual void run() {}

 private:
   PCB* myPCB;
};

void dispatch();

#endif
