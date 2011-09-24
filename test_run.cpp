/*#include <iostream>
#include <vector>
#include "worker.h"
#include "master.h"
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

double threadCompare(int numThreads);

class testWorker: public Worker
{
public:
    void work();
};

class anotherWorker: public Worker
{
public:
    void work();
};

void testWorker::work()
{
    //Simple making of a string
    string* res = new string("This Wroked Yay!");
    this->result = (void*)res;
    this->finished = true;
}

void anotherWorker::work()
{
    //Run a loop so it takes up some time
    int res = 0;
    for(int i = 0; i < 100000; i++)
    {
        for (int j = 0; j < 10000; j++)
        {
            res = sqrt(i*j);
        }
    }
    this->result = (void*)clock();
    this->finished = true;
}

double threadCompare(int numThreads) {
    vector<anotherWorker> withThreads;
    vector<anotherWorker> withoutThreads;
    
    if (numThreads > 20) {
        numThreads = 20;
    }

    for (int i = 0; i < numThreads; i++) {
        withThreads.push_back(anotherWorker());
        withoutThreads.push_back(anotherWorker());
    }

    double res1 = 0;
    clock_t start, finish, tstart;
    tstart = clock();
    for (int i = 0; i < numThreads; i++) {
        withThreads[i].start_worker(0);
    }
    
    start = clock();
    for (int i = 0; i < numThreads; i++) {
        withoutThreads[i].work();
    }
    finish = clock();
    double res2 = (finish - start)/(1.0*CLOCKS_PER_SEC);

    
    void* res[20];
    for (int i = 0; i < numThreads; i++) {
        res[i] = withThreads[i].get_result();
    }
    //find max finish time
    finish = 0;
    for (int i = 0; i < numThreads; i++) {
        finish = ((clock_t)res[i] > finish) ? (clock_t)res[i] : finish;
    }
    
    
    res1 = (finish - tstart)/(1.0*CLOCKS_PER_SEC);
    
    std::cout << "Results for "<< numThreads << " Threads :\n\tWithout Threads- " << res2 << "s\n\tWith Threads- " << res1 <<"s\n";
    std::cout << "\tRatio (without/with): " << res2/res1 << "\n";
    return res2/res1;
}

int main()
{
    
    threadCompare(5);

    return 0;
}
*/
