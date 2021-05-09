#include <iostream>
#include <cmath>

using namespace std;

// example function

double f(double x)
{
    return 1/x*exp(x);
}

// fib computing function

double Fibonacci(double n)
{
    double n0 = 1, n1 = 1, n2;
    
    
    if(n == 0 || n == 1)
        return 1;
    for(int i = 2; i <= n; i++)
    {
        n2 = n0 + n1;
        n0 = n1;
        n1 = n2;
    }
    return n2;
}


int main()
{
    int n = 35;
    double a = 0, b = 100;
    double L0 = b - a;
    
    double c,d;
    for(int i = 2; i < n; i++)
    {
        c = a + (Fibonacci(n-i)/Fibonacci(n))*L0;
        d = b - (Fibonacci(n-i)/Fibonacci(n))*L0;
        
        if(f(c) < f(d))
            b = d;
        else
            a = c;
    }
    
    cout << c;
    
    // output : 1
    
    return 0;
}
