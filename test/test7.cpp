#include <string>

struct Struct1
{
    Struct1() :
        str(),
        num(0)
    {
    }

    std::string str;
    int num;
};

class Object1
{
    int k;
    void func1()
    {
    }

    void func2(int *aptr)
    {
        *aptr = 0;
    }

    void func3(int *aptr)
    {
        if (aptr)
            *aptr = 0;
    }

    void func4(int *aptr)
    {
        k = 3;
    }

    void func5(Struct1 *sptr)
    {
        sptr->num = 0;
    }

    void func6(Struct1 *sptr)
    {
        if (!sptr)
            return;
        sptr->num = 0;
    }
};
