#include <iostream>
#include <memory>
#include <string>
#include <list>
using namespace std;

class RoleStateMem
{
private:
    int life;

public:
    RoleStateMem(int v) : life(v) {}
    int get_life()
    {
        return life;
    }
    void set_life(int v)
    {
        life = v;
    }
};

class GameRole
{
private:
    int life;

public:
    GameRole(int v) : life(v) {}
    int get_life()
    {
        return life;
    }
    void set_life(int v)
    {
        life = v;
    }
    std::shared_ptr<RoleStateMem> save_state()
    {
        return make_shared<RoleStateMem>(life);
    }
    void recovery_state(std::shared_ptr<RoleStateMem> mem)
    {
        life = mem->get_life();
    }
};

class RoleStateTaker
{
private:
    std::shared_ptr<RoleStateMem> mem;

public:
    void set_mem(std::shared_ptr<RoleStateMem> v)
    {
        mem = v;
    }
    std::shared_ptr<RoleStateMem> get_mem()
    {
        return mem;
    }
};

int main()
{
    GameRole *a = new GameRole(100);
    cout << "life:" << a->get_life() << endl;
    RoleStateTaker a_mem;
    a_mem.set_mem(a->save_state());

    a->set_life(20);
    cout << "fight life:" << a->get_life() << endl;

    a->recovery_state(a_mem.get_mem());
    cout << "recovery life:" << a->get_life() << endl;
}