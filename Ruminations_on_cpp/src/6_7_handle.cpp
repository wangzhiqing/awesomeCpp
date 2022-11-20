#include <iostream>
#include <memory>

using namespace std;
class Point
{
public:
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    int xval() const
    {
        return x;
    }
    int yval() const
    {
        return y;
    }
    Point &xval(int xv)
    {
        x = xv;
        return *this;
    }
    Point &yval(int yv)
    {
        y = yv;
        return *this;
    }

private:
    int x;
    int y;
};

class UPoint
{
    friend class PHandle;
    Point p;
    int u;
    UPoint() : u(1) {}
    UPoint(int x, int y) : p(x, y), u(1) {}
    UPoint(const Point &p0) : p(p0), u(1) {}
};
class PHandle
{
public:
    PHandle() : up(new UPoint()) {}
    PHandle(const Point &p) : up(new UPoint(p)) {}
    PHandle(int x, int y) : up(new UPoint(x, y)) {}
    ~PHandle()
    {
        if (--up->u == 0)
        {
            delete up;
        }
    }
    PHandle(const PHandle &h) : up(h.up) { ++up->u; }
    PHandle &operator=(const PHandle &h)
    {
        ++h.up->u;
        if (--up->u == 0)
        {
            delete up;
        }
        up = h.up;
        return *this;
    }
    int xval() const
    {
        return up->p.xval();
    }
    int yval() const
    {
        return up->p.yval();
    }
    PHandle &xval(int x)
    {
        up->p.xval(x);
        return *this;
    }
    PHandle &yval(int x)
    {
        if (up->u != 1)
        {
            --up->u;
            up = new UPoint(up->p);
        }
        up->p.yval(x);
        return *this;
    }
    int count()
    {
        return up->u;
    }

private:
    UPoint *up;
};
class UseCount
{
public:
    UseCount() : p(new int(1)) {}
    UseCount(const UseCount &u) : p(u.p) { ++*p; }
    ~UseCount()
    {
        if (--*p == 0)
        {
            delete p;
        }
    }
    bool only()
    {
        return *p == 1;
    }
    bool reattach(const UseCount &u)
    {
        ++*u.p;
        if (--*p == 0)
        {
            delete p;
            p = u.p;
            return true;
        }
        p = u.p;
        return false;
    }

    bool makeonly()
    {
        if (*p == 1)
        {
            return false;
        }
        --*p;
        p = new int(1);
        return true;
    }
    int count()
    {
        return *p;
    }

private:
    int *p;
};
class PHandle2
{
public:
    PHandle2() : up(new Point()) {}
    PHandle2(const Point &p) : up(new Point(p)) {}
    PHandle2(int x, int y) : up(new Point(x, y)) {}
    ~PHandle2()
    {
        if (u.only())
        {
            delete up;
        }
    }
    PHandle2(const PHandle2 &h) : up(h.up), u(h.u) {}
    PHandle2 &operator=(const PHandle2 &h)
    {
        if (u.reattach(h.u))
        {
            delete up;
        }
        up = h.up;
        return *this;
    }
    int xval() const
    {
        return up->xval();
    }
    int yval() const
    {
        return up->yval();
    }
    PHandle2 &xval(int x)
    {
        up->xval(x);
        return *this;
    }
    PHandle2 &yval(int x)
    {
        if (u.makeonly())
        {
            up = new Point(*up);
        }
        up->yval(x);
        return *this;
    }
    int count()
    {
        return u.count();
    }

private:
    Point *up;
    UseCount u;
};

int main()
{
    Point a(1, 8);
    PHandle2 pa(a);
    PHandle2 pb(pa);
    cout << pa.xval() << " " << pa.yval() << " " << pa.count() << endl;
    PHandle2 tmp = pa.xval(100);
    tmp.yval(1111);
    cout << pa.xval() << " " << pa.yval() << " " << pa.count() << endl;
    pa.yval(100);
    cout << pa.xval() << " " << pa.yval() << " " << pa.count() << endl;

    cout << "use shared_Ptr:" << endl;
    Point *b = new Point(1, 9);
    shared_ptr<Point> sp_P1(new Point(1, 9));
    shared_ptr<Point> sp_P2(sp_P1);
    cout << sp_P1->xval() << " " << sp_P1->yval() << " " << sp_P1.use_count() << endl;
    sp_P1->xval(100);
    cout << sp_P1->xval() << " " << sp_P1->yval() << " " << sp_P1.use_count() << endl;
    cout << sp_P2->xval() << " " << sp_P2->yval() << " " << sp_P2.use_count() << endl;
}