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

typedef void *(*PTRCreateObject)(void);

// 工厂类的定义
class ClassFactory
{
private:
    std::map<std::string, PTRCreateObject> m_classMap;
    ClassFactory(){}; // 构造函数私有化

public:
    void *getClassByName(std::string className);
    void registClass(std::string name, PTRCreateObject method);
    static ClassFactory &getInstance();
};

// 工厂类的实现
//@brief:获取工厂类的单个实例对象
ClassFactory &ClassFactory::getInstance()
{
    static ClassFactory sLo_factory;
    return sLo_factory;
}

//@brief:通过类名称字符串获取类的实例
void *ClassFactory::getClassByName(std::string className)
{
    auto iter = m_classMap.find(className);
    if (iter == m_classMap.end())
        return NULL;
    else
        return iter->second();
}

//@brief:将给定的类名称字符串和对应的创建类对象的函数保存到map中
void ClassFactory::registClass(std::string name, PTRCreateObject method)
{
    m_classMap.insert(make_pair(name, method));
}

// 注册动作类
class RegisterAction
{
public:
    RegisterAction(std::string className, PTRCreateObject ptrCreateFn)
    {
        ClassFactory::getInstance().registClass(className, ptrCreateFn);
    }
};

#define REGISTER(className)                      \
    className *objectCreator##className()        \
    {                                            \
        return new className;                    \
    }                                            \
    RegisterAction g_creatorRegister##className( \
        #className, (PTRCreateObject)objectCreator##className)

// test class A
class TestClassA
{
public:
    virtual void m_print()
    {
        cout << "hello TestClassA" << endl;
    };
};

REGISTER(TestClassA);

// test class B
class TestClassB : public TestClassA
{
public:
    void m_print()
    {
        cout << "hello TestClassB" << endl;
    };
};

REGISTER(TestClassB);

int main(int tt)
{

    TestClassA *ptrObj = (TestClassA *)ClassFactory::getInstance().getClassByName("TestClassB");
    ptrObj->m_print();

    return 0;
}