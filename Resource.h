#ifndef RESOURCE_H
#define RESOURCE_H
#include<string>
#include<queue>
#include"Semaphore.h"
#include"PCB.h"
class Process_control;
class Resource
{
    public:
        string name;
        Semaphore sem;
        Process_control &controller;
        PCB* running_process=NULL;
        queue<PCB*> wait_queue;
    
        Resource(string _name,Semaphore _sem,Process_control& _controller)
            :name(_name),sem(_sem),controller(_controller){}

        void P(PCB* pcb);
        void V();
        void show_wait_queue();
};
#endif