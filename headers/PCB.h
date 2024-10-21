//
// Created by Joseph on 10/7/2017.
//

#ifndef LAB2_PCB_H
#define LAB2_PCB_H

#include <iostream>

// data structure to hold process information
struct PCB
{
    int pid, arrival, burst, priority, num_context;
    float time_left, resp_time, wait_time, finish_time;
    bool started;
    int io_burst;
    int initial_io_burst; // Store the initial I/O Burst time
    bool has_blocked;
    float cpu_time_used;

    PCB()
    {
        pid = arrival = burst = priority = num_context = io_burst = initial_io_burst = 0;
        time_left = resp_time = wait_time = finish_time = cpu_time_used = 0;
        started = has_blocked = false;
    }
    PCB(int id, int arr, int time, int prio, int io) : pid(id), arrival(arr), burst(time), time_left(time),
                                                       priority(prio), io_burst(io), initial_io_burst(io), // Initialize both
                                                       has_blocked(false), cpu_time_used(0)
    {
        resp_time = wait_time = num_context = finish_time = 0;
        started = false;
    }
    void print()
    {
        std::cout << pid << " " << arrival << " " << time_left << " " << priority << " " << initial_io_burst << std::endl;
    }
};
#endif // LAB2_PCB_H
