#include<iostream>
#include<string>
#include<map>
#include"PCB.h"
#include"Semaphore.h"
#include"Resource.h"
#include"Process_control.h"
using namespace std;


int main()
{
    Process_control controller;
    map<string, Semaphore> semaphores;
    map<string, Resource*> resources;

    while(true)
    {
        cout << "\n===== 菜单 =====\n"
             << "1. 创建进程\n"
             << "2. 创建信号量\n"
             << "3. 创建资源\n"
             << "4. 申请资源 (P操作)\n"
             << "5. 释放资源 (V操作)\n"
             << "6. 显示所有进程\n"
             << "7. 显示就绪队列\n"
             << "8. 显示阻塞队列\n"
             << "9. 显示资源等待队列\n"
             << "0. 退出\n请输入选择:";
        int choice;
        cin >> choice;

        if(choice == 0)
        {
            controller.over_all_processes();
            break;
        }
        else if(choice == 1)//创建进程
        {
            string name;
            cout << "输入进程名称：";
            cin >> name;
            controller.create_process(name);
        }
        else if(choice == 2)//创建信号量
        {
            string name;
            int value;
            cout << "输入信号量名称 和 初始值：";
            cin >> name >> value;
            semaphores[name] = Semaphore(name, value);
            cout << "信号量 " << name << " 创建成功"<<endl;
        }
        else if(choice == 3)//创建资源
        {
            string res_name, sem_name;
            cout << "输入资源名称 和 绑定的信号量名称：";
            cin >> res_name >> sem_name;
            if(semaphores.find(sem_name) == semaphores.end())
            {
                cout << "信号量不存在，先创建信号量\n";
                continue;
            }
            // 注意：用信号量副本创建 Resource
            resources[res_name] = new Resource(res_name, semaphores[sem_name], controller);
            cout << "资源 " << res_name << " 创建成功 "<<endl;
        }
        else if(choice == 4)//申请资源（P）
        {
            string res_name;
            int pid;
            cout << "输入资源名 和 请求资源的进程PID: ";
            cin >> res_name >> pid;
            if(resources.find(res_name) == resources.end())
            {
                cout << "资源不存在\n";
                continue;
            }
            PCB* pcb = controller.get_process(pid);
            if(pcb)
                resources[res_name]->P(pcb);
        }
        else if(choice == 5)//释放资源（V）
        {
            string res_name;
            cout << "输入资源名：";
            cin >> res_name;
            if(resources.find(res_name) == resources.end())
            {
                cout << "资源不存在\n";
                continue;
            }
            resources[res_name]->V();
        }
        else if(choice == 6)//显示所有进程
        {
            controller.show_all_processes();
        }
        else if(choice == 7)//显示就绪进程
        {
            controller.show_ready_processes();
        }
        else if(choice == 8)//显示阻塞进程
        {
            controller.show_block_processes();
        }
        else if(choice == 9)//显示资源等待的进程
        {
            string res_name;
            cout << "输入资源名：";
            cin >> res_name;
            if(resources.find(res_name) != resources.end())
                resources[res_name]->show_wait_queue();
            else
                cout << "资源不存在\n";
        }
    }

    return 0;
}