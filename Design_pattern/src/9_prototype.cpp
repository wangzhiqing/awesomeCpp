#include <iostream>
#include <memory>
#include <string>
using namespace std;

class School
{
public:
    void setSchool(string schoolS)
    {
        school = schoolS;
    }
    string getSchool()
    {
        return school;
    }

private:
    string school;
};
class Resume
{
public:
    Resume(string nameS) : name(nameS) { school = std::make_shared<School>(); }
    void setPersonInfo(string sexS, string ageS)
    {
        sex = sexS;
        age = ageS;
    }
    void setWorkExp(string timeAreaS, string companyS)
    {
        timeArea = timeAreaS;
        company = companyS;
    }
    void setSchool(string schoolS)
    {
        school->setSchool(schoolS);
    }
    void display()
    {
        cout << name << " " << sex << " " << age << endl;
        cout << "工作经历: " << timeArea << " " << company << endl;
        cout << "学习经历: " << school->getSchool() << endl;
    }

private:
    string name, sex, age, timeArea, company;
    std::shared_ptr<School> school; //浅拷贝
    // 深拷贝
    // School school
};

int main()
{
    Resume a("xiaowang");
    a.setPersonInfo("man", "18");
    a.setWorkExp("1990-2000", "baidu");
    a.setSchool("zju");

    a.display();
    Resume b = a;
    b.setSchool("zju2");
    a.display();
    b.display();
}