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

    int func1()
    {
        Data1 *ptr1 = getData1();
        tmp2 = ptr1;
        if (tmp2)
        {
            if (k == 10)
            {
                int val = ptr1->val;
                return val;
            }
        }
        return 0;
    }

    void func2()
    {
        Data1 *ptr1 = tmp1->getData3();
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        while (ptr1 && ptr1->val == 3 && ptr1->ptrval)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            ptr1 = ptr1->ptrval->getData3();
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1->ptrval");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
    }

    void func3()
    {
        Data1 *ptr1 = tmp1->getData3();
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "addNullVars", "ptr1");
        paranuckerInternalTest("=", "removeNullVarsAll", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        while (ptr1 && ptr1->val == 3 && ptr1->ptrval)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            ptr1 = ptr1->getData3();
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1->ptrval");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            ptr1 = ptr1->ptrval->getData3();
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr1->ptrval");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1->ptrval");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "ptr1");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        }
    }
};
