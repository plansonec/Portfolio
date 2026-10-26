#include <iostream>
#include "Simulate.hpp"
#include "Scheduler.hpp" 

using namespace std;

int main(int argc, char** argv)
{
   // Error checker
   if (argc != 4)
   {
      cout << "Usage: ./schedulesim <numCPUBound> <numIOBound> <numCycles>" << endl;
      cout << "Example: ./schedulesim 10 5 100000" << endl;
      return 1;
   }

   int numCPUBound = atoi(argv[1]);
   int numIOBound = atoi(argv[2]);
   int numCycles = atoi(argv[3]);

   // Create all three schedulers
   Scheduler* schedArr[] = {
       new RoundRobin(), 
       new FastRoundRobin(), 
       new CompletelyFair()  // <-- Now active!
   };

   string labels[] = {
       "Round Robin (Array List)", 
       "Round Robin (Linked List)", 
       "Completely Fair (BST)"
   };
   
   // Loop through all 3 schedulers
   for(int i = 0; i < 3; i++)
   {
      double* results = simulate(schedArr[i], numCPUBound, numIOBound, numCycles);
      cout << labels[i] << endl;
      cout << "Time per schedule: " << results[0] << endl;
      cout << "CPU Bound CPU Time: " << results[1] << endl;
      cout << "CPU Bound Wait Time: " << results[2] << endl;
      cout << "IO Bound CPU Time: " << results[3] << endl;
      cout << "IO Bound Wait Time: " << results[4] << endl << endl;
      delete[] results;
      delete schedArr[i];
   }
}