#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
#include <map>
using namespace std;

class Man;
class Woman;

class Action
{
public:
    virtual void get_man_state(Man *m) = 0;
    virtual void get_woman_state(Woman *m) = 0;
};

class Person
{
public:
    Person(string v) : name(v) {}
    virtual void accept(Action *a) = 0;
    string name;
};

class Man : public Person
{
public:
    Man(string v) : Person(v) {}
    void accept(Action *a)
    {
        a->get_man_state(this);
    }
};

class Woman : public Person
{
public:
    Woman(string v) : Person(v) {}
    void accept(Action *a)
    {
        a->get_woman_state(this);
    }
};

class Success : public Action
{
public:
    void get_man_state(Man *m)
    {
        cout << "男人" << m->name << "成功" << endl;
    }
    void get_woman_state(Woman *m)
    {
        cout << "女人" << m->name << "成功" << endl;
    }
};

class Failing : public Action
{
public:
    void get_man_state(Man *m)
    {
        cout << "男人" << m->name << "失败" << endl;
    }
    void get_woman_state(Woman *m)
    {
        cout << "女人" << m->name << "失败" << endl;
    }
};

class ObjectStructure
{
public:
    void add(Person *p)
    {
        ele.push_back(p);
    }
    void remove(Person *p)
    {
        ele.remove(p);
    }
    void display(Action *a)
    {
        for (auto &i : ele)
        {
            i->accept(a);
        }
    }

private:
    list<Person *> ele;
};

int main()
{
    ObjectStructure obj;
    Man *mA = new Man("xiaowang");
    Woman *wB = new Woman("xiaoli");
    obj.add(mA);
    obj.add(wB);

    Success *sA = new Success();
    obj.display(sA);

    Failing *fA = new Failing();
    obj.display(fA);
}
