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

struct Data2
{
    virtual ~Data2()
    {
    }
};

int k;

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;

    void func1(Data1 *const ptr1)
    {
        tmp1 = ptr1;
        if (tmp1)
        {
            ptr1->val = 100;
            tmp1->val = 200;
        }
        else
        {
            ptr1->val = 300;
            tmp1->val = 400;
        }
        ptr1->val = 500;
        tmp1->val = 600;
    }

    void func2(Data1 *const ptr1)
    {
        tmp1 = ptr1;
        tmp2 = tmp1;
        if (tmp2)
        {
            ptr1->val = 100;
            tmp1->val = 200;
            tmp2->val = 300;
        }
        else
        {
            ptr1->val = 400;
            tmp1->val = 500;
            tmp2->val = 600;
        }
        ptr1->val = 700;
        tmp1->val = 800;
        tmp2->val = 900;
    }

    void func3(Data1 *ptr1)
    {
        Data1 *ptr2;
        ptr1->val = 100;
        ptr1 = ptr2;
        ptr2->val = 200;
        if (!ptr1)
        {
            ptr1->val = 300;
        }
        ptr1->val = 400;
    }

    void func4(Data1 *const ptr1)
    {
        Data1 *ptr2;
        tmp1 = ptr1;
        tmp1 = ptr2;

        if (tmp1)
        {
            ptr1->val = 100;
            tmp1->val = 200;
        }
        else
        {
            ptr1->val = 300;
            tmp1->val = 400;
        }
        ptr1->val = 500;
        tmp1->val = 600;
    }

    void func5(Data1 *ptr1, Data1 *ptr3)
    {
        Data1 *ptr2;
        ptr1->val = 100;
        ptr1 = ptr2;
        ptr2->val = 200;
        if (!ptr1)
        {
            ptr1->val = 300;
        }
        ptr1 = ptr3;
        ptr1->val = 400;
        ptr1 = ptr2;
        ptr1->val = 500;
    }

    void func6(Data1 *ptr1, Data1 *ptr3)
    {
        ptr1->val = 100;
        ptr1 = tmp1;
        tmp1->val = 200;
        if (!ptr1)
        {
            ptr1->val = 300;
        }
        ptr1 = ptr3;
        ptr1->val = 400;
        ptr1 = tmp2;
        ptr1->val = 500;
    }

    void func7(Data1 *ptr1, Data1 *ptr3)
    {
        Data1 *ptr2;
        tmp1 = ptr3;
        ptr1->val = 100;
        ptr1 = ptr2;
        ptr2->val = 200;
        if (!ptr1)
        {
            ptr1->val = 300;
        }
        ptr1 = ptr3;
        ptr1->val = 400;
        ptr1 = tmp1;
        ptr1->val = 500;
    }

    void func8(Data1 *ptr1, Data1 *ptr3)
    {
        Data1 *ptr2;
        tmp1 = ptr3;
        if (ptr1)
        ptr1->val = 100;
        ptr1 = ptr2;
        ptr2->val = 200;
        if (!ptr1)
        {
            ptr1->val = 300;
        }
        ptr1 = ptr3;
        if (ptr3)
            ptr1->val = 400;
        ptr1 = tmp1;
        ptr2 = ptr1;
        if (tmp1)
            ptr1->val = 500;
        if (ptr2)
            ptr1->val = 600;
    }
};
