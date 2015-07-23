struct Data1;
struct Data2;

struct Data2
{
    int val;
    Data1 *ptrval;
    int arr[3];
    Data1 *getData3()
    {
        return ptrval;
    }
};

struct Data1
{
    int val;
    Data1 *ptrval;
    Data2 perm;
    int arr[3];
    virtual ~Data1();
    virtual Data1 *getData3(int &k)
    {
        val = k;
        return ptrval;
    }
    static Data1 *getData4()
    {
        return 0;
    }
    Data2 *getData5() __attribute__((returns_nonnull))
    {
        return &perm;
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

    void func1(Data1 *ptr1) const __attribute__((nonnull(2)))
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
        int k100 = 100;
        ptr1->getData3(k100);
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

};
