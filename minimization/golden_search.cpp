#include <iostream>
#include <cmath>

#define EPSILON 0.0000000000007
#define e 2.7182

using namespace std;

// example function

double f(double x)
{
    return 1/x*pow(e,x);
}

void GoldenSearch()
{
    double a, b, c, d;
    
    a = 0;
    b = 1000;

    int pasi = 0;
    
    

    do
    {
        c = b - (0.618)*(b - a);
    	d = a + (0.618)*(b - a);
        if(f(c) <= f(d))
            b = d;
        else
            a = c;
            
        c = b - (0.618)*(b - a);
        d = a + (0.618)*(b - a);
        
        pasi++;

    } while(abs(f(c) - f(d)) > EPSILON);
    
    cout << "Pasi: " << pasi << "; " << c;
}


int main()
{
  
    GoldenSearch();
    
    
    return 0;
}
