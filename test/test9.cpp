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



/*
    void func8(int *ptr1, int *ptr2)
    {
        int c;
        if (k == c || !ptr1)
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
*/
};
