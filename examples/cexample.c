int k;

int main(void)
{
}

void func1(int *ptr1, int *ptr2)
{
    if (ptr1 || ptr2)
    {
        *ptr2 = 400;
    }
    else
    {
        *ptr1 = 100;
    }
        *ptr1 = 200;
    *ptr2 = 300;
}

void func2(int *ptr1, int *ptr2)
{
    if (ptr1 || ptr2)
    {
        *ptr2 = 400;
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

void func4(int *ptr1, int *ptr2)
{
    int c;
    if (k == c || !ptr1 || !ptr2)
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
    int c;
    if (!ptr1 || !ptr2 || k == c)
    {
        c = 3;
    }
    else
    {
        *ptr1 = 100;
    }

    *ptr1 = 200;
    *ptr2 = 300;
}

void func6(int *ptr1, int *ptr2)
{
    if (ptr1 && ptr2)
    {
        *ptr1 = 100;
        *ptr2 = 200;
    }
    else
    {
        return;
    }

    *ptr1 = 300;
    *ptr2 = 400;
}

void func7(int *ptr1, int *ptr2)
{
    if (!ptr1 && !ptr2)
    {
        *ptr1 = 100;
        *ptr2 = 200;
    }
    else
    {
        return;
    }

    *ptr1 = 300;
    *ptr2 = 400;
}

void func8(int *ptr1, int *ptr2)
{
    if (ptr1 && ptr2)
    {
        *ptr1 = 100;
        *ptr2 = 200;
        return;
    }
    else
    {
        *ptr1 = 300;
        *ptr2 = 400;
        return;
    }

    *ptr1 = 500;
    *ptr2 = 600;
}

void func9(int *ptr1, int *ptr2)
{
    if (ptr1 || ptr2)
    {
        *ptr2 = 100;
        return;
    }
    else
    {
        *ptr1 = 200;
        return;
    }

    *ptr1 = 300;
    *ptr2 = 400;
}

void func10(int *ptr1, int *ptr2)
{
    if (ptr1 && ptr2 && k)
    {
        *ptr1 = 100;
        *ptr2 = 200;
        return;
    }
    else
    {
        *ptr1 = 300;
        *ptr2 = 400;
    }

    *ptr1 = 500;
    *ptr2 = 600;
}

void func11(int *ptr1, int *ptr2)
{
    if (ptr1 && ptr2 || ptr1)
    {
        *ptr1 = 100;
        *ptr2 = 200;
        return;
    }
    else
    {
        *ptr1 = 300;
        *ptr2 = 400;
    }

    *ptr1 = 500;
    *ptr2 = 600;
}

void func12(int *ptr1, int *ptr2)
{
    if (ptr1 || !ptr1)
    {
        *ptr1 = 100;
        *ptr2 = 200;
        return;
    }
    else
    {
        *ptr1 = 300;
        *ptr2 = 400;
    }

    *ptr1 = 500;
    *ptr2 = 600;
}
