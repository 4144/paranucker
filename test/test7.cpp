class Object1
{
    int k;
    void func1()
    {
    }

    void func2(int *aptr)
    {
        *aptr = 0;
    }

    void func3(int *aptr)
    {
        if (aptr)
            *aptr = 0;
    }

    void func4(int *aptr)
    {
        k = 3;
    }
};
