#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class Player
{
public:
    string name;
    Player(string nameV) : name(nameV) {}
    virtual void attack() = 0;
    virtual void defend() = 0;
};

class Center : public Player
{
public:
    Center(string nameV) : Player(nameV) {}
    void attack() { cout << name << " zhongfeng attack" << endl; }
    void defend() { cout << name << " zhongfeng defend" << endl; }
};
class ForeignCenter
{
private:
    string name;

public:
    ForeignCenter(string nameV) : name(nameV) {}
    void jingong() { cout << name << " 进攻" << endl; }
    void fangshou() { cout << name << " 防守" << endl; }
};

class Translator : public Player
{
private:
    ForeignCenter *a;

public:
    Translator(string nameV) : Player(nameV)
    {
        a = new ForeignCenter(nameV);
    }
    void attack()
    {
        a->jingong();
    }
    void defend()
    {
        a->fangshou();
    }
};
int main()
{
    Player *a = new Center("xiaowang");
    a->attack();

    Player *b = new Translator("yaoming");
    b->attack();
    b->defend();
}