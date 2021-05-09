#include <iostream>
#include <cmath>

#define EPSILON 0.01

using namespace std;

// example function with first and second order derivatives

double f(double x)
{
    return -x*(1/pow(2,x)+1/pow(4,x));
}

double fderiv1(double x)
{
    double delta = pow(10,-4);
    return (f(x+delta)-f(x-delta))/(2*delta);
}

double fderiv2(double x)
{
    double delta = pow(10,-4);
    return (f(x+delta)-2*f(x)+f(x-delta))/pow(delta,2);
}



void Newton(double x)
{
    double h = fderiv1(x) / fderiv2(x);
    
    while(abs(fderiv1(x)) >= EPSILON)
    {
        h = fderiv1(x)/fderiv2(x);
        
        x -= h;
    }
    
    cout << x << endl;
    
}


int main()
{
    
    //  initial guess value
    
    double x0 = 0;
    Newton(x0);
    
    return 0;
}
