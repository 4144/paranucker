struct Data1;

struct Data1
{
    int val;
    Data1 *ptrval;
    int arr[3];
};

struct Data2 : public Data1
{
};

int k;

void paranuckerInternalTest(const char *action, const char *collection, const char *values);

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;

    Data1 *getData1()
    {
        return tmp2;
    }

    Data1 *getData2() __attribute__((returns_nonnull))
    {
        return tmp2;
    }

    void func1(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        while (ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            ptr1->val = 100;
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        ptr1->val = 200;
    }

    void func2(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        if (ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            ptr1->val = 100;
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        ptr1->val = 200;
    }

    void func3(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        if (ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func4(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        while (ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func5(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        if (!ptr1)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
        if (ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func6(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        if (!ptr1)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
        while (ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func7(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        if (!ptr1)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
        while (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func8(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        while (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            ptr1 = getData2();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func9(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        ptr1 = getData1();
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        if (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
    }

    void func10(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        while (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func11(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        while (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            if (!ptr1)
                return;
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
    }

    void func12(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        while (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            if (!ptr1)
                continue;
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
    }

    void func13(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        while (ptr1 && ptr1->val == 100)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            ptr1 = getData1();
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            if (!ptr1)
                break;
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
    }
};
