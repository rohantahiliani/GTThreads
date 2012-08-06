Project 1
Rohan Tahiliani
gtID#: 902837193

I used Fedora 13 with Intel (i386) 32-bit Architecture. The OS was running on VMWare Workstation with 2 cores.

To compile the library:

1) Place the code in a folder along with the 'Makefile' file.
2) Run the make command at the terminal.

To run the dining philosophers program using the library, place the file in the same directory and use the following command:

gcc -Wall -pedantic -I{...} -o runner runner.c gtthread.a

Note: If the program is in a different directory from the library files then add the path before the program name.


The preemptive scheduler was implemented by creating a 2-way-linked-list which contains all the threads that are in execution. 
A pointer holds information about the thread that is being executed currently. 
A ITIMER_PROF timer is used to trigger an alarm at an interval specified by the user.
When the SIGPROF signal is raised, the scheduler is called and it performs a context switch using the 'swapcontext' system call.
The current context is saved in the node which is going to be swapped out and the new context is loaded from the next thread to be scheduled.
While the context is being switched, all signals are blocked to avoid an inconsistent state.


To prevent deadlocks in the dining philosophers problem, a policy is adopted for the philosophers. Each philosopher can only pick up the higher numbered chopsticks first followed by the lower numbered chopstick.
Because of this, if the program only gives time for each philosopher to pick up 1 chopstick, 1 of the philosophers will be left without any chopstick and in the next round 1 of the philosophers will be able to eat.
This process will keep continuing and none of the philosophers will starve as there are 2 philosophers that have their highest numbered chopstick as 5.


As the library allows the user to decide the quantum for the scheduling, it gives better flexibility and hence provides for better scheduling policies as required by the program. 
A fixed scheduler might switch threads even though a program requires threads within the process to run for large time quantums. 
Such a program will perform much better with the GTThread library.
Also a preemptive round-robin scheduler fair scheduling policy.

This also happens to be a drawback of having a round-robin scheduler. There is no way for threads having higher priority to be able to execute for a longer period of time, or be scheduled before other low priority threads. 

