void func1(int a, int *b, char c);
void func2(int a, int *b, char c);

void func1(int a, int *b, char c)
{
    *b = 100;
}

void func2(int a, int *b, char c)
{
    *(1 + b) = 200;
}
