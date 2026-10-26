#include "Process.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

/*
What it Does: Constructs a new Process object.
What it Takes: The unique identifier for this process (id).
Effects: Initializes the process with the given id, and sets
 cpuTime and waitTime to 0.
What it Returns: N/A (it's a constructor)
*/
Process::Process(int id) : id(id)
{
   cpuTime = 0;
   waitTime = 0;
}

/*
What it Does: Gets the process's unique ID.
What it Takes: Nothing.
Effects: None.
What it Returns: The integer ID of the process.
*/
int Process::getID() const
{
   return id;
}

/*
What it Does: Gets the total CPU time consumed by the process so far.
What it Takes: Nothing.
Effects: None.
What it Returns: The total accumulated CPU time in cycles.
*/
int Process::getCPUTime() const
{
   return cpuTime;
}

/*
What it Does: Gets the total time the process has spent waiting for the CPU.
What it Takes: The current cycle number of the simulation (curCycleNum).
Effects: Calculates any additional wait time since the process
 was last active and adds it to the total.
What it Returns: The total accumulated wait time in cycles.
*/
int Process::getWaitTime(int curCycleNum) const
{
   int additionalWait = curCycleNum - lastTime;
   if(additionalWait < 0)
   {
      additionalWait = 0;
   }
   return waitTime + additionalWait;
}

/*
What it Does: Constructs a new CPUBoundProcess object.
What it Takes: The unique identifier for this process (id).
Effects: Calls the base Process constructor and initializes
 lastTime to 0.
What it Returns: N/A (it's a constructor)
*/
CPUBoundProcess::CPUBoundProcess(int id) : Process(id)
{
   lastTime = 0;
}

/*
What it Does: Checks if the process is currently blocked.
What it Takes: The current cycle number of the simulation (curCycleNum).
Effects: None.
What it Returns: Always returns false, as a CPUBoundProcess is never blocked.
*/
bool CPUBoundProcess::isBlocked(int curCycleNum) const
{
   return false;
}

/*
What it Does: Simulates the process using the CPU for a given time slice.
What it Takes: 
 - The current cycle number of the simulation (curCycleNum).
 - The number of cycles given to the process (sliceSize).
Effects: 
 - Increases cpuTime by the full sliceSize.
 - Calculates and adds to waitTime.
 - Updates lastTime to the end of this slice.
What it Returns: The number of cycles used, which is always the full sliceSize.
*/
int CPUBoundProcess::useCPU(int curCycleNum, int sliceSize)
{
   //The process uses all CPU time given to it
   cpuTime += sliceSize;
   
   waitTime += curCycleNum - lastTime;
   //When the process next uses the CPU, it will have been
   //waiting since the end of this window.
   lastTime = curCycleNum + sliceSize;

   return sliceSize;
}

/*
What it Does: Constructs a new IOBoundProcess object.
What it Takes: The unique identifier for this process (id).
Effects: Calls the base Process constructor and initializes
 burst/IO times and state variables (lastTime,
 blockedUntil, remainingBurst) to 0.
What it Returns: N/A (it's a constructor)
*/
IOBoundProcess::IOBoundProcess(int id) : Process(id), minBurst(5), maxBurst(15), minIO(50), maxIO(200)
{
   lastTime = 0;
   blockedUntil = 0;
   remainingBurst = 0;
}

/*
What it Does: Checks if the process is currently blocked waiting for I/O.
What it Takes: The current cycle number of the simulation (curCycleNum).
Effects: None.
What it Returns: True if curCycleNum is less than the process's
 blockedUntil time, false otherwise.
*/
bool IOBoundProcess::isBlocked(int curCycleNum) const
{
   return curCycleNum < blockedUntil;
}

/*
What it Does: Simulates the process using the CPU for a given time slice.
What it Takes: 
 - The current cycle number of the simulation (curCycleNum).
 - The number of cycles given to the process (sliceSize).
Effects: 
 - May use the full sliceSize or only part of it before
   blocking for I/O.
 - Randomly determines a new CPU burst time if unblocked.
 - Randomly determines a new I/O block time if a burst completes.
 - Updates cpuTime, waitTime, and lastTime based on usage.
What it Returns: The number of cycles actually used (<= sliceSize).
*/
int IOBoundProcess::useCPU(int curCycleNum, int sliceSize)
{
   //If the process was blocked, and is now unblocked,
   //choose a length for the next CPU burst
   if(curCycleNum >= blockedUntil && remainingBurst == 0)
   {
      remainingBurst = random()%(maxBurst - minBurst + 1) + minBurst;
   }

   int timeUsed = 0;
   if(remainingBurst > 0) //If the process is not blocked...
   {
      waitTime += curCycleNum - lastTime;

      if(remainingBurst > sliceSize) //If the whole window will be used...
      {
    remainingBurst -= sliceSize;
    timeUsed = sliceSize;

    //When the process next uses the CPU, it will have been
    //waiting since the end of this window.
    lastTime = curCycleNum + sliceSize;
      }
      else //Otherwise the process will block without using the whole window
      {
    timeUsed = remainingBurst;
    remainingBurst = 0;

    //Choose a time for the IO request to complete
    blockedUntil = curCycleNum + timeUsed + random()%(maxIO - minIO + 1) + minIO;
    //When the process next uses the CPU, it will have been
    //waiting since it unblocked (not since the end of this window).
    lastTime = blockedUntil;
      }
   }

   cpuTime += timeUsed;
   return timeUsed;
}