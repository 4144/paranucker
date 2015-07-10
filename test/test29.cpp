struct Data1;

struct Data1
{
    int val;
    Data1 *ptrval;
    int arr[3];
};

struct Data2 : public Data1
{
    virtual ~Data2();
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

    Data2 *getData2()
    {
        return nullptr;
    }

    void func1(Data1 *ptr1, Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        if (!ptr2)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
            return;
        }
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

    void func2(Data1 *ptr1, Data1 *ptr2)
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

    void func4(Data1 *ptr1, Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        if (ptr2)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
            return;
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        ptr1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
    }

    void func5(Data1 *ptr1, Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        if (ptr2)
            return;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        ptr1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
    }

    Data1 *func6(Data1 *ptr2)
    {
        Data1 *ptr1;
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        if (ptr2)
            return 0;
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        ptr1 = ptr2;
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        return ptr1;
    }

    void func7(Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        // null || 10 -> return
        // null || 9  -> return
        // 123  || 10 -> return
        // 123  || 9  -> continue
        // wco if_stmt  clean checkedElseNonNullVars:ptr2,  needCheckNullVars:ptr2,  knownVars:ptr2,
        if (!ptr2 || k == 10)
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
        }
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
    }

    void func8(Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        // null && 10 -> return
        // null && 9  -> continue
        // 123  && 10 -> continue
        // 123  && 9  -> continue
        // wco if_stmt  needCheckNullVars:ptr2,  knownVars:ptr2,  knownNullVars:ptr2,
        if (!ptr2 && k == 10)
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            return;
        }
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
    }

    void func9(Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        // null || 10 -> return
        // null || 9  -> contine
        // 123  || 10 -> return
        // 123  || 9  -> return
        // wco if_stmt  clean needCheckNullVars:ptr2,  knownVars:ptr2,
        if (ptr2 || k == 10)
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        }
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
    }

    void func10(Data1 *ptr1, Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        // null || null -> continue
        // null || 123  -> return
        // 123  || null -> return
        // 123  || 123  -> return
        // wco if_stmt  clean checkedElseNullVars:ptr1, ptr2,  needCheckNullVars:ptr1, ptr2,  knownVars:ptr1, ptr2,
        if (ptr2 || ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
    }

    void func11(int *ptr1, int *ptr2)
    {
        // null && null || null -> continue
        // null && 123  || null -> continue
        // 123  && null || 123  -> return
        // 123  && 123  || 123  -> return
        // wco if_stmt  clean checkedThenNonNullVars:ptr1,  checkedElseNullVars:ptr1,  needCheckNullVars:ptr1, ptr2,  knownVars:ptr1, ptr2,
        if ((ptr1 && ptr2) || ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
    }

    void func12(int *ptr1, int *ptr2)
    {
        // null || null && null -> continue
        // null || 123  && null -> continue
        // 123  || null && 123  -> return
        // 123  || 123  && 123  -> return
        if ((ptr1 || ptr2) && ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
    }

    void func13(int *ptr1)
    {
        // null -> continue
        // 123  -> return
        if ((ptr1 || ptr1) && ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
    }

    void func14(int *ptr1)
    {
        // null -> continue
        // 123  -> return
        if ((ptr1 && ptr1) || ptr1)
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr1");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr1");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "ptr1");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
        }
        paranuckerInternalTest("=", "knownVars", "ptr1");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "ptr1");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1");
    }

    void func15(Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        // null || 10 -> continue
        // null || 9  -> continue
        // 123  || 10 -> continue
        // 123  || 9  -> return
        // wco if_stmt  clean checkedElseNonNullVars:ptr2,  needCheckNullVars:ptr2,  knownVars:ptr2,
        if (!ptr2 || k == 10)
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            return;
        }
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
    }

    void func16(Data1 *ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
        // wco if_stmt  clean checkedElseNonNullVars:ptr2,  needCheckNullVars:ptr2,  knownVars:ptr2,
        if (!ptr2 || k == 10)
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "ptr2");
            return;
        }
        else
        {
            paranuckerInternalTest("=", "knownVars", "ptr2");
            paranuckerInternalTest("=", "knownNonNullVars", "ptr2");
            paranuckerInternalTest("=", "knownNullVars", "");
            paranuckerInternalTest("=", "needCheckNullVars", "");
            return;
        }
        paranuckerInternalTest("=", "knownVars", "ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "");
    }

    void func17(Data1 *ptr1, const Data2 *const ptr2)
    {
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
        const Data1 *const ptr3 = dynamic_cast<const Data1* const>(ptr2);
        paranuckerInternalTest("=", "knownVars", "ptr1 ptr2");
        paranuckerInternalTest("=", "knownNonNullVars", "");
        paranuckerInternalTest("=", "knownNullVars", "");
        paranuckerInternalTest("=", "needCheckNullVars", "ptr1 ptr2");
    }

    int func18()
    {
        Data1 *ptr1 = dynamic_cast<Data1*>(getData2());
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
};
