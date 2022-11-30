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
    virtual std::shared_ptr<Operation> createOp() = 0;
};

class AddFactory : public OpFactory
{
public:
    std::shared_ptr<Operation> createOp()
    {
        return std::make_shared<OpAdd>();
    }
};

class SubFactory : public OpFactory
{
public:
    std::shared_ptr<Operation> createOp()
    {
        return std::make_shared<OpSub>();
    }
};

class MulFactory : public OpFactory
{
public:
    std::shared_ptr<Operation> createOp()
    {
        return std::make_shared<OpMul>();
    }
};

class DivFactory : public OpFactory
{
public:
    std::shared_ptr<Operation> createOp()
    {
        return std::make_shared<OpDiv>();
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

    std::shared_ptr<OpFactory> factory;

    switch (op)
    {
    case '+':
        factory = std::shared_ptr<AddFactory>(new AddFactory());
        break;
    case '-':
        factory = std::make_shared<SubFactory>();
        break;
    case '*':
        factory = std::make_shared<MulFactory>();
        break;
    case '/':
        factory = std::make_shared<DivFactory>();
        break;
    }
    std::shared_ptr<Operation> operation = factory->createOp();
    operation->set_num1(num1);
    operation->set_num2(num2);
    cout << operation->get_result() << endl;
    cout << "Ptr use count:" << operation.use_count() << endl;
}