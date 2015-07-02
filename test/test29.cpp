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

    Data1 *getData()
    {
        return tmp1;
    }

    void func1(Data1 *ptr1, Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        if (!ptr2)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        ptr1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
    }

    void func2(Data1 *ptr1, Data2 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        if (!ptr2)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        ptr1 = dynamic_cast<Data1*>(ptr2);
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
    }

    Data1 *func3(Data1 *ptr2)
    {
        Data1 *ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        if (!ptr2)
            return 0;
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        ptr1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        return ptr1;
    }
};
