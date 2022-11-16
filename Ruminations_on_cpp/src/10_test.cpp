#include <iostream>
#include <string>
#include <string.h>
using namespace std;

static void pad(ostream &o, int x, int y)
{
    for (int i = x; i < y; ++i)
    {
        o << " ";
    }
}
class PNode;
class Picture
{
    friend ostream &operator<<(ostream &o, const Picture &p);

public:
    Picture();
    Picture(const Picture &);
    Picture &operator=(const Picture &);
    Picture(const char *const *, int);
    ~Picture();

private:
    PNode *p;
    int height() const;
    int width() const;
    void display(ostream &, int, int) const;
};

ostream &operator<<(ostream &o, const Picture &pic)
{
    int ht = pic.height();
    for (int i = 0; i < ht; ++i)
    {
        pic.display(o, i, pic.width());
        o << endl;
    }
    return o;
}

class PNode
{
    friend class Picture;

public:
    PNode() : use(1) {}
    virtual ~PNode() {}
    virtual int height() const = 0;
    virtual int width() const = 0;
    virtual void display(ostream &, int, int) const = 0;

private:
    int use;
};
class StringPic : public PNode
{
    friend class Picture;
    StringPic(const char *const *a, int b) : data(new char *[b]), size(b)
    {
        for (int i = 0; i < b; ++i)
        {
            data[i] = new char[strlen(a[i])];
            strcpy(data[i], a[i]);
        }
    }
    ~StringPic()
    {
        for (int i = 0; i < size; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    };
    int height() const
    {
        return size;
    };
    int width() const
    {
        int n = 0;
        for (int i = 0; i < size; ++i)
        {
            n = max(n, static_cast<int>(strlen(data[i])));
        }
        return n;
    };
    void display(ostream &o, int row, int width) const
    {
        int start = 0;
        if (row >= 0 && row < height())
        {
            o << data[row];
            start = strlen(data[row]);
        }
        pad(o, start, width);
    };
    char **data;
    int size;
};
class FramePic : public PNode
{
};
class VCatPic : public PNode
{
};
class HCatPic : public PNode
{
};

// Picture frame(const Picture &p)
// {
//     Picture res;
//     res.init(p.height + 2, p.width + 2);
//     res.position(0, 0) = '+';
//     res.position(0, p.width + 1) = '+';
//     res.position(p.height + 1, p.width + 1) = '+';
//     res.position(p.height + 1, 0) = '+';
//     for (int i = 1; i < p.width + 1; ++i)
//     {
//         res.position(0, i) = '-';
//         res.position(p.height + 1, i) = '-';
//     }
//     for (int i = 1; i < p.height + 1; ++i)
//     {
//         res.position(i, 0) = '|';
//         res.position(i, p.width + 1) = '|';
//     }
//     res.copyblock(1, 1, p);
//     return res;
// }

// Picture operator&(const Picture &p_left, const Picture &p_right)
// {
//     Picture res;
//     res.init(max(p_left.height, p_right.height), p_left.width + p_right.width);
//     res.clear(p_left.height, 0, res.height, p_left.width);
//     res.clear(p_right.height, p_left.width, res.height, res.width);

//     res.copyblock(0, 0, p_left);
//     res.copyblock(0, p_left.width, p_right);
//     return res;
// }
// Picture operator|(const Picture &p_top, const Picture &p_bottom)
// {
//     Picture res;
//     res.init(max(p_top.width, p_bottom.width), p_top.height + p_bottom.height);
//     res.clear(0, p_top.width, p_top.height, res.width);
//     res.clear(p_top.height, p_bottom.width, res.height, res.width);

//     res.copyblock(0, 0, p_top);
//     res.copyblock(p_top.height, 0, p_bottom);
//     return res;
// }

char *init[] = {"Paris", "in the", "Spring"};
int main()
{
    Picture p(init, 3);
    cout << p << endl;

    // Picture q = frame(p);
    // cout << q << endl;

    // Picture r = p | q;
    // cout << r << endl;

    // Picture s = q & r;
    // cout << s << endl
    //      << frame(s) << endl;
}

Picture::Picture() : p(0) {}
Picture::Picture(const char *const *a, int k) : p(new StringPic(a, k)) {}

Picture::Picture(const Picture &org) : p(org.p)
{
    org.p->use++;
}
Picture &Picture::operator=(const Picture &org)
{
    org.p->use++;
    if (--p->use == 0)
    {
        delete p;
    }
    p = org.p;
    return *this;
}

Picture::~Picture()
{
    if (--p->use == 0)
    {
        delete p;
    }
}

int Picture::height() const
{
    return p->height();
};
int Picture::width() const
{
    return p->width();
};
void Picture::display(ostream &o, int x, int y) const
{
    p->display(o, x, y);
};