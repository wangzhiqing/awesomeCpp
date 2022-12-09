#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
using namespace std;

std::mutex mtx;

class Singleton
{
public:
    static Singleton *get_instance()
    {
        if (cur == nullptr)
        {
            std::lock_guard<std::mutex> lck(mtx);
            if (cur == nullptr)
            {
                cur = new Singleton();
                return cur;
            }
        }

        return cur;
    }
    void show()
    {
        cout << "成功" << endl;
    }

private:
    Singleton(){};
    static Singleton *cur;
};
Singleton *Singleton::cur = nullptr;
int main()
{
    Singleton *s1 = Singleton::get_instance();
    Singleton *s2 = Singleton::get_instance();
    if (s1 == s2)
    {
        cout << "一样" << endl;
    }
    s1->show();
}