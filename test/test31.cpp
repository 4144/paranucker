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
    Data1 *tmp3;

    Data1 *getData()
    {
        return tmp1;
    }

    void func1(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func2(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        tmp2 = tmp1;
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1 this->tmp2");
    }

    void func3(Data1 *ptr1)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        // wco if_stmt  clean checkedThenNonNullVars:ptr1,  checkedElseNullVars:ptr1,  needCheckNullVars:ptr1, this->tmp1,
        //      knownVars:ptr1, this->tmp1,  knownNonNullVars:ptr1,  addNullVars:this->tmp1,
        //      linkedVars:ptr1 -> (this->tmp1, ),  linkedReverseVars:this->tmp1 -> ptr1
        if (ptr1)
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            if (tmp1)
                return;
        }
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
    }

    void func4(Data1 *ptr1)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        if (ptr1)
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        }
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
    }

    void func5(Data1 *ptr1)
    {
        tmp1 = ptr1;
        if (!ptr1)
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
        }
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
    }

    void func6(Data1 *ptr1)
    {
        tmp1 = ptr1;
        if (!tmp1)
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
        }
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
    }

    void func7(Data1 *ptr1)
    {
        tmp1 = ptr1;
        tmp2 = ptr1;
        if (!tmp2)
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "addNullVars", "this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            if (!ptr1)
            {
                paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
                paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
                paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
                paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "knownNonNullVars", "");
                paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "addNullVars", "this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "removeNullVars", "");
                paranuckerInternalTest("=", "removeNullVarsAll", "");
            }
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "addNullVars", "this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            paranuckerInternalTest("=", "removeNullVars", "");
            paranuckerInternalTest("=", "removeNullVarsAll", "");
            if (tmp1)
            {
                paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
                paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
                paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
                paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "knownNullVars", "");
                paranuckerInternalTest("=", "needCheckNullVars", "");
                paranuckerInternalTest("=", "removeNullVars", "");
                paranuckerInternalTest("=", "removeNullVarsAll", "");
            }
        }
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
        paranuckerInternalTest("=", "removeNullVars", "");
        paranuckerInternalTest("=", "removeNullVarsAll", "this->tmp2");
    }

    void func8(Data1 *ptr1)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        tmp1 = tmp2;
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func9(Data1 *ptr1)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        ptr1 = tmp2;
        paranuckerInternalTest("=", "knownVars", "this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
    }

    void func10(Data1 *ptr1)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        tmp2 = tmp1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        tmp2 = tmp3;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
    }

    void func11(Data1 *ptr1)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        tmp2 = tmp1;
        paranuckerInternalTest("=", "knownVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        ptr1 = tmp3;
        paranuckerInternalTest("=", "knownVars", "this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 this->tmp1");
    }

    void func12(Data1 *ptr1, Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "tmp1");
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
    }

    void func13(Data1 *ptr1, Data1 *ptr2)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        ptr1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr2 ptr1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
    }

    void func14(Data1 *ptr1, Data1 *ptr2)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        tmp1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1");
        paranuckerInternalTest("=", "linkedVars", "ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr2");
    }

    void func15(Data1 *ptr1, Data1 *ptr2)
    {
        tmp1 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2");
        tmp2 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr2 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr2");
        tmp2 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        tmp2 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "ptr2 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr2");
    }

    void func16(Data1 *ptr1, Data1 *ptr2)
    {
        tmp1 = ptr1;
        tmp2 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        if (tmp1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        if (!ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            if (ptr2 && k == 10)
            {
                paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "knownNonNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "knownNullVars", "");
                paranuckerInternalTest("=", "needCheckNullVars", "");
                paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
                paranuckerInternalTest("=", "linkedVars", "ptr2");
                paranuckerInternalTest("=", "linkedVars", "this->tmp1");
                paranuckerInternalTest("=", "linkedVars", "this->tmp2");
                paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
                paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
                paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
                paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
                return;
            }
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
    }

    void func17(Data1 *ptr1, Data1 *ptr2)
    {
        tmp1 = ptr1;
        tmp2 = ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
        if (tmp1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            tmp1 = tmp3;
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            tmp3 = ptr2;
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp2 this->tmp3");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1 this->tmp2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2 this->tmp3");
            paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "ptr2 this->tmp3");
            paranuckerInternalTest("=", "linkedVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedVars", "this->tmp2");
            paranuckerInternalTest("=", "linkedVars", "this->tmp3");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
            paranuckerInternalTest("=", "linkedReverseVars", "this->tmp3 ptr2");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2 this->tmp1 this->tmp2 this->tmp3");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2 this->tmp1 this->tmp2 this->tmp3");
        paranuckerInternalTest("=", "linkedVars", "ptr1 this->tmp1 this->tmp2");
        paranuckerInternalTest("=", "linkedVars", "ptr2");
        paranuckerInternalTest("=", "linkedVars", "this->tmp1");
        paranuckerInternalTest("=", "linkedVars", "this->tmp2");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "ptr2");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp1 ptr1");
        paranuckerInternalTest("=", "linkedReverseVars", "this->tmp2 ptr1");
    }
};
