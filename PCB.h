#ifndef PCB_H
#define PCB_H

//进程控制块（结构体）
#include<string>
#include<queue>
using namespace std;
enum process_state{ready,running,block,exist};

//进程控制块
class PCB
{
    public:
        int pid;
        string name;
        process_state state;
        string waiting_sem;//阻塞时等待的信号量
        queue<string> message_queue;//消息队列
        PCB(int _pid,string _name):pid(_pid),name(_name),state(ready){}
};
#endif

