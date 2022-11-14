#include <iostream>
#include <string>
using namespace std;

class Expr_node;
class Expr
{
    friend ostream &operator<<(ostream &, const Expr &);
    Expr_node *p;

public:
    Expr(int n);
    Expr(string op, Expr t);
    Expr(string op, Expr left, Expr right);
    Expr(string op, Expr left, Expr mid, Expr right);
    ~Expr();
    Expr(const Expr &t);
    Expr &operator=(const Expr &rhs);
    int get_result();
};

class Expr_node
{
    friend ostream &operator<<(ostream &, const Expr_node &);
    friend class Expr;
    int use;

public:
    Expr_node() : use(1) {}
    virtual void print(ostream &) const = 0;
    virtual ~Expr_node() {}
    virtual int get_result() = 0;
};
ostream &operator<<(ostream &o, const Expr_node &e)
{
    e.print(o);
    return o;
}

class Int_node : public Expr_node
{
    friend class Expr;
    int n;
    Int_node(int k) : n(k) {}
    void print(ostream &o) const
    {
        o << n;
    }
    int get_result()
    {
        return n;
    }
};

class Unary_node : public Expr_node
{
    friend class Expr;
    string op;
    Expr opnd;
    Unary_node(const string a, Expr b) : op(a), opnd(b) {}
    void print(ostream &o) const
    {
        o << "(" << op << opnd << ")";
    }
    int get_result()
    {
        if (op[0] == '-')
        {
            return -1 * opnd.get_result();
        }
        return opnd.get_result();
    }
};
class Binary_node : public Expr_node
{
    friend class Expr;
    string op;
    Expr left;
    Expr right;
    Binary_node(const string a, Expr b,
                Expr c) : op(a), left(b), right(c) {}
    void print(ostream &o) const
    {
        o << "(" << left << op << right << ")";
    }
    int get_result()
    {
        int res = 0;
        switch (op[0])
        {
        case '+':
            res = left.get_result() + right.get_result();
            break;
        case '-':
            res = left.get_result() - right.get_result();
            break;
        case '*':
            res = left.get_result() * right.get_result();
            break;
        case '/':
            res = left.get_result() / right.get_result();
            break;
        default:
            break;
        }
        return res;
    }
};
class Ternary_node : public Expr_node
{
    friend class Expr;
    string op;
    Expr left;
    Expr mid;
    Expr right;
    Ternary_node(const string a, Expr b,
                 Expr c, Expr d) : op(a), left(b), mid(c), right(d) {}
    void print(ostream &o) const
    {
        o << "(" << left << "?" << mid << ":" << right << ")";
    }
    int get_result()
    {
        if (left.get_result() == 0)
        {
            return mid.get_result();
        }
        else
        {
            return right.get_result();
        }
    }
};

Expr::Expr(int n) : p(new Int_node(n)) {}
Expr::Expr(string op, Expr t) : p(new Unary_node(op, t)) {}
Expr::Expr(string op, Expr left, Expr right) : p(new Binary_node(op, left, right)) {}
Expr::Expr(string op, Expr left, Expr mid, Expr right) : p(new Ternary_node(op, left, mid, right)) {}
Expr::~Expr()
{
    if (--p->use == 0)
        delete p;
}
Expr::Expr(const Expr &t)
{
    p = t.p;
    p->use++;
}

Expr &Expr::operator=(const Expr &rhs)
{
    rhs.p->use++;
    if (--p->use == 0)
    {
        delete p;
    }
    p = rhs.p;
    return *this;
}
int Expr::get_result()
{
    return p->get_result();
}
ostream &operator<<(ostream &o, const Expr &t)
{
    t.p->print(o);
    return o;
}

int main()
{
    Expr t = Expr("*",
                  Expr("-", 5),
                  Expr("+", 3, 4));
    cout << t << "=" << t.get_result() << endl;
    ;
    t = Expr("*", t, t);
    cout << t << "=" << t.get_result() << endl;
}
