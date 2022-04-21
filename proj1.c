/*
examples
a b n estimate
-1 1 1883 1.178979838
0 10 2028 0.489888070
-1000 1000 18861 0.999796418
10 15 1515 0.016860599
0.1 0.2 138 0.096211811
*/

#include<stdio.h>
#include<math.h>

#define PI 3.141592654
//function
double I(double a,double b);
double f(double x);
//

/******************************************/
int main()
{
    double a, b;
    
    printf("Enter a value for a:");
    scanf("%lf", &a);
    printf("Enter a value for b:");
    scanf("%lf", &b);
    
    printf("The integral result is %.9lf", I(a, b));

    getchar();
    getchar();
    return 0;
}

/*************************************************/

double I(double a,double b)
{
    unsigned int n = 10;//n原来奇数有问题是因为没考虑f(0)=1
    double sum = 0;
    double last_sum = 0;
    double err = 1;
    double rec = (b - a) / n;
    printf("Integral evaluation\n");
    while (n < 100000)
    {
        rec = (b - a) / n;
        for (int i = 1; i <= n; i++)
        {
            if (!(a + (i - 0.5) * rec)) // f(0) = 1;
            {
                sum += rec;
            }
            else
                sum += f(a + (i - 0.5) * rec) * rec;
        }
        
        //误差err<1e-10停
        
        if (n > 10)
        {
            //取err绝对值
            if (last_sum - sum < 0)
            {
                err = -1 * (last_sum - sum);
            }
            else
                err = last_sum - sum;
        }
        last_sum = sum;
        
        if (err < 1e-10)
        {
            printf("%d: %.9lf %.6e\n", n, sum, err);
            break;
        }
        

        printf("%d: %.9lf %.6e\n", n, sum, err);
        sum = 0;
        n++;
        
    }
    return sum;
}

double f(double x)
{ 
    return (sin(PI * x) / PI / x);
}