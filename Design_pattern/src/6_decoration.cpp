#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Person
{
public:
    Person() {}
    Person(string a) : name(a) {}
    virtual void show()
    {
        cout << "装扮 " << name << endl;
    }

private:
    string name;
};

class Finery : public Person
{
public:
    Finery() {}
    void show()
    {
        if (component != nullptr)
        {
            component->show();
        }
    }
    void Decorate(std::shared_ptr<Person> a)
    {
        component = a;
    }

protected:
    std::shared_ptr<Person> component;
};

class TShirts : public Finery
{
public:
    TShirts() {}
    void show()
    {
        cout << "T恤" << endl;
        this->Finery::show();
    }
};

class BigTrouser : public Finery
{
public:
    BigTrouser() {}
    void show()
    {
        cout << "裤子" << endl;
        this->Finery::show();
    }
};

int main()
{

    std::shared_ptr<Person> shp_xc(new Person("wangzhiqing"));

    std::shared_ptr<TShirts> shp_ts(new TShirts());
    std::shared_ptr<BigTrouser> shp_bt(new BigTrouser());

    shp_bt->Decorate(shp_xc);
    shp_ts->Decorate(shp_bt);
    shp_ts->show();

    cout << "Shared ptr count:" << shp_xc.use_count() << endl;
}