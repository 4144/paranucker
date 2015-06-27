struct Data1;

typedef void (*FuncPtr1) (void);
typedef void (*FuncPtr2) (struct Data1 *ptr);

struct Data1
{
    int val;
    struct Data1 *ptrval;
    int arr[3];
    FuncPtr2 fptr1;
    FuncPtr2 fptr2[3];
};

int ftest1(void)
{
    return 1;
}

static int ftest2(struct Data1 *ptr0)
{
    return 1;
}

void ftest3(struct Data1 *ptr0)
{
}

int k;

void func1(FuncPtr1 ptr1)
{
    ptr1();
}

void func2(struct Data1 *ptr1)
{
    FuncPtr2 fptr2;
    fptr2(ptr1);
}

void func3(struct Data1 *ptr1)
{
    struct Data1 *data;
    data->fptr1(ptr1);
}

void func4(struct Data1 *ptr1)
{
    struct Data1 *ptr2;
    ptr1->fptr1(ptr2);
}

void func5(struct Data1 *ptr1)
{
    struct Data1 *data;
    (*data->fptr2[1])(ptr1);
}

void func6(FuncPtr2 ptr1[3])
{
    struct Data1 *data;
    (*ptr1[1])(data);
}

int test1(char *w1, char *w2)
{
}

void func7(char *w1, char *w2)
{
    int (*fptr[]) (char *w1, char *w2) =
    {
        test1
    };
    int i;
    for(i = 0; i < 10; i++)
    {
        if ((*fptr[i])(w1,w2))
            break;
    }
}

void func8(int (*fptr[]) (char *w1, char *w2))
{
    fptr[1]("", "");
}
