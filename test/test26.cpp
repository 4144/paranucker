#include <string>
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
    int arr[3];
    std::string str1;

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
    void func1(Data1 *const ptr1)
    {
        if (ptr1)
        {
            if (ptr1 && k == 1)
                return;
        }
    }
};
