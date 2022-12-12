#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
using namespace std;

template <class T>
class Iterator
{
public:
    virtual T *first() = 0;
    virtual T *next() = 0;
    virtual bool is_done() = 0;
    virtual T *cur() = 0;
};

template <class T>
class Aggregate
{
public:
    virtual Iterator<T> *create_iter() = 0;
};

template <class T>
class ConcreteAggregate;

template <class T>
class ConcreteIterator : public Iterator<T>
{
private:
    std::shared_ptr<ConcreteAggregate<T>> ca;
    int cur_index = 0;

public:
    ConcreteIterator(std::shared_ptr<ConcreteAggregate<T>> v) : ca(v) {}
    T *first()
    {
        return (*ca)[0];
    }
    T *next()
    {
        cur_index++;
        if (cur_index < ca->get_count())
        {
            return (*ca)[cur_index];
        }
        else
        {
            return nullptr;
        }
    }
    bool is_done()
    {
        return cur_index == ca->get_count();
    }
    T *cur()
    {
        return (*ca)[cur_index];
    }
};

template <class T>
class ConcreteAggregate : public Aggregate<T>
{
public:
    ConcreteAggregate() {}
    Iterator<T> *create_iter()
    {
        return new ConcreteIterator<T>(std::make_shared<ConcreteAggregate<T>>(*this));
    }
    int get_count()
    {
        return items.size();
    }
    T *operator[](int index)
    {
        return items[index];
    }
    void insert(T *obj)
    {
        return items.push_back(obj);
    }

private:
    vector<T *> items;
};

int main()
{
    std::shared_ptr<ConcreteAggregate<float>> a = std::make_shared<ConcreteAggregate<float>>();
    float b_1 = 100;
    float b_2 = 200;
    float b_3 = 300;
    a->insert(&b_1);
    a->insert(&b_2);
    a->insert(&b_3);

    Iterator<float> *iter = a->create_iter();
    float *cur = iter->first();
    while (!iter->is_done())
    {
        cout << *iter->cur() << endl;
        iter->next();
    }
}