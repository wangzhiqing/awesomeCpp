#include <iostream>
#include <memory>
using namespace std;

class Cash
{
public:
    virtual double getCash(double money) = 0;
};

class NormalCash : public Cash
{
public:
    double getCash(double money)
    {
        return money;
    }
};

class RebateCash : public Cash
{
public:
    RebateCash(double num) : rebate(num) {}
    double getCash(double money)
    {
        return rebate * money;
    }

private:
    double rebate = 1.;
};

class ReturnCash : public Cash
{
public:
    ReturnCash(double c, double r) : condition_money(c), return_money(r) {}
    double getCash(double money)
    {
        double result = money;
        if (money >= condition_money)
        {
            result = money - static_cast<int>(money / condition_money) * return_money;
        }
        return result;
    }

private:
    double condition_money, return_money;
};

class CashContext
{
private:
    std::shared_ptr<Cash> shp_cash;

public:
    CashContext(Cash *a) : shp_cash(a) {}
    CashContext(int strategy)
    {
        switch (strategy)
        {
        case 0:
            shp_cash = std::make_shared<NormalCash>();
            break;
        case 1:
            shp_cash = std::make_shared<RebateCash>(0.8);
            break;
        case 2:
            shp_cash = std::shared_ptr<Cash>(new ReturnCash(300, 100));
            break;
        }
    }
    double getCash(double money)
    {
        shp_cash->getCash(money);
    }
};
int main()
{
    double num;
    int strategy;
    cout << "Input money:" << endl;
    cin >> num;
    cout << "Input strategy:" << endl;
    cin >> strategy;

    std::shared_ptr<CashContext> shp_cc(new CashContext(strategy));
    cout << shp_cc->getCash(num) << endl;
    cout << "shared ptr count:" << shp_cc.use_count() << endl;
}