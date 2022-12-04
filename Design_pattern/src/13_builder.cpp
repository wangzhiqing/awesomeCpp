#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Pen
{
public:
    string color = "红色";
};

class PersonBuilder
{
public:
    PersonBuilder(Pen a) : pen(a) {}
    virtual void build_arm() = 0;
    virtual void build_head() = 0;
    virtual void build_body() = 0;
    virtual void build_leg() = 0;
    virtual ~PersonBuilder(){};

protected:
    Pen pen;
};

class ThinPersonBuilder : public PersonBuilder
{
public:
    ThinPersonBuilder(Pen a) : PersonBuilder(a) {}
    void build_arm() override
    {
        cout << pen.color << " 胳膊" << endl;
    }
    void build_head() override
    {
        cout << pen.color << " 头" << endl;
    }
    void build_body() override
    {
        cout << pen.color << " 身体" << endl;
    }
    void build_leg() override
    {
        cout << pen.color << " 腿" << endl;
    }
    virtual ~ThinPersonBuilder() {}
};

class PersonDirector
{
public:
    PersonDirector(std::shared_ptr<PersonBuilder> a) : person_builder_ptr(a) {}
    void createPerson()
    {
        person_builder_ptr->build_head();
        person_builder_ptr->build_body();
        person_builder_ptr->build_arm();
        person_builder_ptr->build_leg();
    }

private:
    std::shared_ptr<PersonBuilder> person_builder_ptr;
};
int main()
{
    Pen p;
    p.color = "黄色";
    std::shared_ptr<PersonBuilder> person_a(new ThinPersonBuilder(p));
    std::shared_ptr<PersonDirector> person_direc(new PersonDirector(person_a));
    person_direc->createPerson();
    cout << "shared ptr:" << person_a.use_count() << endl;
}