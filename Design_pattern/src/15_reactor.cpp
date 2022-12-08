#include <string>
#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
class Base
{
public:
    Base()
    {

        strcpy(name, "Base");
    }

    virtual void display()

    {

        cout << "Display Base." << endl;
    }

protected:
    char name[64];
};

class Child1 : public Base

{

public:
    Child1()

    {

        strcpy(name, "Child1");
    }

    void display()
    {

        cout << "Display Child1." << endl;
    }
};

class Child2 : public Base
{
public:
    Child2()
    {

        strcpy(name, "Child2");
    }

    void display()

    {

        cout << "Display Child2." << endl;
    }
};

void Process(Base *type)
{

    if ((typeid(Child1)) == (typeid(*type)))
    {

        ((Child1 *)type)->display();
    }

    else if ((typeid(Child2)) == (typeid(*type)))

    {
        ((Child2 *)type)->display();
    }
    else
    {
        cout << "Unknow type!" << endl;
    }
}

// int main(void)
// {
//     Base *pT1 = new Child1();
//     Base *pT2 = new Child2();
//     Process(pT1);
//     Process(pT2);

//     printf("OK/n");
//     return 0;
// }

typedef void *(*CreateFuntion)(void);

class ClassFactory
{
public:
    static void *GetClassByName(std::string name)
    {
        std::map<std::string, CreateFuntion>::const_iterator find;
        find = m_clsMap.find(name);
        if (find == m_clsMap.end())
        {
            return NULL;
        }
        else
        {
            return find->second();
        }
    }
    static void RegistClass(std::string name, CreateFuntion method)
    {
        m_clsMap.insert(std::make_pair(name, method));
    }

private:
    static std::map<std::string, CreateFuntion> m_clsMap;
};

std::map<std::string, CreateFuntion> ClassFactory::m_clsMap;

class RegistyClass
{
public:
    RegistyClass(std::string name, CreateFuntion method)
    {

        ClassFactory::RegistClass(name, method);
    }
};

template <class T, const char name[]>
class Register
{
public:
    Register()
    {

        const RegistyClass tmp = rc;
    }

    static void *CreateInstance()
    {

        return new T;
    }

public:
    static const RegistyClass rc;
};

template <class T, const char name[]>
const RegistyClass Register<T, name>::rc(name, Register<T, name>::CreateInstance);

#define DEFINE_CLASS(class_name)    \
    char NameArray[] = #class_name; \
    class class_name : public Register<class_name, NameArray>

#define DEFINE_CLASS_EX(class_name, father_class) \
    char NameArray[] = #class_name;               \
    class class_name : public Register<class_name, NameArray>, public father_class

DEFINE_CLASS(CG){
    public :
        void Display(){
            printf("I am Here\n");
}
}
;

int main(int tt)
{

    CG *tmp = (CG *)ClassFactory::GetClassByName("CG");

    tmp->Display();

    return 0;
}