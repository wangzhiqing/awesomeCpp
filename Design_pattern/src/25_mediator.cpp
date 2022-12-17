#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
using namespace std;

class Country;

class UnitedNations
{
public:
    virtual void declare(string message, Country *c) = 0;
};

class Country
{
public:
    std::shared_ptr<UnitedNations> mediator;
    Country(std::shared_ptr<UnitedNations> m) : mediator(m) {}
};

class USA : public Country
{
public:
    USA(std::shared_ptr<UnitedNations> m) : Country(m) {}
    void declare(string message)
    {
        mediator->declare("美国要" + message, this);
    }
    void get_message(string message)
    {
        cout << "USA 获取消息: " << message << endl;
    }
};

class China : public Country
{
public:
    China(std::shared_ptr<UnitedNations> m) : Country(m) {}
    void declare(string message)
    {
        mediator->declare("中国要"+ message, this);
    }
    void get_message(string message)
    {
        cout << "China 获取消息: " << message << endl;
    }
};

class UnitedNationsSecurityCouncil : public UnitedNations
{
public:
    void set_usa(std::shared_ptr<USA> a)
    {
        countryA = a;
    }
    void set_china(std::shared_ptr<China> b)
    {
        countryB = b;
    }
    void declare(string message, Country *c)
    {
        if (c == countryA.get())
        {
            countryB->get_message(message);
        }
        else if (c == countryB.get())
        {
            countryA->get_message(message);
        }
    }

private:
    std::shared_ptr<USA> countryA;
    std::shared_ptr<China> countryB;
};

int main()
{
    std::shared_ptr<UnitedNationsSecurityCouncil> un = std::make_shared<UnitedNationsSecurityCouncil>();
    std::shared_ptr<USA> a = std::make_shared<USA>(un);
    std::shared_ptr<China> b = std::make_shared<China>(un);

    un->set_usa(a);
    un->set_china(b);

    a->declare("禁止华为!!!");
    b->declare("禁止苹果!!!");
}
