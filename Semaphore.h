#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include<string>
using namespace std;
//信号量
class Semaphore
{
    public:
        string name;
        int value;

        Semaphore(){}
        Semaphore(string _name,int _value)
            :name(_name),value(_value){}
};
#endif