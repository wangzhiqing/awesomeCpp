#include <iostream>
#include <memory>
#include <string>
using namespace std;

// repeat = easy-wrong, hard-fix
class TestPaper
{
public:
    void TestQuestion1()
    {
        cout << "Q1: XXX" << endl;
        cout << "Answer: " << get_answer1() << endl;
    }
    void TestQuestion2()
    {
        cout << "Q2: YYY" << endl;
        cout << "Answer: " << get_answer2() << endl;
    }
    virtual string get_answer1()
    {
        return "";
    }
    virtual string get_answer2()
    {
        return "";
    }
};

class TestPaperA : public TestPaper
{
public:
    string get_answer1()
    {
        return "a";
    }
    string get_answer2()
    {
        return "b";
    }
};

class TestPaperB : public TestPaper
{
public:
    string get_answer1()
    {
        return "b";
    }
    string get_answer2()
    {
        return "c";
    }
};

int main()
{
    TestPaper *a = new TestPaperA();
    TestPaper *b = new TestPaperB();
    a->TestQuestion1();
    a->TestQuestion2();
    b->TestQuestion1();
    b->TestQuestion2();
    delete a;
    delete b;
}