#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
using namespace std;

class PhoneSoft
{
public:
    virtual void run() = 0;
};

class GameSoft : public PhoneSoft
{
public:
    virtual void run()
    {
        cout << "运行游戏" << endl;
    }
};

class CameraSoft : public PhoneSoft
{
public:
    virtual void run()
    {
        cout << "运行相机" << endl;
    }
};

class PhoneBrand
{
public:
    std::shared_ptr<PhoneSoft> soft;
    void set_phone_soft(std::shared_ptr<PhoneSoft> s)
    {
        soft = s;
    }
    virtual void run() = 0;
};

class XiaoMi : public PhoneBrand
{
public:
    virtual void run()
    {
        cout << "在小米手机:" << endl;
        soft->run();
    }
};

class Huawei : public PhoneBrand
{
public:
    virtual void run()
    {
        cout << "在华为手机:" << endl;
        soft->run();
    }
};

int main()
{
    std::shared_ptr<PhoneBrand> p = std::make_shared<XiaoMi>();
    p->set_phone_soft(std::make_shared<CameraSoft>());
    p->run();
    p->set_phone_soft(std::make_shared<GameSoft>());
    p->run();

    p = std::make_shared<Huawei>();
    p->set_phone_soft(std::make_shared<CameraSoft>());
    p->run();
}