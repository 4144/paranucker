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
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        if (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            ptr1 = new Data1;
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
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func2(Data1 *ptr1)
    {
        tmp1 = ptr1;
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
        if (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "addNullVars", "this->tmp1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            ptr1 = new Data1;
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "this->tmp1");
            paranuckerInternalTest("=", "needCheckNullVars", "this->tmp1");
            paranuckerInternalTest("=", "addNullVars", "this->tmp1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "this->tmp1");
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func3(Data1 *ptr1)
    {
        tmp1 = ptr1;
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
        if (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "addNullVars", "this->tmp1");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            tmp1 = new Data1;
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "this->tmp1");
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
        paranuckerInternalTest("=", "addNullVars", "this->tmp1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
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
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        if (!ptr1 && !tmp1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            ptr1 = new Data1;
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
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        if (!ptr1 || !tmp1)
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
            ptr1 = new Data1;
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
        // after flags can be different
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
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        while (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            ptr1 = new Data1;
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
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "addNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }
};
