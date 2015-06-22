struct Data1
{
    int val;
};

int k;

int func1(struct Data1 *ptr1, struct Data1 *ptr2)
{
    struct Data1 *ptr3 = ptr1;
}

int func2(struct Data1 *ptr1, struct Data1 *ptr2)
{
    struct Data1 *ptr3 = ptr1;
    ptr3->val = 100;
}

int func3(struct Data1 *ptr1, struct Data1 *ptr2)
{
    struct Data1 *ptr3 = ptr1;
    if (ptr3)
        ptr3->val = 100;
}

int func4(struct Data1 *ptr1, struct Data1 *ptr2)
{
    struct Data1 *ptr3 = ptr1;
    if (ptr3)
        ptr3->val = 100;
    else if (!ptr1 && ptr2)
        ptr2->val = 200;
}

int func5(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (!ptr1 || k == 10)
        return 0;

    struct Data1 *ptr3 = ptr1;

    ptr3->val = 100;
}

int func6(struct Data1 *ptr1, struct Data1 *ptr2)
{
    if (ptr1 || k == 10)
        return 0;

    struct Data1 *ptr3 = ptr1;

    ptr3->val = 100;
}

int func7(struct Data1 *ptr1, struct Data1 *ptr2)
{
    int c;
    if (k != c)
    {
        if (!ptr1)
            return 0;
    }

    struct Data1 *ptr3 = ptr1;

    ptr1->val = 100;
    ptr3->val = 200;
}

int func8(struct Data1 *ptr1, struct Data1 *ptr2)
{
    int c;
    if (k != c)
    {
        if (ptr1)
            return 0;
    }

    struct Data1 *ptr3 = ptr1;

    ptr1->val = 100;
    ptr3->val = 200;
}
