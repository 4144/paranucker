struct Data1;

struct Data1
{
    int val;
    Data1 *ptrval;
    int arr[3];
    Data1 *getData3()
    {
        return ptrval;
    }
    static Data1 *getData4()
    {
        return 0;
    }
};

struct Data2
{
    int val;
    Data1 *ptrval;
    int arr[3];
    virtual ~Data2()
    {
    }
    Data1 *getData3()
    {
        return ptrval;
    }
};

struct Data3
{
    int val;
    Data1 *ptrval;
    int arr[3];
    virtual ~Data3()
    {
    }

    Data3(int v) :
        val(v)
    {
    }

    Data1 *getData3()
    {
        return ptrval;
    }
};

int k;

void paranuckerInternalTest(const char *action, const char *collection, const char *values);

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;
    Data2 *tmp3;
    Data3 *tmp4;

    Data1 *getData1()
    {
        return tmp2;
    }

    Data1 *getData2() __attribute__((returns_nonnull))
    {
        return tmp2;
    }

    void func1()
    {
        Data1 *ptr1 = new Data1;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func2()
    {
        Data1 *ptr1 = new Data1[10];
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func3()
    {
        int *ptr1 = new int[10];
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func4()
    {
        tmp1 = new Data1;
        paranuckerInternalTest("=", "knownVars", "this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func5()
    {
        tmp3 = new Data2;
        paranuckerInternalTest("=", "knownVars", "this->tmp3");
        paranuckerInternalTest("=", "knownNonNullVars", "this->tmp3");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp3");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp3");
    }

    void func6() const
    {
        Data1 *ptr1 = Data1::getData4();
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        if (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            ptr1 = new Data1;
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        if (k == 10)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1->val = 100;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func7()
    {
        tmp4 = new Data3(100);
        paranuckerInternalTest("=", "knownVars", "this->tmp4");
        paranuckerInternalTest("=", "knownNonNullVars", "this->tmp4");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp4");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp4");
        tmp4->getData3();
        paranuckerInternalTest("=", "knownVars", "this->tmp4");
        paranuckerInternalTest("=", "knownNonNullVars", "this->tmp4");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp4");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp4");
    }
};
