#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <map>
#include <functional>
using namespace std;

class Subject
{
public:
    virtual void notify() = 0;
    string get_state()
    {
        return state;
    }
    void set_state(string s)
    {
        state = s;
    }

protected:
    string state;
};

class Boss : public Subject
{
public:
    list<std::function<void()>> obs_list;
    virtual void notify()
    {
        for (auto i : obs_list)
        {
            i();
        }
    };
};

class Secretary : public Subject
{
public:
    list<std::function<void()>> obs_list;
    virtual void notify()
    {
        for (auto i : obs_list)
        {
            i();
        }
    };
};

class StockObs
{
    string name;
    Subject *sub;

public:
    StockObs(string nameS, Subject *subPtr) : name(nameS), sub(subPtr) {}
    void closePhone()
    {
        cout << sub->get_state() << " " << name << " 关闭股票" << endl;
    }
};

class SoccerObs
{
    string name;
    Subject *sub;

public:
    SoccerObs(string nameS, Subject *subPtr) : name(nameS), sub(subPtr) {}
    void closeTV()
    {
        cout << sub->get_state() << " " << name << " 关闭球赛" << endl;
    }
};

int main()
{
    Boss *b = new Boss();
    SoccerObs *a1 = new SoccerObs("xiaowang", b);
    StockObs *a2 = new StockObs("xiaoli", b);
    b->obs_list.push_back(std::bind(&SoccerObs::closeTV, *a1));
    b->obs_list.push_back(std::bind(&StockObs::closePhone, *a2));
    b->set_state("回来了！！！");
    b->notify();
}