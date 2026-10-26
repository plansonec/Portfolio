#include "Simulate.hpp"
#include "Process.hpp"
#include "ArrayList.hpp"
#include <chrono>

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles) 
{
    ArrayList<Process*> cpuProcs;
    ArrayList<Process*> ioProcs;

    for (int i = 0; i < numCPUBound; i++) 
    {
        Process* p = new CPUBoundProcess(i);
        sched->addProcess(p);
        cpuProcs.pushBack(p);
    }

    for (int i = 0; i < numIOBound; i++) 
    {
        Process* p = new IOBoundProcess(numCPUBound + i);
        sched->addProcess(p);   // Add to the scheduler
        ioProcs.pushBack(p); // Add to our local list
    }

    int totalSimulatedCycles = 0;
    int popNextCalls = 0;

    auto startTime = std::chrono::system_clock::now();

while (totalSimulatedCycles < numCycles) 
    {
        Process* nextProc = sched->popNext(totalSimulatedCycles);
        popNextCalls++;

        if (nextProc == 0) // Or nextProc == nullptr
        {
            totalSimulatedCycles += 10;
        }
        else 
        {
            int cyclesUsed = nextProc->useCPU(totalSimulatedCycles, 10);
            totalSimulatedCycles += cyclesUsed;

            sched->addProcess(nextProc);
        }
    }

    auto endTime = std::chrono::system_clock::now();

    auto duration = endTime - startTime;
    auto durationNS = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

    double timePerOperation = static_cast<double>(durationNS.count()) / popNextCalls;

    double totalCpuTime_CPU = 0;
    double totalWaitTime_CPU = 0;

    for (int i = 0; i < cpuProcs.getSize(); i++)
    {
        Process* p = cpuProcs.getItem(i);
        totalCpuTime_CPU += p->getCPUTime();
        totalWaitTime_CPU += p->getWaitTime(totalSimulatedCycles);
    }

    double totalCpuTime_IO = 0;
    double totalWaitTime_IO = 0;

    for (int i = 0; i < ioProcs.getSize(); i++)
    {
        Process* p = ioProcs.getItem(i);
        totalCpuTime_IO += p->getCPUTime();
        totalWaitTime_IO += p->getWaitTime(totalSimulatedCycles);
    }

    double avgCpuTime_CPU = (numCPUBound == 0) ? 0 : totalCpuTime_CPU / numCPUBound;
    double avgWaitTime_CPU = (numCPUBound == 0) ? 0 : totalWaitTime_CPU / numCPUBound;
    double avgCpuTime_IO = (numIOBound == 0) ? 0 : totalCpuTime_IO / numIOBound;
    double avgWaitTime_IO = (numIOBound == 0) ? 0 : totalWaitTime_IO / numIOBound;

    double* stats = new double[5];
    stats[0] = timePerOperation;
    stats[1] = avgCpuTime_CPU;
    stats[2] = avgWaitTime_CPU;
    stats[3] = avgCpuTime_IO;
    stats[4] = avgWaitTime_IO;

    for (int i = 0; i < cpuProcs.getSize(); i++)
    {
        delete cpuProcs.getItem(i);
    }

    for (int i = 0; i < ioProcs.getSize(); i++)
    {
        delete ioProcs.getItem(i);
    }

    return stats;
}