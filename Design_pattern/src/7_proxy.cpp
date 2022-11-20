#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Base
{
public:
    virtual void giveFlower() = 0;
    virtual void giveDoll() = 0;
};

class SchoolGirl
{
public:
    string get_name()
    {
        return name;
    }
    void set_name(string a)
    {
        name = a;
    }

private:
    string name;
};

class Pursuit : public Base
{
public:
    Pursuit(SchoolGirl a) : mm(a) {}
    void giveFlower()
    {
        cout << "give flower to " << mm.get_name() << endl;
    }
    void giveDoll()
    {
        cout << "give doll to " << mm.get_name() << endl;
    }

private:
    SchoolGirl mm;
};

class Proxy : public Base
{
public:
    Proxy(SchoolGirl a)
    {
        gg = std::make_shared<Pursuit>(a);
    }
    void giveFlower()
    {
        gg->giveFlower();
    }
    void giveDoll()
    {
        gg->giveDoll();
    }

private:
    std::shared_ptr<Pursuit> gg;
};

int main()
{
    SchoolGirl mm;
    mm.set_name("abc");

    std::shared_ptr<Proxy> ww = std::make_shared<Proxy>(mm);

    ww->giveFlower();
    ww->giveDoll();
}