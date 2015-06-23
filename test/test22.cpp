#include <vector>

struct Data1
{
    int val;

    int ftest()
    {
        return 1;
    }
};

int k;

class Object1
{
    int func1(Data1 *const ptr1)
    {
        std::vector<Data1*> vec1;
        vec1.push_back(ptr1);
    }

    int func2(Data1 *const ptr1)
    {
        Data1* ptr2 = ptr1 + 1;
    }

    int func3(Data1 *ptr1)
    {
        Data1** ptr2 = &ptr1;
        (*ptr2)->val = 10;
    }

    void func4(Data1 *const ptr1)
    {
        if (ptr1->ftest() == 100)
        {
            return;
        }
    }
};
