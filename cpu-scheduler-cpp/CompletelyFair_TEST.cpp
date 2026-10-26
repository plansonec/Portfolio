#include <iostream>
#include <cassert>
#include "Scheduler.hpp"
#include "Process.hpp"

using namespace std;

int main()
{
    cout << "Testing CompletelyFair Scheduler" << endl;
    CompletelyFair scheduler;

    Process* p1 = new CPUBoundProcess(1); 
    p1->useCPU(0, 100); 

    Process* p2 = new CPUBoundProcess(2); 
    p2->useCPU(0, 10);

    scheduler.addProcess(p1);
    scheduler.addProcess(p2);

    Process* next = scheduler.popNext(0);
    assert(next == p2);
    cout << "Fairness test passed (picked p2 first)." << endl;

    next = scheduler.popNext(0);
    assert(next == p1);
    cout << "Sequence test passed (picked p1 second)." << endl;

    delete p1;
    delete p2;

    cout << "ALL COMPLETELY FAIR TESTS PASSED" << endl;
    return 0;
}