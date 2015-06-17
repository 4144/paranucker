class Object1
{
    int k;

    void func1(int *ptr1)
    {
        if (!ptr1)
            return;

        *ptr1 = 100;
    }

    void func2(int *ptr2)
    {
        if (!ptr2)
        {
            k = 0;
        }

        *ptr2 = 200;
    }

    void func3(int *ptr3)
    {
        if (ptr3)
            return;

        *ptr3 = 300;
    }

    void func4(int *ptr4)
    {
        if (ptr4)
            k = 0;
        else
            return;

        *ptr4 = 400;
    }

    void func5(int *ptr5)
    {
        if (!ptr5)
            return;
        else
            *ptr5 = 501;

        *ptr5 = 500;
    }

    void func6(int *ptr6)
    {
        if (ptr6)
        {
            if (!ptr6)
                return;
        }

        *ptr6 = 600;
    }

    void func7(int *ptr7)
    {
        if (!ptr7)
        {
            return;
        }
        else
        {
            if (!ptr7)
                return;
            *ptr7 = 701;
        }

        *ptr7 = 700;
    }
};
