#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class Subject;

class Observer
{
protected:
    string name;
    Subject *sub;

public:
    Observer(string nameS, Subject *subPtr) : name(nameS), sub(subPtr) {}
    virtual void update() = 0;
};

class Subject
{
public:
    virtual void attach(Observer *o) = 0;
    virtual void detach(Observer *o) = 0;
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
private:
    list<Observer *> obs_list;

public:
    virtual void attach(Observer *o)
    {
        obs_list.push_back(o);
    };
    virtual void detach(Observer *o)
    {
        obs_list.remove(o);
    };
    virtual void notify()
    {
        for (auto i : obs_list)
        {
            i->update();
        }
    };
};

class Secretary : public Subject
{
private:
    list<Observer *> obs_list;

public:
    virtual void attach(Observer *o)
    {
        obs_list.push_back(o);
    };
    virtual void detach(Observer *o)
    {
        obs_list.remove(o);
    };
    virtual void notify()
    {
        for (auto i : obs_list)
        {
            i->update();
        }
    };
};

class StockObs : public Observer
{

public:
    StockObs(string nameS, Subject *subPtr) : Observer(nameS, subPtr) {}
    virtual void update()
    {
        cout << sub->get_state() << " " << name << " 关闭股票" << endl;
    }
};

class SoccerObs : public Observer
{

public:
    SoccerObs(string nameS, Subject *subPtr) : Observer(nameS, subPtr) {}
    virtual void update()
    {
        cout << sub->get_state() << " " << name << " 关闭球赛" << endl;
    }
};

int main()
{
    Boss *b = new Boss();
    SoccerObs *a1 = new SoccerObs("xiaowang", b);
    StockObs *a2 = new StockObs("xiaoli", b);

    b->attach(a1);
    b->attach(a2);
    b->detach(a1);
    b->set_state("回来了！！！");
    b->notify();
}