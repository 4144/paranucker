struct Data1;
struct Data2;

struct Data2
{
    int val;
    Data1 *ptrval;
    int arr[3];
    Data1 *getData3()
    {
        return ptrval;
    }
};

struct Data1
{
    int val;
    Data1 *ptrval;
    Data2 perm;
    int arr[3];
    virtual ~Data1();

    Data1 *getData2()
    {
        return ptrval;
    }

    virtual Data1 *getData3(int &k)
    {
        val = k;
        return ptrval;
    }
    static Data1 *getData4()
    {
        return 0;
    }
    Data2 *getData5() __attribute__((returns_nonnull))
    {
        return &perm;
    }
    virtual Data1 *getData6()
    {
        return 0;
    }
};

int k;

Data1 *gptr1;
Data1 *gptr2 __attribute__((nonnullpointer));

void paranuckerInternalTest(const char *action, const char *collection, const char *values);

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;
    Data1 *tmp3 __attribute__((nonnullpointer));

    Data1 *getData1()
    {
        return tmp2;
    }

    Data1 *getData2()
    {
        return tmp2;
    }

    Data1 *func1(Data1 *ptr1) const
    {
        return k ? tmp1 : tmp2;
    }

    Data1 *func2(Data1 *ptr1) const
    {
        return tmp1;
    }

    Data1 *func3(Data1 *ptr1) const
    {
        return &tmp1[1];
    }
};
