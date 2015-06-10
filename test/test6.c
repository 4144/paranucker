void func1(int *a);
void func2(int *a);
void func3(int *a);
void func4(int *a);
void func5(int *a);
void func6(int *a);

void func1(int *a)
{
    *a = 100;
}

void func2(int *a)
{
    if (!a)
        return;
    else
        *a = 200;
}

void func3(int *a)
{
    if (!a)
        return;

    *a = 300;
}

void func4(int *a)
{
    if (a)
    {
        *a = 400;
    }
}

void func5(int *a)
{
    if (a)
    {
        *a = 500;
    }
    *a = 600;
}

void func6(int *aptr)
{
    if (!aptr)
    {
        int k = 10;
        return;
    }

    *aptr = 700;
}
