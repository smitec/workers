#include "worker.h"

/** Empty Constuctor
*/
Worker::Worker()
{
    //ctor
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
    arg may become a vector of void* so that multiple
    args can be sent to the Worker function
*/
void Worker::start_worker(void* arg)
{
    this->arg = arg;
    LPDWORD temp = 0;
    this->collected = false;
    this->finished = false;
    this->threadHandle = CreateThread(NULL, 0, worker_thread, (LPVOID)this, 0, temp);
    this->threadID = temp;

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
    return this->result;
}

/** work function is virtual so will be overwritten
    this allows almost anything to be done by a Worker
*/
void Worker::work()
{
    /*default behavious just return the arg as an int, essentially useless
    but can be used to test if the Worker is creating itself properly*/
    int i = (int)this->arg;
    this->result = (void*)i;
    this->finished = true;
}

/** Used to call the work function of the class
    used like this because class functions cannot
    be passed into the CreateThread function
    easily.
    \arg the Worker which is to be run

*/
DWORD WINAPI worker_thread(LPVOID toWork)
{
    Worker* myWorker = (Worker*)toWork;
    myWorker->work();
    return 0;
}

void Worker::set_arg(void* arg){
    this->arg = arg;
}
