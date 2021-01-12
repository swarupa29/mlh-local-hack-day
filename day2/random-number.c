
//generator  uses linear equation
#include<stdio.h>
long long rand_gen1();
long long rand_gen2();

long long a=39268791;
long long b=796837465820;
long long x0=8;
long long m=17895;
long long m2=791;
int main()
{
    int i;
    for(i=0;i<19;i++)
    {
        printf(" linear random number: %lli \n",rand_gen1());
        printf(" quadratic random number: %lli \n",rand_gen2());
    }
}
long long rand_gen1()
{
    long long x1=(a*x0+b)%m;
    x0=x1/2;
    return x1;
}


