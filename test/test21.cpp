struct Data1
{
    int val;
};

int k;

class Object1
{
    int func1(void *ptr1)
    {
        int tmpvar = 0;
        Data1 *const ptr2 = static_cast<Data1*>(ptr1);

        if (!ptr1)
        {
            return 0;
        }

        if (ptr2->val)
        {
            return 3;
        }
        return 0;
    }

    int func2(void *ptr1)
    {
        int attempts = 0;
        Data1 *const ptr2 = reinterpret_cast<Data1*>(ptr1);

        if (!ptr2)
            return 0;

        int outFilename = ptr2->val;
    }

    int func3(void *ptr1)
    {
        if (!ptr1)
            return 1;

        Data1 *const ptr2 = reinterpret_cast<Data1*>(ptr1);
        int val = ptr2->val;
    }

    int func4(Data1 *const ptr1)
    {
        const Data1 *ptr2 = static_cast<Data1*>(0);
        if (ptr1 && ptr2)
        {
            int k = ptr1->val;
        }
    }

    int func5(Data1 *const ptr1)
    {
        const Data1 *ptr2 = static_cast<Data1*>(0);
        int z;
        if (ptr2 && ptr1 && z == 12)
        {
            const Data1 *const ptr3 = reinterpret_cast<const Data1* const>(ptr2);
            if (ptr3)
            {
                if (ptr1->val == 10)
                {
                    int k2 = ptr1->val + 1;
                }
            }
        }
    }

    int func6(Data1 *const ptr1)
    {
        const Data1 *ptr2 = static_cast<Data1*>(0);
        if (ptr2 && ptr1 && k == 10)
        {
            k = ptr1->val;
        }
    }
};
