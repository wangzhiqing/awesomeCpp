#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
#include <map>
using namespace std;

class User
{
public:
    User(string s) : name(s) {}
    string get_name()
    {
        return name;
    }

private:
    string name;
};

class Website
{
public:
    virtual void use(User u) = 0;
};

class WebsiteIns : public Website
{
public:
    WebsiteIns(string s) : name(s) {}
    virtual void use(User u)
    {
        cout << u.get_name() << "使用" << name << "网站" << endl;
    }

private:
    string name;
};

class WebFactory
{
public:
    std::shared_ptr<WebsiteIns> get_web(string key)
    {
        if (webFac.find(key) == webFac.end())
        {
            webFac.insert(std::make_pair(key, std::make_shared<WebsiteIns>(key)));
        }
        return webFac[key];
    }
    int get_web_count()
    {
        return webFac.size();
    }

private:
    map<string, std::shared_ptr<WebsiteIns>> webFac;
};

int main()
{
    WebFactory A;
    User u1("xiaowang");
    User u2("xiaoli");
    std::shared_ptr<WebsiteIns> web_a = A.get_web("直播");
    std::shared_ptr<WebsiteIns> web_b = A.get_web("录播");
    std::shared_ptr<WebsiteIns> web_c = A.get_web("录播");

    web_a->use(u1);
    web_b->use(u2);
    web_c->use(u1);

    cout << "网站总数：" << A.get_web_count() << endl;
}
