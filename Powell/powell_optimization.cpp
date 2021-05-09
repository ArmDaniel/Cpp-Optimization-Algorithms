#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>

#define EPS 0.001
#define STEP 0.5

using namespace std;

// define our function using struct, easier manipulation and passing for argument

struct func {
	double operator()(double x, double y) const{
		return pow(x,3) + pow(y,3) - sin(x*y);
	}
};

class Powell {
public:
  
  // initialize starting point
	Powell(double x, double y):x0{x},y0{y}
  {
		iter = 0;
	}
  // function to apply algorithm
	tuple<double,double> runPowell(func f, double eps);
	int get_iter() const { return iter; }

private:
	double x0,y0,xk,yk,delta;
	double xsol, ysol;
	int iter;

};

// declare goldenSearch prototype
double goldenSearch(double a, double b, double y, int c,func f);
tuple<double,double> Powell::runPowell(func f, double eps){

	xk = x0;
	yk = y0;

	for(int i = 0; i < 150; i ++)
	{

		delta = sqrt(pow(abs(xk-xsol),2)+ pow(abs(yk-ysol),2));
		if(delta < eps)
			break;

		xsol = goldenSearch(xk-STEP,xk + STEP,yk,0,f);
		ysol = goldenSearch(yk-STEP,yk + STEP,xk,1,f);

		if(f(xsol,yk) < f(xk,ysol))
		{
			xk = xsol;
			iter++;
		}
		else
			yk = ysol;

	}

	return {xk,yk};


}

double goldenSearch(double a, double b, double y, int coord, func f)
{
	double c,d;

	switch(coord){
		case 0:
			while(abs(f(a,y)-f(b,y)) >= EPS)
			{
				c = b - (0.618*(b-a));
				d = a + (0.618*(b-a));
				if(f(c,y)<f(d,y))
					b = d;
				else
					a = c;
			}
			return c;
			break;
		case 1:
			while(abs(f(y,a)-f(y,b)) >= EPS)
			{
				c = b - (0.618*(b-a));
				d = a + (0.618*(b-a));
				if(f(y,c)<f(y,d))
					b = d;
				else
					a = c;
			}
			break;
		
	}
	return c;


}

int main()
{

	Powell p(15,25);
  
	auto [min1, min2] = p.runPowell(func(),EPS);
  
	cout << "Min: " << min1 << " " << min2 << endl;
	cout << "Iter: " << p.get_iter();

	return 0;
}
