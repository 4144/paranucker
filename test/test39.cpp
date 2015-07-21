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

int k;

void paranuckerInternalTest(const char *action, const char *collection, const char *values);

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;
    Data2 *tmp3;

    Data1 *getData1()
    {
        return tmp2;
    }

    Data1 *getData2() __attribute__((returns_nonnull))
    {
        return tmp2;
    }

    void func1(Data1 *ptr1) const
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1->val = 100;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1->val = 0;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func2(Data1 *ptr1) const
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1->ptrval = reinterpret_cast<Data1*>(1);
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1->ptrval");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1->ptrval");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func3(Data1 *ptr1) const
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1->ptrval = 0;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1->ptrval");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr1->ptrval");
        paranuckerInternalTest("=", "addNullVars", "ptr1->ptrval");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func4() const
    {
        paranuckerInternalTest("=", "knownVars", "");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        Data1 data2;
        paranuckerInternalTest("=", "knownVars", "");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        Data1 *ptr1 = &data2;
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
};
