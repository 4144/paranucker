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
        int val1 = ptr1 ? ptr1->val : ptr2->val;
    }

    void func2(Data1 *ptr1, Data1 *ptr2)
    {
        int val1 = (!ptr1) ? ptr1->val : ptr2->val;
    }

    void func3(Data1 *ptr1, Data1 *ptr2)
    {
        int val1 = (ptr1 && !ptr2) ? ptr1->val : ptr2->val;
    }

    void func4(Data1 *ptr1, Data1 *ptr2)
    {
        if ((ptr1 ? ptr1 : ptr2)->val == 100)
        {
            ptr1->val = 200;
        }
        else
        {
            ptr2->val = 300;
        }
    }

    void func5(Data1 *ptr1, Data1 *ptr2)
    {
        int tmp = (ptr1 ? ptr1 : ptr2)->val;
    }

    void func6(Data1 *ptr1, Data1 *ptr2)
    {
        int tmp = ptr1 ? ptr1->val : (ptr2 ? ptr2->val : 0);
    }

    void func7(Data1 *ptr1, Data1 *ptr2)
    {
        int tmp = ptr1 ? ptr1->val : (!ptr2 ? ptr2->val : 0);
    }
};
