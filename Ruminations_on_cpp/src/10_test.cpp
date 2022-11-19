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
    friend Picture frame(const Picture &);
    friend Picture operator&(const Picture &, const Picture &);
    friend Picture operator|(const Picture &, const Picture &);
    friend class StringPic;
    friend class FramePic;
    friend class VCatPic;
    friend class HCatPic;
    friend Picture reframe(const Picture &, char, char, char);

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
    Picture(PNode *);
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
    friend Picture reframe(const Picture &, char, char, char);

public:
    PNode() : use(1) {}
    virtual ~PNode() {}
    virtual int height() const = 0;
    virtual int width() const = 0;
    virtual void display(ostream &, int, int) const = 0;
    virtual Picture reframe(char, char, char) = 0;

protected:
    int use;
};
Picture reframe(const Picture &org, char a, char b, char c)
{
    return org.p->reframe(a, b, c);
}
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
    }
    Picture reframe(char a, char b, char c)
    {
        use++;
        return this;
    }

    char **data;
    int size;
};
class FramePic : public PNode
{
    friend Picture frame(const Picture &pic);
    FramePic(const Picture &pic, char c = '+', char t = '-', char s = '|') : p(pic), ccorner(c), ctop(t), cside(s) {}
    int height() const
    {
        return p.height() + 2;
    };
    int width() const
    {
        return p.width() + 2;
    };
    void display(ostream &o, int row, int width) const
    {

        if (row >= 0 && row < height())
        {
            if (row == 0 || row == height() - 1)
            {
                o << ccorner;
                int i = p.width();
                while (--i >= 0)
                {
                    o << ctop;
                }
                o << ccorner;
            }
            else
            {
                o << cside;
                p.display(o, row - 1, p.width());
                o << cside;
            }
            pad(o, this->width(), width);
        }
        else
        {
            pad(o, 0, width);
        }
    }
    Picture reframe(char a, char b, char c)
    {
        return new FramePic(::reframe(p, a, b, c), a, b, c);
    }
    Picture p;
    char ccorner;
    char ctop;
    char cside;
};

class VCatPic : public PNode
{
    friend Picture operator|(const Picture &, const Picture &);
    Picture p_top;
    Picture p_bottom;
    int height() const
    {
        return p_top.height() + p_bottom.height();
    };
    int width() const
    {
        return max(p_top.width(), p_bottom.width());
    };
    void display(ostream &o, int row, int width) const
    {
        if (row >= 0 && row < p_top.height())
        {
            p_top.display(o, row, width);
        }
        else if (row < this->height())
        {
            p_bottom.display(o, row - p_top.height(), width);
        }
        else
        {
            pad(o, 0, width);
        }
    }
    VCatPic(const Picture &a, const Picture &b) : p_top(a), p_bottom(b) {}
    Picture reframe(char a, char b, char c)
    {
        return new VCatPic(::reframe(p_top, a, b, c), ::reframe(p_bottom, a, b, c));
    }
};
class HCatPic : public PNode
{
    friend Picture operator&(const Picture &, const Picture &);
    Picture p_left;
    Picture p_right;
    int height() const
    {
        return max(p_left.height(), p_right.height());
    };
    int width() const
    {
        return p_left.width() + p_right.width();
    };
    void display(ostream &o, int row, int width) const
    {
        if (row >= 0 && row < this->height())
        {
            p_left.display(o, row, p_left.width());
            p_right.display(o, row, p_right.width());
            pad(o, this->width(), width);
        }
        else
        {
            pad(o, 0, width);
        }
    }
    HCatPic(const Picture &a, const Picture &b) : p_left(a), p_right(b) {}
    Picture reframe(char a, char b, char c)
    {
        return new HCatPic(::reframe(p_left, a, b, c), ::reframe(p_right, a, b, c));
    }
};

Picture frame(const Picture &pic)
{
    return new FramePic(pic);
}
Picture operator&(const Picture &a, const Picture &b)
{
    return new HCatPic(a, b);
}
Picture operator|(const Picture &a, const Picture &b)
{
    return new VCatPic(a, b);
}

char *init[] = {"Paris", "in the", "Spring"};
int main()
{
    Picture p(init, 3);
    cout << p << endl;

    Picture q = frame(p);
    cout << q << endl;

    Picture r = p | q;
    cout << r << endl;

    Picture s = q & r;
    cout << s << endl
         << frame(s) << endl;

    Picture wzq = reframe(frame(s), '*', '*', '*');
    cout << wzq << endl;
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

Picture::Picture(PNode *a) : p(a) {}