#include<iostream>
#include<cmath>
#define eps 0.01

using namespace std;

double f(double x)
{
    return  -x*(1/pow(2,x)+1/pow(4,x));
}

double fp(double x)
{
    double delta = pow(10,-4);

    return (f(x+delta)-f(x-delta))/(2*delta);
}

double falses(double a,double b){
    double c;
    do
    {
        c=a-fp(a)*(fp(a)-fp(b))/(a-b);
      
        if( c<a-sqrt(eps) || c>b+sqrt(eps) )
            c=(a+b)/2;
        if( fp(c) < 0 )
        {
            a=c;
        } else {
            b=c;
        }
    } while( abs( fp(c) ) >= eps );
  
    return c;
}

int main()
{
    double a = -7, b = 14;
  
    cout << falses(a,b);

    return 0;
}

