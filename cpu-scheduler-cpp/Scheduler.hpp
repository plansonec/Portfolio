#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "List.hpp"
#include "Process.hpp"
#include "LinkedList.hpp"
#include "BSTMultimap.hpp"

class Scheduler
{
  public:
   virtual ~Scheduler() {}
   virtual void addProcess(Process* proc) = 0;
   virtual Process* popNext(int curCycle) = 0;
};

class RoundRobin : public Scheduler
{
    protected:
    List<Process*>* procQueue;

    public:
    RoundRobin();
    virtual ~RoundRobin();
    virtual void addProcess(Process* proc);
    virtual Process* popNext(int curCycle);
};

class FastRoundRobin : public RoundRobin
{
  public:
   FastRoundRobin();
   virtual ~FastRoundRobin() { }
};

class CompletelyFair : public Scheduler
{
  protected:
   BSTMultimap<int, Process*>* procTree;

  public:
   CompletelyFair();
   virtual ~CompletelyFair();
   virtual void addProcess(Process* proc);
   virtual Process* popNext(int curCycle);
};

#endif