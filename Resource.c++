#include"Resource.h"
#include"Process_control.h"
void Resource::P(PCB* pcb)
{
    sem.value--;
    if(sem.value<0)
    {
        pcb->state=block;
        pcb->waiting_sem=sem.name;
        wait_queue.push(pcb);
        controller.remove_from_ready_queue(pcb);
        controller.add_to_block_queue(pcb);
        cout<<"进程"<<pcb->pid<<"被阻塞到信号量"<<name<<"中"<<endl;
    }
    else
    {
        pcb->state=running;
        controller.remove_from_ready_queue(pcb);
        running_process=pcb;
        cout<<"进程"<<pcb->pid<<"获得信号量"<<endl;
    }
}

void Resource::V()
{
    if(running_process)
    {
        PCB* pcb=running_process;
        pcb->state=exist;
        controller.over_process(pcb);
        running_process=NULL;
    }
    sem.value++;
    if(sem.value<=0&&!wait_queue.empty())
    {
        PCB* pcb=wait_queue.front();
        wait_queue.pop();
        pcb->state=ready;
        pcb->waiting_sem=" ";
        controller.wakeup_process(pcb);
        cout<<"唤醒进程"<<pcb->name<<endl;
    }
}


void Resource::show_wait_queue()
{
    cout<<"信号量"<<name<<"中的等待队列"<<endl;
    queue<PCB*> temp=wait_queue;
    if(temp.empty())
    {
        cout<<"信号量"<<name<<"无阻塞进程"<<endl;
    }
    else
    {
        while(!temp.empty())
        {
            PCB* pcb=temp.front();
            temp.pop();
            cout<<"进程id: "<<pcb->pid<<" 进程名称："<<pcb->name<<" 进程状态："<<pcb->state<<endl;
        }
    }
}