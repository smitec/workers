#ifndef MASTER_H
#define MASTER_H
#include "Worker.h"
#include <windows.h> //for threads

/*
Master starts and the tread is running until it is killed.
A master is assigned a Worker, makes it execute its task
After the task is collected it waits again for a new Worker
Masters are designed to remove thread overhead
*/

DWORD WINAPI master_thread(LPVOID masterPtr);

class master
{
    public:
        master();
        virtual ~master();

        bool assign_worker(Worker* newWorker, bool nohang);
        void start_master();

        void kill();

        Worker* currentJob;
        bool busy;
        bool newJob;
        bool killMe;
        bool pending;
        bool jobCollected;
        HANDLE threadHandle;
        LPDWORD threadID;

    protected:
    private:
};



#endif // MASTER_H
