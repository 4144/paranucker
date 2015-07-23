#include <string>
#include <vector>

struct Data1;

typedef void (*FuncPtr1) (void);
typedef void (*FuncPtr2) (Data1 *ptr);
typedef void (Data1::*FuncPtr3) (Data1 *ptr);
typedef void (&FuncPtr4)(const void *const);

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

    void ftest3(Data1 *ptr0)
    {
    }
};

int k;

class Object1
{
    Data1 *dataptr;

    Object1(Data1 *ptr1) :
        dataptr(ptr1)
    {
        if (dataptr)
        {
            ptr1->ftest1();
        }
        dataptr->ftest1();
    }

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

    void func6(FuncPtr1 ptr1)
    {
        ptr1();
    }

    void func7(Data1 *ptr1)
    {
        FuncPtr2 fptr2;
        fptr2(ptr1);
    }

    void func8(Data1 *ptr1)
    {
        FuncPtr3 fptr2 = &Data1::ftest3;
        (ptr1->*fptr2)(ptr1);
    }

    void func9(FuncPtr4 ptr1, Data1 *const ptr2)
    {
        ptr1(ptr2);
    }

    void func10(Data1 *ptr1, Data1 *ptr2)
    {
        FuncPtr3 fptr2 = &Data1::ftest3;
        (ptr1->*fptr2)(ptr2);
    }
};
