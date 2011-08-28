#ifndef WORKER_H
#define WORKER_H

#include <pthread.h>
void* worker_thread(void* worker);
/*
Workers do work
they can be executed in a thread via the start Worker function
they can be executed inline using the work function
if executed inline the arg must be set manually
*/



class Worker
{
public:
    Worker();
    ~Worker();

    void start_worker(void* arg);
    bool is_finished();
    void* get_result();

    void set_arg(void* arg);

    virtual void work();
protected:
    pthread_t threadID;
    bool finished;
    bool collected;
    void* result;
    void* arg;

private:
};

#endif // WORKER_H
