#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
using namespace std;

enum RequestType
{
    REST,
    MONEY,
    BECEO
};

class Manager
{
public:
    Manager(string n) : name(n) {}
    virtual void process_request(RequestType type) = 0;
    void set_next(std::shared_ptr<Manager> m)
    {
        next_boss = m;
    }

protected:
    string name;
    std::shared_ptr<Manager> next_boss = nullptr;
};

class Stuff : public Manager
{
public:
    Stuff(string n) : Manager(n) {}
    void process_request(RequestType type)
    {
        if (type == REST)
        {
            cout << "ok, rest 1 day!!!" << endl;
        }
        else
        {
            if (next_boss != nullptr)
                next_boss->process_request(type);
        }
    }
};

class Director : public Manager
{
public:
    Director(string n) : Manager(n) {}
    void process_request(RequestType type)
    {
        if (type == REST)
        {
            cout << "ok, rest 3 day!!!" << endl;
        }
        else if (type == MONEY)
        {
            cout << "ok, give money!!!" << endl;
        }
        else
        {
            if (next_boss != nullptr)
                next_boss->process_request(type);
            cout << "无能为力" << endl;
        }
    }
};

int main()
{
    std::shared_ptr<Manager> xl = std::make_shared<Stuff>("XiaoLi");
    std::shared_ptr<Manager> xw = std::make_shared<Director>("XiaoWang");
    xl->set_next(xw);
    enum RequestType my_req = REST;
    xl->process_request(my_req);
    my_req = MONEY;
    xl->process_request(my_req);
    my_req = BECEO;
    xl->process_request(my_req);
}
