struct Data1
{
    int val;
};

int k;

int func1(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (ptr1 ? 0 : 1)
        return(0);

    ptr1->val = 100;
}

int func2(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (ptr1 == (123, 0))
        return 0;
    ptr1->val = 100;
    return 0;
}

int func3(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (ptr1 != (123, 0))
        return 0;
    ptr1->val = 100;
    return 0;
}

void func4(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (k == 10)
    {
        if (!ptr1)
            return;
    }

    ptr1->val = 100;
}

void func5(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (!ptr1)
        return;

    if (ptr2)
        return;

    ptr1->val = 100;
}
