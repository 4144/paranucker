

class Test1;
class Test2;

class Test2
{
    int a;
    Test1 *ptr1;
};

class Test1
{
    Test2 *ptr;
    int a;
    float b;
};

void func()
{
    Test1 var1;
}
