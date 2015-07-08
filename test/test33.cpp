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

    void func1(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        while (ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            ptr1->val = 100;
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        ptr1->val = 200;
    }

    void func2(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        if (ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            ptr1->val = 100;
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        ptr1->val = 200;
    }

    void func3(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        while (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            ptr1->val = 100;
            return;
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        ptr1->val = 200;
        tmp2 = ptr1;
        if (tmp2)
            tmp2->val = 300;
    }

};
