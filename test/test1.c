#define MAX123 10
int fun1(const int x,int*** y);
int c=1;

void func3(int *ptr, char *ptr2) __attribute__((nonnull (1, 2))) __attribute__ ((noreturn));

void func3(int *ptr, char *ptr2)
{
    *ptr = 10;
    *ptr2 = 20;
    while(true);
}

int main()
{
	fun1(1,(int***)2);
        char k, k2;
        func3(0, &k);
	return 1;
}
void fun(int a , int b)
{
	if (a==0)
		a=(a+b)*c;
	else
		b=1;

}
int fun1(const int x,int*** y)
{
	int a=0;int b=1;
	c=b;
	fun(0,1);
	if(a==0)
		return a+b;
	else return MAX123;
}
long fun2(const char* zz) { return (long)zz; }
