void func1(int *a);
void func2(int *a);
void func3(int *a);
void func4(int *a);
void func5(int *a);
void func6(int *a);
void func7(int *a);
void func8(int *a);

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

void func6(int *a)
{
    if (!a)
    {
        int k = 10;
        return;
    }

    *a = 700;
}

void func7(int *aptr)
{
    if (1 == 0)
    {
        if (!aptr)
        {
            int k = 10;
            return;
        }
    }

    *aptr = 800;
}

void func8(int *aptr)
{
    if (!aptr)
    {
        if (1 == 0)
        {
            int k = 10;
            int l = 20;
        }
        return;
    }

    *aptr = 900;
}
