struct Data1;

struct Data1
{
    int val;
    Data1 *ptrval;
    int arr[3];
    Data1 *getData3() const
    {
        return ptrval;
    }
};

struct Data2 : public Data1
{
};

int k;

Data1 *getfData1()
{
    return 0;
}

Data1 *getfData2() __attribute__((returns_nonnull));
Data1 *getfData2()
{
    return 0;
}

void paranuckerInternalTest(const char *action, const char *collection, const char *values);

class Object1
{
    Data1 *tmp1;
    Data1 *tmp2;
    Data1 *tmp3;
    int val1;

    Object1() :
        tmp3(getfData2())
    {
        tmp3->val = 100;
    }

    Data1 *getData1()
    {
        return tmp1;
    }

    Data1 *getData2() __attribute__((returns_nonnull))
    {
        return tmp1;
    }

    int getInt()
    {
        return 123;
    }

    void func1(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        long var1 = reinterpret_cast<long>(ptr1);
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func2(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1 = reinterpret_cast<Data1*>(getInt());
        paranuckerInternalTest("=", "knownVars", "");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "linkedVars", "");
        paranuckerInternalTest("=", "linkedReverseVars", "");
        val1 = getInt();
        paranuckerInternalTest("=", "knownVars", "");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "linkedVars", "");
        paranuckerInternalTest("=", "linkedReverseVars", "");
    }

    void func3(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1 = getData1();
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func4(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1 = getData2();
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func5(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        tmp1 = getData1();
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func6(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        tmp1 = getfData1();
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func7(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        tmp1 = getfData1();
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        if (!tmp1 || tmp1->val == 10)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            paranuckerInternalTest("=", "linkedVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        }
    }

    void func8(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        Data1 *const var1 = getData2();
        paranuckerInternalTest("=", "knownVars", "ptr1 var1");
        paranuckerInternalTest("=", "knownNonNullVars", "var1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        Data1 *var2 = var1->getData3();
        paranuckerInternalTest("=", "knownVars", "ptr1 var1 var2");
        paranuckerInternalTest("=", "knownNonNullVars", "var1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 var2");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }
};
