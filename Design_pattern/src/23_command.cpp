#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
using namespace std;

class Barbecuer
{
public:
    void bake_mutton()
    {
        cout << "烤羊肉串" << endl;
    }
    void bake_chicken()
    {
        cout << "烤鸡" << endl;
    }
};

class Command
{
public:
    Command(std::shared_ptr<Barbecuer> b) : receiver(b) {}
    virtual void exec_command() = 0;

protected:
    std::shared_ptr<Barbecuer> receiver;
};

class BakeMuttonCommand : public Command
{
public:
    BakeMuttonCommand(std::shared_ptr<Barbecuer> b) : Command(b) {}
    virtual void exec_command()
    {
        receiver->bake_mutton();
    }
};

class BakeChickenCommand : public Command
{
public:
    BakeChickenCommand(std::shared_ptr<Barbecuer> b) : Command(b) {}
    virtual void exec_command()
    {
        receiver->bake_chicken();
    }
};

class Waiter
{
public:
    void set_command(std::shared_ptr<Command> com)
    {
        c.push_back(com);
    }
    void notify()
    {
        for (auto &i : c)
        {
            i->exec_command();
        }
    }
    void cancel(std::shared_ptr<Command> com)
    {
        cout << "取消订单" << endl;
        c.remove(com);
    }

private:
    list<std::shared_ptr<Command>> c;
};

int main()
{
    std::shared_ptr<Barbecuer> b = std::make_shared<Barbecuer>();
    std::shared_ptr<Command> com_1 = std::make_shared<BakeMuttonCommand>(b);
    std::shared_ptr<Command> com_2 = std::make_shared<BakeChickenCommand>(b);
    std::shared_ptr<Command> com_3 = std::make_shared<BakeChickenCommand>(b);

    std::shared_ptr<Waiter> w = std::make_shared<Waiter>();
    w->set_command(com_1);
    w->set_command(com_2);
    w->set_command(com_3);
    w->cancel(com_3);
    w->notify();
}
