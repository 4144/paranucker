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
        if (!ptr1 || ptr1->val == 1)
        {
            return;
        }

        ptr1->val = 100;
    }

    void func2(Data1 *ptr1, Data1 *ptr2)
    {
        if (ptr1 && ptr1->val == 1)
        {
            ptr1->val = 100;
            return;
        }

        ptr1->val = 200;
    }
};
