struct Data1
{
    int val;
};

int k;

int func1(struct Data1 *ptr1, struct Data1 *ptr2)
{
    Data1 *ptr3 = ptr1;
}

int func2(struct Data1 *ptr1, struct Data1 *ptr2)
{
    Data1 *ptr3 = ptr1;
    ptr3->val = 100;
}

int func3(struct Data1 *ptr1, struct Data1 *ptr2)
{
    Data1 *ptr3 = ptr1;
    if (ptr3)
        ptr3->val = 100;
}

int func4(struct Data1 *ptr1, struct Data1 *ptr2)
{
    Data1 *ptr3 = ptr1;
    if (ptr3)
        ptr3->val = 100;
    else if (!ptr1 && ptr2)
        ptr2->val = 200;
}
