#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class Company
{
public:
    string name;
    Company(string n) : name(n) {}
    virtual void add(std::shared_ptr<Company> c) = 0;
    virtual void remove(std::shared_ptr<Company> c) = 0;
    virtual void display(int depth) = 0;
    virtual void work() = 0;
};

class ConcreteCompany : public Company
{
public:
    ConcreteCompany(string n) : Company(n) {}
    virtual void add(std::shared_ptr<Company> c)
    {
        child_c.push_back(c);
    }
    virtual void remove(std::shared_ptr<Company> c)
    {
        child_c.remove(c);
    }
    virtual void display(int depth)
    {
        cout << depth << "---" << name << endl;
        for (auto &i : child_c)
        {
            i->display(depth + 1);
        }
    }
    virtual void work()
    {
        for (auto &i : child_c)
        {
            i->work();
        }
    }

private:
    list<std::shared_ptr<Company>> child_c;
};

class HRDepartment : public Company
{
public:
    HRDepartment(string n) : Company(n) {}
    virtual void add(std::shared_ptr<Company> c)
    {
    }
    virtual void remove(std::shared_ptr<Company> c)
    {
    }
    virtual void display(int depth)
    {
        cout << depth << "---" << name << endl;
    }
    virtual void work()
    {
        cout << name << " HR 工作" << endl;
    }
};

class FinanceDepartment : public Company
{
public:
    FinanceDepartment(string n) : Company(n) {}
    virtual void add(std::shared_ptr<Company> c)
    {
    }
    virtual void remove(std::shared_ptr<Company> c)
    {
    }
    virtual void display(int depth)
    {
        cout << depth << "---" << name << endl;
    }
    virtual void work()
    {
        cout << name << " 财务 工作" << endl;
    }
};

int main()
{
    std::shared_ptr<ConcreteCompany> root_c = std::make_shared<ConcreteCompany>("北京总部");
    root_c->add(std::make_shared<HRDepartment>("HR部门"));
    root_c->add(std::make_shared<FinanceDepartment>("财务部门"));

    std::shared_ptr<ConcreteCompany> sh_c = std::make_shared<ConcreteCompany>("上海分部");
    sh_c->add(std::make_shared<HRDepartment>("上海 HR部门"));
    sh_c->add(std::make_shared<FinanceDepartment>("上海 财务部门"));

    root_c->add(sh_c);

    root_c->display(1);
    root_c->work();
}