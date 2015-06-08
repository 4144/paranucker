int main(void)
{
    return 0;
}

void func4_1(int a, int *b, char *c);
void func4_2(int a, int *b, char *c) __attribute__((nonnull (2)));
void func4_3(int a, int *b, char *c) __attribute__((nonnull (2, 3)));

void func4_1(int a, int *b, char *c)
{
    return;
}

void func4_2(int a, int *b, char *c)
{
    return;
}

void func4_3(int a, int *b, char *c)
{
    return;
}
