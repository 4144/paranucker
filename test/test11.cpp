class Data1
{
    public:
        int val;
};

class Object1
{
    int k;

    void func1(Data1 *ptr1, Data1 *ptr2)
    {
        if (!ptr1 || ptr1->val == 100)
        {
            return;
        }

        ptr1->val = 200;
    }

    void func2(Data1 *ptr1, Data1 *ptr2)
    {
        if (ptr1 && ptr1->val == 100)
        {
            ptr1->val = 200;
            return;
        }

        ptr1->val = 300;
    }

    void func3(Data1 *ptr1, Data1 *ptr2)
    {
        if (ptr1 || ptr1->val == 100)
        {
            return;
        }

        ptr1->val = 200;
    }

    void func4(Data1 *ptr1, Data1 *ptr2)
    {
        if (!ptr1 && ptr1->val == 100)
        {
            return;
        }

        ptr1->val = 200;
    }

    void func5(Data1 *ptr1, Data1 *ptr2)
    {
        if ((!ptr1 || ptr1->val == 100) || (!ptr2 || ptr2->val == 200))
        {
            return;
        }

        ptr1->val = 300;
        ptr2->val = 400;
    }

    void func6(Data1 *ptr1, Data1 *ptr2)
    {
        if ((!ptr1 || ptr1->val == 100) && (!ptr2 || ptr2->val == 200))
        {
            return;
        }

        ptr1->val = 300;
        ptr2->val = 400;
    }
};
