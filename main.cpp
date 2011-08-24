#include <iostream>
#include <vector>
#include "worker.h"
#include "master.h"
#include <time.h>
#include <fstream>

using namespace std;

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
    int* res = new int;
    for(int i = 0; i < 2000; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            *res = i*j + 1;
        }
    }
    this->result = (void*)res;
    this->finished = true;
}

double threadCompare(int numThreads) {
    vector<anotherWorker> withThreads;
    vector<anotherWorker> withoutThreads;

    for (int i = 0; i < numThreads; i++) {
        withThreads.push_back(anotherWorker());
        withoutThreads.push_back(anotherWorker());
    }

    /** Testing With Threads First
    */
    double res1 = 0;
    clock_t start, finish;
    start = clock();
    for (int i = 0; i < numThreads; i++) {
        withThreads[i].start_worker(0);
    }
    void* res;
    for (int i = 0; i < numThreads; i++) {
        res = withThreads[i].get_result();
    }
    finish = clock();
    res1 = (finish - start)/(1.0*CLOCKS_PER_SEC);
    /** Testing Without threads
    */
    start = clock();
    for (int i = 0; i < numThreads; i++) {
        withoutThreads[i].work();
    }
    finish = clock();
    double res2 = (finish - start)/(1.0*CLOCKS_PER_SEC);

    //std::cout << "Results for "<< numThreads << " Threads :\n\tWithout Threads- " << res2 << "s\n\tWith Threads- " << res1 <<"s\n";
    //std::cout << "\tRatio (without/with): " << res2/res1 << "\n";
    return res2/res1;
}

int main()
{
    int bins[40];
    for (int i = 0; i < 40; i++) {
        bins[i] = 0;
    }
    double temp, temptwo;
    int fastest;
    for (int j = 0; j < 500; j++) {
        if (j%(500/100) == 0) { std::cout << ".";}
        temp = 0;
        fastest = -1;
        for (int i = 2; i <= 40; i++){
            temptwo = threadCompare(i);
            if (temptwo > temp) {
                temp = temptwo;
                fastest = i;
            }
        }
        bins[fastest]++;
    }
    ofstream output;
    output.open("results.txt", ios::out);
    for (int i = 0; i < 40; i++) {
        output << bins[i] << "\n";
    }
    output.close();

    return 0;
}
