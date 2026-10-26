#include <iostream>
#include <cassert>
#include "Scheduler.hpp"
#include "Process.hpp"

using namespace std;

int main()
{
    cout << "--- Testing RoundRobin (ArrayList) ---" << endl;
    RoundRobin scheduler;

    cout << "Scheduler created." << endl;

    Process* p1 = new CPUBoundProcess(1);
    Process* p2 = new IOBoundProcess(2);

    cout << "Created processes 1 (CPU) and 2 (I/O)." << endl;

    scheduler.addProcess(p1);
    scheduler.addProcess(p2);

    cout << "Added processes to scheduler." << endl;

    cout << "Testing popNext(0)..." << endl;

    Process* nextProc = scheduler.popNext(0);
    assert(nextProc == p1);

    nextProc = scheduler.popNext(0);
    assert(nextProc == p2);

    nextProc = scheduler.popNext(0);
    assert(nextProc == 0);

    cout << "popNext(0) passed." << endl;

    cout << "\n--- Testing Blocked Logic ---" << endl;
    Process* p3 = new CPUBoundProcess(3);
    Process* p4 = new IOBoundProcess(4);
    cout << "Created processes 3 (CPU) and 4 (I/O)." << endl;

    int curCycle = 0;
    cout << "Forcing p4 to block..." << endl;
    while (!p4->isBlocked(curCycle))
    {
        int timeUsed = p4->useCPU(curCycle, 10);
        curCycle += timeUsed;
    }
    cout << "p4 is now blocked until cycle " << curCycle << "." << endl;

    scheduler.addProcess(p4);
    scheduler.addProcess(p3);
    cout << "Added processes. Queue: [p4_blocked, p3_unblocked]" << endl;

    cout << "Testing popNext(" << curCycle << ")..." << endl;
    nextProc = scheduler.popNext(curCycle);
    assert(nextProc == p3);

    nextProc = scheduler.popNext(curCycle);
    assert(nextProc == 0);

    cout << "Block logic tests passed." << endl;

    cout << "\nAll RoundRobin tests passed!" << endl;

    delete p1;
    delete p2;
    delete p3;
    delete p4; 

    cout << "\n\n--- Testing FastRoundRobin (LinkedList) ---" << endl;
    FastRoundRobin fastScheduler;

    cout << "Scheduler created." << endl;

    Process* p5 = new CPUBoundProcess(5);
    Process* p6 = new IOBoundProcess(6);

    cout << "Created processes 5 (CPU) and 6 (I/O)." << endl;

    fastScheduler.addProcess(p5);
    fastScheduler.addProcess(p6); 

    cout << "Added processes to scheduler." << endl;

    cout << "Testing popNext(0)..." << endl;

    Process* nextProc_frr = fastScheduler.popNext(0); 
    assert(nextProc_frr == p5);

    nextProc_frr = fastScheduler.popNext(0);
    assert(nextProc_frr == p6);

    nextProc_frr = fastScheduler.popNext(0); 
    assert(nextProc_frr == 0);

    cout << "popNext(0) passed." << endl;

    cout << "\n--- Testing Blocked Logic ---" << endl;
    Process* p7 = new CPUBoundProcess(7); 
    Process* p8 = new IOBoundProcess(8); 
    cout << "Created processes 7 (CPU) and 8 (I/O)." << endl;

    int curCycle_frr = 0; 
    cout << "Forcing p8 to block..." << endl;
    while (!p8->isBlocked(curCycle_frr))
    {
        int timeUsed = p8->useCPU(curCycle_frr, 10);
        curCycle_frr += timeUsed;
    }
    cout << "p8 is now blocked until cycle " << curCycle_frr << "." << endl;

    fastScheduler.addProcess(p8); 
    fastScheduler.addProcess(p7); // <-- Use _frr
    cout << "Added processes. Queue: [p8_blocked, p7_unblocked]" << endl;

    cout << "Testing popNext(" << curCycle_frr << ")..." << endl;
    nextProc_frr = fastScheduler.popNext(curCycle_frr); 
    assert(nextProc_frr == p7);

    nextProc_frr = fastScheduler.popNext(curCycle_frr); 
    assert(nextProc_frr == 0);

    cout << "Block logic tests passed." << endl;

    cout << "\nAll FastRoundRobin tests passed!" << endl;

    delete p5; 
    delete p6;
    delete p7;
    delete p8;

    return 0;
}