void func1(int a, int *b, char c);
void func2(int a, int *b, char c);
void func3(int a, int *b, char c);
void func4(int a, int *b, char c);
void func5(int a, int *b, char c);
void func6(int a, int *b, char c);
void func7(int a, int *b, char c);
void func8(int a, int *b, char c);

void func1(int a, int *b, char c)
{
    *b = 100;
}

void func2(int a, int *b, char c)
{
    *(1 + b) = 200;
}

void func3(int a, int *b, char c)
{
    *(1 + (1 + b)) = 300;
}

void func5(int a, int *b, char c)
{
    int var1 = 1;
    *(var1 + b) = 400;
}

void func6(int a, int *b, char c)
{
    int *var2 = b;
    *var2 = 500;
}

void func7(int a, int *b, char c)
{
    int *var3 = 12 + b;
    *var3 = 600;
}

void func8(int a, int *bptr, char c)
{
    int **var4 = &bptr;
    **var4 = 700;
}
