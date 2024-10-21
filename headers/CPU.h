#ifndef LAB2_CPU_H
#define LAB2_CPU_H

#include "PCB.h"
#include "DList.h"
#include "Clock.h"
#include "Schedulers.h"

class Dispatcher;

class CPU
{
private:
    PCB *pcb;
    bool idle;
    Clock *clock;
    DList<PCB> *finished_queue; // For terminated processes
    DList<PCB> *blocked_queue;  // For blocked processes
    int timeq;                  // Time quantum
    friend Dispatcher;

public:
    CPU(DList<PCB> *fq, DList<PCB> *bq, Clock *cl, int tq);
    PCB *getpcb();
    bool isidle();
    void execute();
    void terminate();
    void block(); // Method to handle blocking
};

#endif
