struct Data1
{
    int val;
};

int k;

void func1(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (!ptr1 || ptr1->val == 100)
    {
        return;
    }

    ptr1->val = 200;
}

void func2(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (ptr1 && ptr1->val == 100)
    {
        ptr1->val = 200;
        return;
    }

    ptr1->val = 300;
}

void func3(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (ptr1 || ptr1->val == 100)
    {
        return;
    }

    ptr1->val = 200;
}

void func4(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (!ptr1 && ptr1->val == 100)
    {
        return;
    }

    ptr1->val = 200;
}

void func5(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if ((!ptr1 || ptr1->val == 100) || (!ptr2 || ptr2->val == 200))
    {
        return;
    }

    ptr1->val = 300;
    ptr2->val = 400;
}

void func6(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if ((!ptr1 || ptr1->val == 100) && (!ptr2 || ptr2->val == 200))
    {
        return;
    }

    ptr1->val = 300;
    ptr2->val = 400;
}
