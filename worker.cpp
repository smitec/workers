#include "worker.h"

/** Empty Constuctor
*/
Worker::Worker()
{
    //ctor
    this->finished = false;
    this->arg = 0;
    this->result = 0;
    this->ready = true;
}

/** Empty deconstructor
*/
Worker::~Worker()
{
    //dtor
}

/** sets up the Worker and creates it's thread
    Worker now runs its process in the background
    \arg void* to be cast within work function
*/
//TODO add nohang and bool return
bool Worker::start_worker(void* arg, bool nohang)
{
    if (!this->ready && nohang) {
        return false;
    }
    while (!this->ready); //wait until the worker is ready so we cant start it twice while its running
    this->arg = arg;
    pthread_t temp = 0;
    this->collected = false;
    this->finished = false;
    pthread_create(&temp, NULL, worker_thread, (void*)this);//CreateThread(NULL, 0, worker_thread, (void*)this, 0, &temp);
    pthread_detach(temp);
    this->threadID = temp;
    return true;
}

/** checks if the Worker has finished processing
    Does not block. good for checking from time to time
    \return returns status of done flag
*/
bool Worker::is_finished()
{
    return this->finished;
}

/** Get the result of the Worker
    This function blocks when called
    For non blocking use isFinished to
    check if Worker is ready
    \return void* to be cast as needed

*/
void* Worker::get_result()
{
    while(!this->finished);
    this->collected = true;
    this->ready = true;
    return this->result;
}

/** work function is virtual so will be overwritten
    this allows almost anything to be done by a Worker
*/
void Worker::work()
{
    /*default behavious just return the arg, essentially useless
    but can be used to test if the Worker is creating itself properly*/
    this->result = this->arg;
    this->finished = true;
}

/** Used to call the work function of the class
    used like this because class functions cannot
    be passed into the CreateThread function
    easily.
    \arg the Worker which is to be run

*/
void* worker_thread(void* worker)
{
    Worker *myWorker = (Worker*)worker;
    myWorker->work();
    return 0;
}

void Worker::set_arg(void* arg){
    this->arg = arg;
}
