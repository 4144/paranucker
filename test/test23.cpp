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
    Data1 *dataptr;

    void func1(Data1 *const ptr1)
    {
        dataptr = ptr1;
        if (dataptr)
        {
            ptr1->ftest1();
        }
    }

    void func2(Data1 *const ptr1)
    {
        dataptr = ptr1;
        if (ptr1)
        {
            ptr1->ftest1();
        }
    }

    void func3(Data1 *const ptr1)
    {
        dataptr = ptr1;
        if (!dataptr)
        {
            ptr1->ftest1();
        }
    }

    void func4(Data1 *const ptr1)
    {
        dataptr = ptr1;
        if (!dataptr && ptr1)
        {
            ptr1->ftest1();
        }
    }

    void func5(Data1 *const ptr1)
    {
        dataptr = ptr1;
        if (!dataptr || !ptr1)
        {
            ptr1->ftest1();
        }
    }
};
