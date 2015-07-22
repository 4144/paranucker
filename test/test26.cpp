#include <string>
#include <vector>

struct Data1;

struct Data1
{
    Data1()
    {
    }

    Data1(Data1 *ptr0) :
        ptrval(ptr0)
    {
    }

    int val;
    Data1 *ptrval;
    int arr[3];
    std::string str1;

    int ftest1()
    {
        return 1;
    }

    static int ftest2(Data1 *ptr0)
    {
        return 1;
    }
};

struct Data2
{
    virtual ~Data2()
    {
    }
};

int k;

class Object1
{
    void func1(Data1 *const ptr1)
    {
        if (ptr1)
        {
            if (ptr1 && k == 1)
                return;
        }
    }

    void func2(Data1 *const ptr1)
    {
        if (!ptr1)
        {
            if (!ptr1 && k == 1)
                return;
        }
    }

    void func3(Data1 *const ptr1)
    {
        if (!ptr1)
        {
            return;
        }
        delete ptr1;
    }

    void func4(Data1 *const ptr1)
    {
        if (ptr1)
        {
            return;
        }
        delete ptr1;
    }

    static void func5(Data2 *const ptr1)
    {
        if (!ptr1)
            return;
        // here false report. some how need add ignore because delete here
        delete ptr1;
    }

    void func6(Data1 *const ptr1)
    {
        if (!ptr1 || k == 3)
        {
            if (!ptr1 && k == 1)
                k = 10;
            if (ptr1 && k == 2)
                k = 20;
            if (!ptr1 || k == 1)
                k = 30;
            if (ptr1 || k == 2)
                k = 40;
        }
        else
        {
            if (!ptr1 && k == 4)
                k = 50;
            if (ptr1 && k == 5)
                k = 60;
            if (!ptr1 || k == 4)
                k = 70;
            if (ptr1 || k == 5)
                k = 80;
        }
    }

    void func7(Data1 *const ptr1)
    {
        if (ptr1 || k == 3)
        {
            if (ptr1 && k == 1)
                k = 10;
            if (!ptr1 && k == 2)
                k = 20;
            if (ptr1 || k == 1)
                k = 30;
            if (!ptr1 || k == 2)
                k = 40;
        }
        else
        {
            if (ptr1 && k == 4)
                k = 50;
            if (!ptr1 && k == 5)
                k = 60;
            if (ptr1 || k == 4)
                k = 70;
            if (!ptr1 || k == 5)
                k = 80;
        }
    }

    void func8(Data1 *const ptr1)
    {
        if (!ptr1 && k == 3)
        {
            if (!ptr1 || k == 1)
                k = 10;
            if (ptr1 || k == 2)
                k = 20;
            if (!ptr1 && k == 3)
                k = 30;
            if (ptr1 && k == 4)
                k = 40;
        }
        else
        {
            if (!ptr1 || k == 5)
                k = 50;
            if (ptr1 || k == 6)
                k = 60;
            if (!ptr1 && k == 7)
                k = 70;
            if (ptr1 && k == 8)
                k = 80;
        }
    }

    void func9(Data1 *const ptr1)
    {
        if (ptr1 && k == 3)
        {
            if (ptr1 || k == 1)
                k = 10;
            if (!ptr1 || k == 2)
                k = 20;
            if (ptr1 && k == 3)
                k = 30;
            if (!ptr1 && k == 4)
                k = 40;
        }
        else
        {
            if (ptr1 || k == 5)
                k = 50;
            if (!ptr1 || k == 6)
                k = 60;
            if (ptr1 && k == 7)
                k = 70;
            if (!ptr1 && k == 8)
                k = 80;
        }
    }

    void func10(Data1 *const ptr1)
    {
        if (ptr1)
        {
            if (ptr1)
                ptr1->val = 100;
        }
    }

    void func11(Data1 *const ptr1)
    {
        if (ptr1 && k == 10)
        {
            if (ptr1)
                ptr1->val = 100;
        }
    }

    void func12(Data1 *const ptr1)
    {
        if (ptr1 || k == 10)
        {
            if (ptr1)
                ptr1->val = 100;
        }
    }

    void func13(Data1 *const ptr1)
    {
        if (ptr1 && k == 10)
        {
            return;
        }
        else
        {
            if (ptr1)
                ptr1->val = 100;
        }
    }

    void func14(Data1 *const ptr1)
    {
        if (ptr1 || k == 10)
        {
            return;
        }
        else
        {
            if (ptr1)
                ptr1->val = 100;
        }
    }
};
