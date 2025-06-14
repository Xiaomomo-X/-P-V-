#ifndef PROCESS_CONTROL_H
#define PROCESS_CONTROL_H

#include<iostream>
#include<vector>
#include<queue>
#include"PCB.h"
using namespace std;

//进程调度器
class Process_control
{
    private:
        int PC=10000;//程序计数器，初始地址设置为10000
    public:

        queue<PCB*> ready_queue;//就绪队列
        queue<PCB*> block_queue;//阻塞队列
        vector<PCB*> all_processes;//用一个vector向量来保存已有的进程

        //创建进程
        PCB* create_process(string name);

        //阻塞进程
        void block_process(PCB* pcb);

        //唤醒进程
        void wakeup_process(PCB* pcb);

        //终止进程
        void over_process(PCB* pcb);
        
        //移出就绪队列
        void remove_from_ready_queue(PCB* pcb);

        //移出阻塞队列
        void remove_from_block_queue(PCB* pcb);

        //添加到就绪队列
        void add_to_ready_queue(PCB* pcb);

        //添加到阻塞队列
        void add_to_block_queue(PCB* pcb);

        //发送消息给某个进程
        void send_message(int to_pid,string content);

        //接收来自进程的消息
        string receive_message(int from_pid);

        //获取进程
        PCB* get_process(int pid);
        
        //展示所有进程
        void show_all_processes();

        //展示就绪进程
        void show_ready_processes();
        
        //展示阻塞进程
        void show_block_processes();
        
        //终止所有进程
        void over_all_processes();
};
#endif