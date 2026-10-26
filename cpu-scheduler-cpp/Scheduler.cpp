#include "Scheduler.hpp"
#include "ArrayList.hpp"

RoundRobin::RoundRobin()
{
    procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin()
{
    delete procQueue;
}

void RoundRobin::addProcess(Process* proc)
{
    procQueue->pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle)
{
    int procsToCheck = procQueue->getSize();

    for (int i = 0; i < procsToCheck; i++)
    {
        Process* proc = procQueue->getFront();

        if (proc->isBlocked(curCycle))
        {
            procQueue->popFront();
            procQueue->pushBack(proc);
        }
        else
        {
            procQueue->popFront();
            return proc;
        }
    }

    return 0;
}

FastRoundRobin::FastRoundRobin()
{
    delete procQueue;
    procQueue = new LinkedList<Process*>();
}

CompletelyFair::CompletelyFair()
{
    procTree = new BSTMultimap<int, Process*>();
}

CompletelyFair::~CompletelyFair()
{
    delete procTree;
}

void CompletelyFair::addProcess(Process* proc)
{
    procTree->insert(proc->getCPUTime(), proc);
}

Process* CompletelyFair::popNext(int curCycle)
{
    BSTForwardIterator<int, Process*> it = procTree->getMin();

    while (!it.isPastEnd())
    {
        Process* p = it.getValue();

        if (!p->isBlocked(curCycle))
       {
            procTree->remove(it);
            return p;
        }

        it.next();
    }

    return nullptr;
}