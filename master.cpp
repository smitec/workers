#include "Master.h"

master::master() {
    this->busy = false;
    this->jobCollected = false;
    this->pending = false;
    this->killMe = false;
    this->currentJob = NULL;
}

master::~master() {
    //dtor
}

bool master::assign_worker(Worker* newWorker, bool noHang) {
    if (noHang && this->busy) {
        return false;
    }
    while(this->busy && !this->pending);
    this->pending = true; //Mutex This
    this->currentJob = newWorker;
    this->newJob = true;
    return true;
}

void master::start_master() {
    pthread_t temp = 0;
    this->busy = false;
    this->jobCollected = false;
    this->pending = false;
    this->killMe = false;
    pthread_create(&temp, NULL, master_thread, (void*)this);
    this->threadID = temp;
}

void master::kill() {
    this->killMe = true;
}

void* master_thread(void* masterPtr)
{
    master* theMaster = (master*)masterPtr;
    while(!theMaster->killMe){
        if (theMaster->newJob){
            theMaster->busy = true;
            theMaster->pending = false;
            theMaster->currentJob->work();
            while(!theMaster->jobCollected);
            theMaster->busy = false;
            theMaster->jobCollected = false;
        }
    }
    return 0;
}
