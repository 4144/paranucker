void func1(int *a);
void func2(int *a);
void func3(int *a);

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

void func3(int *aptr)
{
    if (!aptr)
        return;

    *aptr = 300;
}
