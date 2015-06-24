#include <vector>

struct Data1;

struct Data1
{
    Data1()
    {
    }

    Data1(Data1 *ptr0) :
        ptrval(ptr0)
    {
    }

    int val;
    Data1 *ptrval;

    int ftest1()
    {
        return 1;
    }

    static int ftest2(Data1 *ptr0)
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
        if (ptr1->ftest1() == 100)
        {
            return;
        }
    }

    void func5(Data1 *ptr1)
    {
        Data1 data(ptr1);
    }

    void func6(Data1 *const ptr1)
    {
        if (!ptr1)
            return;
        int num = ptr1->val;
    }

    void func7(Data1 *const ptr1)
    {
        if (Data1::ftest2(ptr1) == 200)
        {
            return;
        }
    }
};
