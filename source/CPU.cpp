#include "../headers/CPU.h"

CPU::CPU(DList<PCB> *fq, DList<PCB> *bq, Clock *cl, int tq)
{
    pcb = NULL;
    idle = true;
    finished_queue = fq;
    blocked_queue = bq;
    clock = cl;
    timeq = tq;
}

// used by others to determine what the cpu is working on like priority and time left
PCB *CPU::getpcb()
{
    return pcb;
}

// check to see if cpu is currently working on a process
bool CPU::isidle()
{
    return idle;
}

// called every clock cycle
void CPU::execute()
{
    if (pcb != NULL)
    {
        idle = false;
        if (!pcb->started)
        {
            pcb->started = true;
            pcb->resp_time = clock->gettime() - pcb->arrival;
        }
        pcb->time_left -= 0.5;     // Simulate half a time unit
        pcb->cpu_time_used += 0.5; // Increment CPU time used

        // Debug statements
        std::cout << "CPU Time: " << clock->gettime()
                  << ", PID: " << pcb->pid
                  << ", CPU Time Used: " << pcb->cpu_time_used
                  << ", Time Quantum/2: " << (timeq / 2)
                  << ", Has Blocked: " << (pcb->has_blocked ? "Yes" : "No")
                  << ", I/O Burst: " << pcb->io_burst << std::endl;

        // Check if the process needs to be blocked
        if (!pcb->has_blocked && pcb->io_burst > 0 && pcb->cpu_time_used >= (timeq / 2))
        {
            std::cout << "Blocking process PID: " << pcb->pid << std::endl;
            block();
            idle = true;
            return;
        }

        if (pcb->time_left <= 0)
        {
            terminate();
            idle = true;
        }
    }
}

void CPU::block()
{
    pcb->has_blocked = true; // Set has_blocked to true
    pcb->cpu_time_used = 0;  // Reset CPU time used
    blocked_queue->add_end(*pcb);
    delete pcb;
    pcb = NULL;
}

// routine to update termination related stats, for StatUpdater to use later
void CPU::terminate()
{
    pcb->finish_time = clock->gettime() + .5;
    finished_queue->add_end(*pcb);
    delete pcb;
    pcb = NULL;
}