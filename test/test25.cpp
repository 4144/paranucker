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
    int test1(Data1 *const ptr1) __attribute__((nonnull (2)))
    {
        if (ptr1)
            return 1;
        else
            return 0;
    }

    void func1(Data1 *const ptr1)
    {
        test1(nullptr);
    }

    void func2(Data1 *const ptr1)
    {
        test1(ptr1);
    }
};
