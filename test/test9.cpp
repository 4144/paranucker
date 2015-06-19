class Object1
{
    int k;

    void func1(int *ptr1, int *ptr2)
    {
        if (!ptr1 || !ptr2)
        {
            return;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func2(int *ptr1, int *ptr2)
    {
        if (!ptr1 || !ptr2)
        {
            return;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func3(int *ptr1, int *ptr2)
    {
        if (ptr1 || ptr2)
        {
            return;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func4(int *ptr1, int *ptr2)
    {
        if (ptr1 || ptr2)
        {
            return;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func5(int *ptr1, int *ptr2)
    {
        if (!ptr1 || ptr2)
        {
            return;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func6(int *ptr1, int *ptr2)
    {
        if (!ptr1 || ptr2)
        {
            return;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func7(int *ptr1, int *ptr2)
    {
        if (ptr1 || !ptr2)
        {
            return;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func8(int *ptr1, int *ptr2)
    {
        if (!ptr1 && !ptr2)
        {
            return;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func9(int *ptr1, int *ptr2)
    {
        if (ptr1 && ptr2)
        {
            return;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func10(int *ptr1, int *ptr2)
    {
        if (!ptr1 || !ptr2)
        {
            int k = 0;
        }
        else
        {
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func11(int *ptr1, int *ptr2)
    {
        if (!ptr1 || ptr2)
        {
            int k = 10;
            *ptr1 = 100;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }

    void func12(int *ptr1, int *ptr2)
    {
        if (!ptr1 || k == 10)
        {
            *ptr1 = 100;
        }
        else
        {
            *ptr1 = 400;
        }

        *ptr1 = 200;
        *ptr2 = 300;
    }
};
