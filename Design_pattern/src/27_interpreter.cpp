#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <mutex>
#include <vector>
#include <map>
using namespace std;

class MusicText
{
public:
    string text;
};

class Expression
{
public:
    void interpret(MusicText &m)
    {
        if (m.text.size() == 0)
        {
            return;
        }
        else
        {
            char playKey = m.text[0];
            m.text = m.text.substr(2);
            size_t index = m.text.find_first_of(" ");
            float playValue = std::stof(m.text.substr(0, index));
            m.text = m.text.substr(index + 1);
            excute(playKey, playValue);
        }
    }
    virtual void excute(char key, float value) = 0;
};

class Note : public Expression
{
public:
    virtual void excute(char key, float value)
    {
        string note = "";
        switch (key)
        {
        case 'C':
            note = "1";
            break;
        case 'D':
            note = "2";
            break;
        case 'E':
            note = "3";
            break;
        case 'F':
            note = "4";
            break;
        case 'G':
            note = "5";
            break;
        case 'A':
            note = "6";
            break;
        case 'B':
            note = "7";
            break;
        }
        cout << " " << note << " " << endl;
    }
};

class Scale : public Expression
{
public:
    virtual void excute(char key, float value)
    {
        string scale = "";
        switch (static_cast<int>(value))
        {
        case 1:
            scale = "低音";
            break;
        case 2:
            scale = "中音";
            break;
        case 3:
            scale = "高音";
            break;
        }
        cout << " " << scale << " " << endl;
    }
};

int main()
{
    MusicText mt;
    mt.text = "O 2 E 0.5 G 0.5 A 3 E 0.5 G 0.5 O 3 C 1 O 2 A 0.5 ";
    std::shared_ptr<Expression> exp;
    while (mt.text.size() > 0)
    {
        char c = mt.text[0];
        switch (c)
        {
        case 'O':
            exp = std::make_shared<Scale>();
            break;
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'A':
        case 'B':
        case 'P':
            exp = std::make_shared<Note>();
            break;
        }
        exp->interpret(mt);
    }
}
