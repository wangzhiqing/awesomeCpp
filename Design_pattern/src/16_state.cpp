#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class Work;
class State
{
public:
    virtual void write_program(Work *w) = 0;
};

class ForenoonState : public State
{
public:
    virtual void write_program(Work *w);
};

class Work
{
public:
    Work()
    {
        cur = new ForenoonState();
    }
    void write_program()
    {
        cur->write_program(this);
    }
    void SetState(State *next)
    {
        cur = next;
    }
    float hour;
    bool taskFinished = false;

private:
    State *cur;
};

class SleepState : public State
{
public:
    void write_program(Work *w)
    {
        cout << w->hour << " 睡觉" << endl;
    }
};

class RestState : public State
{
public:
    void write_program(Work *w)
    {
        cout << w->hour << " 休息" << endl;
    }
};

class EveningState : public State
{
public:
    void write_program(Work *w)
    {
        if (w->taskFinished)
        {
            w->SetState(new RestState());
            w->write_program();
        }
        else
        {
            if (w->hour < 21)
            {
                cout << w->hour << "晚上加班" << endl;
            }
            else
            {
                w->SetState(new SleepState());
                w->write_program();
            }
        }
    }
};

class AfternoonState : public State
{
public:
    void write_program(Work *w)
    {
        if (w->hour < 17)
        {
            cout << w->hour << "下午工作" << endl;
        }
        else
        {
            w->SetState(new EveningState());
            w->write_program();
        }
    }
};

class NoonState : public State
{
public:
    void write_program(Work *w)
    {
        if (w->hour < 13)
        {
            cout << w->hour << "中午休息" << endl;
        }
        else
        {
            w->SetState(new AfternoonState());
            w->write_program();
        }
    }
};

void ForenoonState::write_program(Work *w)
{

    if (w->hour < 12)
    {
        cout << w->hour << "上午工作" << endl;
    }
    else
    {
        w->SetState(new NoonState());
        w->write_program();
    }
}

int main()
{
    Work *pro = new Work();
    pro->hour = 9;
    pro->write_program();
    pro->hour = 12;
    pro->write_program();
    pro->hour = 13;
    pro->write_program();
    pro->hour = 17;
    pro->taskFinished = true;
    pro->write_program();
}