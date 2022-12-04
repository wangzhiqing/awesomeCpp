#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Stock
{
public:
    void sell()
    {
        cout << "卖股票" << endl;
    }
    void buy()
    {
        cout << "买股票" << endl;
    }
};

class NationalDebt
{
public:
    void sell()
    {
        cout << "卖国债" << endl;
    }
    void buy()
    {
        cout << "买国债" << endl;
    }
};

class House
{
public:
    void sell()
    {
        cout << "卖房" << endl;
    }
    void buy()
    {
        cout << "买房" << endl;
    }
};

class Fund
{
public:
    Fund()
    {
        stockPtr = std::make_shared<Stock>();
        nationalDebtPtr = std::make_shared<NationalDebt>();
        housePtr = std::make_shared<House>();
    }
    void buy_fund()
    {
        stockPtr->buy();
        nationalDebtPtr->buy();
        housePtr->buy();
    }
    void sell_fund()
    {
        stockPtr->sell();
        nationalDebtPtr->sell();
        housePtr->sell();
    }

private:
    std::shared_ptr<Stock> stockPtr;
    std::shared_ptr<NationalDebt> nationalDebtPtr;
    std::shared_ptr<House> housePtr;
};
int main()
{
    std::shared_ptr<Fund> jj(new Fund());
    jj->buy_fund();
    jj->sell_fund();
}