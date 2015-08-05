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

    void func1(Data1 *ptr1) const
    {
        tmp1->val = 100;
    }

    void func2(Data1 *ptr1) const
    {
        tmp3->val = 100;
    }

    void func3(Data1 *ptr1) const
    {
        gptr1->val = 100;
    }

    void func4(Data1 *ptr1) const
    {
        gptr2->val = 100;
    }

    void func5(Data1 *ptr1) const
    {
        tmp1->getData2();
    }

    void func6(Data1 *ptr1) const
    {
        tmp3->getData2();
    }

    void func7(Data1 *ptr1) const
    {
        Data1 val1;
        val1.val = 100;
    }

    void func8(Data1 &ptr1) const
    {
        ptr1.val = 200;
    }

    void func9(Data1 *ptr1) const
    {
        Data1 *val1;
        val1->val = 300;
    }

    void func10(Data1 &ptr1) const
    {
        if (ptr1.val == 100)
            k = 100;
    }

    void func11(Data2 &ptr1) const
    {
        if (ptr1.val == 100)
            k = 100;
    }

    int func12(Data2 &ptr1) const
    {
        const int &ref1 = ptr1.val;
        return ref1;
    }

//    broken for now
    void func13(Data1 *ptr1) const
    {
        tmp3->getData2()->val = 100;
    }

//    broken for now
    void func14(Data1 *ptr1) const
    {
        tmp1->getData2()->val = 100;
    }
};
