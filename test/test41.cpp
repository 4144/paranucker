struct Data1;
struct Data2;

struct Data1
{
    int val;
    Data1 *ptrval;
    int arr[3];
};

int k;

void paranuckerInternalTest(const char *action, const char *collection, const char *values);

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;

    Data1 *getData1()
    {
        return tmp1;
    }

    Data1 *getData2()
    {
        return tmp1;
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
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        if (ptr1 == (getData1(), getData2(), static_cast<Data1*>(0)))
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        }
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

    void func2(Data1 *ptr1)
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
        if (ptr1 != (getData1(), getData2(), static_cast<Data1*>(0)))
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        }
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

    void func3(Data1 *ptr1)
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
        if ((getData1(), getData2(), ptr1))
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "addNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        }
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

};
