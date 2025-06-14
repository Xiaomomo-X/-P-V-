#include"Process_control.h"

//创建进程
PCB* Process_control::create_process(string name)
{
    PC++;
    PCB* pcb=new PCB(PC,name);
    ready_queue.push(pcb);
    all_processes.push_back(pcb);
    cout<<"创建进程"<<pcb->pid<<"  "<<pcb->name<<endl;
    return pcb;
}

//阻塞进程
void Process_control::block_process(PCB* pcb)
{
    PCB* target=NULL;
    for(auto iter=all_processes.begin();iter!=all_processes.end();iter++)
    {
        if((*iter)==pcb)
        {
            (*iter)->state=block;
            block_queue.push(*iter);
            cout<<"进程"<<(*iter)->name<<"被阻塞"<<endl;
            target=(*iter);
            break;
        }
    }

    //用临时队列来删除就绪队列中的阻塞进程
    queue<PCB*> temp;
    while(!ready_queue.empty())
    {
        PCB* pcb=ready_queue.front();
        ready_queue.pop();
        if(pcb!=target)
        {
            temp.push(pcb);
        }  
    }
    ready_queue=temp;
}

//唤醒进程
void Process_control::wakeup_process(PCB *pcb)
{
    PCB* target=NULL;
    for(auto iter=all_processes.begin();iter!=all_processes.end();iter++)
    {
        if((*iter)==pcb)
        {
            (*iter)->state=ready;
            ready_queue.push(*iter);
            cout<<"进程"<<(*iter)->name<<"被唤醒"<<endl;
            target=(*iter);
            break;
        }
    }
    queue<PCB*> temp;
    while(!block_queue.empty())
    {
        PCB *pcb=block_queue.front();
        block_queue.pop();
        if(pcb!=target)
        {
            temp.push(pcb);
        }
    }
    block_queue=temp;
}

//终止进程
void Process_control::over_process(PCB* pcb)
{
    for(auto iter=all_processes.begin();iter!=all_processes.end();iter++)//vector.begin()返回的是首元素的地址
    {
        if((*iter)==pcb)
        {
            (*iter)->state=exist;
            cout<<"进程"<<(*iter)->name<<"终止"<<endl;
            remove_from_ready_queue((*iter));
            remove_from_ready_queue((*iter));
            all_processes.erase(iter);
            return ;
        }
    }
    cout<<"进程不存在"<<endl;
}

//从就绪进程中移出某个进程
void Process_control::remove_from_ready_queue(PCB* pcb) {
    std::queue<PCB*> temp;
    while (!ready_queue.empty()) 
    {
        PCB* pcb1 = ready_queue.front();
        ready_queue.pop();
        if (pcb1!=pcb)
        {
            temp.push(pcb1);
        }
    }
    ready_queue = temp;
}

//从阻塞进程中移出某个进程
void Process_control::remove_from_block_queue(PCB* pcb) {
    std::queue<PCB*> temp;
    while (!block_queue.empty()) 
    {
        PCB* pcb1 = block_queue.front();
        block_queue.pop();
        if (pcb1!=pcb)
        {
            temp.push(pcb1);
        }
    }
    block_queue = temp;
}

//添加就绪进程
void Process_control::add_to_ready_queue(PCB* pcb) 
{
    ready_queue.push(pcb);
}

//添加阻塞进程
void Process_control::add_to_block_queue(PCB* pcb)
{
    block_queue.push(pcb);
}

//发送消息给某个进程
void Process_control::send_message(int to_pid,string content)
{
    PCB* receiver=get_process(to_pid);
    if(!receiver)
    {
        cout<<"不存在该进程，消息发送失败"<<endl;
    }
    else
    {
        receiver->message_queue.push(content);
        cout<<"给进程"<<receiver->name<<"发送消息成功"<<endl;
    }
}

//接收来自进程的消息
string Process_control::receive_message(int from_pid)
{
    PCB* receiver=get_process(from_pid);
    if(!receiver)
    {
        return "不存在该进程,接收消息失败";
    }

    if(receiver->message_queue.empty())
    {
        return "消息接收失败，该进程无可发送消息";
    }

    string message=receiver->message_queue.front();
    receiver->message_queue.pop();
    return message;
}
//取某个进程
PCB* Process_control::get_process(int pid)
{

    for(auto &pcb: all_processes)
    {
        if(pcb->pid==pid)
        {
            cout<<"存在该进程，已返回"<<endl;
            return pcb;
        }
    }
    cout<<"不存在该进程"<<endl;
    return NULL;      
}

//显示所有进程信息
void Process_control::show_all_processes()
{
    cout<<"所有进程"<<endl;
    if(all_processes.empty())
    {
        cout<<"无进程"<<endl;
    }
    for(auto &pcb: all_processes)
    {
        cout<<"进程id: "<<pcb->pid<<" 进程名称："<<pcb->name<<" 进程状态："<<pcb->state<<endl;
    }
}

//显示就绪进程
void Process_control::show_ready_processes()
{
    cout<<"就绪进程"<<endl;
    queue<PCB*> temp=ready_queue;
    if(temp.empty())
    {
        cout<<"无就绪进程"<<endl;
    }
    while(!temp.empty())
    {
        PCB* pcb=temp.front();
        temp.pop();
        cout<<"进程id: "<<pcb->pid<<" 进程名称："<<pcb->name<<" 进程状态："<<pcb->state<<endl;
    }
}

//显示阻塞进程
void Process_control::show_block_processes()
{
    cout<<"阻塞进程"<<endl;
    queue<PCB*> temp=block_queue;
    if(temp.empty())
    {
        cout<<"无阻塞进程"<<endl;
    }
    while(!temp.empty())
    {
        PCB* pcb=temp.front();
        temp.pop();
        cout<<"进程id: "<<pcb->pid<<" 进程名称："<<pcb->name<<" 进程状态："<<pcb->state<<endl;
    }
}

//为了方便，直接写个函数吧所有进程终止
void Process_control::over_all_processes()
{
    for(PCB* &pcb: all_processes)
    {
        delete pcb;
    }
    all_processes.clear();
    while(!ready_queue.empty())
    {
        ready_queue.pop();
    }
    while(!block_queue.empty())
    {
        block_queue.pop();
    }
    cout<<"已清空所有进程"<<endl;
}