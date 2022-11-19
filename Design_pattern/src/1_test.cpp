#include <iostream>
#include <memory>
using namespace std;

class Operation
{
public:
    int get_num1()
    {
        return num_1;
    }
    int get_num2()
    {
        return num_2;
    }
    void set_num1(int a)
    {
        num_1 = a;
    }
    void set_num2(int a)
    {
        num_2 = a;
    }
    virtual int get_result() = 0;

private:
    int num_1, num_2;
};

class OpAdd : public Operation
{
public:
    int get_result()
    {
        return get_num1() + get_num2();
    }
};

class OpSub : public Operation
{
public:
    int get_result()
    {
        return get_num1() - get_num2();
    }
};

class OpMul : public Operation
{
public:
    int get_result()
    {
        return get_num1() * get_num2();
    }
};

class OpDiv : public Operation
{
public:
    int get_result()
    {
        return get_num1() / get_num2();
    }
};

class OpFactory
{
public:
    static std::shared_ptr<Operation> createOp(char c)
    {
        switch (c)
        {
        case '+':
            return std::shared_ptr<Operation>(new OpAdd());
        case '-':
            return std::shared_ptr<Operation>(new OpSub());
        case '*':
            return std::shared_ptr<Operation>(new OpMul());
        case '/':
            return std::shared_ptr<Operation>(new OpDiv());
        }
    }
};
int main()
{
    int num1;
    int num2;
    char op;
    cout << "Input 1:" << endl;
    cin >> num1;
    cout << "Input 2:" << endl;
    cin >> num2;
    cout << "Input op:" << endl;
    cin >> op;

    std::shared_ptr<Operation> p = OpFactory::createOp(op);
    p->set_num1(num1);
    p->set_num2(num2);
    cout << p->get_result() << endl;
    cout << "Ptr use count:" << p.use_count() << endl;
}