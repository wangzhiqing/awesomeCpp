#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Picture
{
public:
    friend ostream &operator<<(ostream &o, const Picture &p);
    friend Picture frame(const Picture &);
    friend Picture operator&(const Picture &, const Picture &);
    friend Picture operator|(const Picture &, const Picture &);

    Picture();
    Picture(const Picture &);
    Picture &operator=(const Picture &);
    Picture(const char *const *, int);
    ~Picture();

private:
    char *data;
    int height, width;
    char &position(int row, int col)
    {
        return data[row * width + col];
    }
    char position(int row, int col) const
    {
        return data[row * width + col];
    }
    void init(int h, int w)
    {
        height = h;
        width = w;
        data = new char[height * width];
    }
    void copyblock(int row, int col, const Picture &p)
    {
        for (int i = 0; i < p.height; ++i)
        {
            for (int j = 0; j < p.width; ++j)
            {
                position(i + row, j + col) = p.position(i, j); //注意第一个position越界
            }
        }
    }
    void clear(int top, int left, int bottom, int right)
    {
        for (int i = top; i < bottom; ++i)
        {
            for (int j = left; j < right; ++j)
            {
                position(i, j) = ' ';
            }
        }
    }
};

ostream &operator<<(ostream &o, const Picture &p)
{
    for (int i = 0; i < p.height; ++i)
    {
        for (int j = 0; j < p.width; ++j)
        {
            o << p.position(i, j);
        }
        o << endl;
    }
    return o;
}

Picture frame(const Picture &p)
{
    Picture res;
    res.init(p.height + 2, p.width + 2);
    res.position(0, 0) = '+';
    res.position(0, p.width + 1) = '+';
    res.position(p.height + 1, p.width + 1) = '+';
    res.position(p.height + 1, 0) = '+';
    for (int i = 1; i < p.width + 1; ++i)
    {
        res.position(0, i) = '-';
        res.position(p.height + 1, i) = '-';
    }
    for (int i = 1; i < p.height + 1; ++i)
    {
        res.position(i, 0) = '|';
        res.position(i, p.width + 1) = '|';
    }
    res.copyblock(1, 1, p);
    return res;
}

Picture operator&(const Picture &p_left, const Picture &p_right)
{
    Picture res;
    res.init(max(p_left.height, p_right.height), p_left.width + p_right.width);
    res.clear(p_left.height, 0, res.height, p_left.width);
    res.clear(p_right.height, p_left.width, res.height, res.width);

    res.copyblock(0, 0, p_left);
    res.copyblock(0, p_left.width, p_right);
    return res;
}
Picture operator|(const Picture &p_top, const Picture &p_bottom)
{
    Picture res;
    res.init(max(p_top.width, p_bottom.width), p_top.height + p_bottom.height);
    res.clear(0, p_top.width, p_top.height, res.width);
    res.clear(p_top.height, p_bottom.width, res.height, res.width);

    res.copyblock(0, 0, p_top);
    res.copyblock(p_top.height, 0, p_bottom);
    return res;
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
}

Picture::Picture() : data(0), height(0), width(0) {}
Picture::Picture(const char *const *a, int k)
{
    int w = 0;
    for (int i = 0; i < k; ++i)
    {
        w = max(w, static_cast<int>(strlen(a[i])));
    }
    init(k, w);
    for (int i = 0; i < k; ++i)
    {
        int j = 0;
        const char *src = a[i];
        for (; j < strlen(src); ++j)
        {
            position(i, j) = src[j];
        }
        for (; j < width; ++j)
        {
            position(i, j) = ' ';
        }
    }
}

Picture::Picture(const Picture &p) : height(p.height), width(p.width),
                                     data(new char[p.height * p.width])
{
    copyblock(0, 0, p);
}
Picture &Picture::operator=(const Picture &p)
{
    if (this != &p)
    {
        delete[] data;
        init(p.height, p.width);
        copyblock(0, 0, p);
    }
    return *this;
}

Picture::~Picture()
{
    delete[] data;
}