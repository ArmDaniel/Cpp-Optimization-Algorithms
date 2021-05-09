#include <iostream>
#include <math.h>

using namespace std;

/* ---------------------------------------------- */

// To apply GC to Rosenbrock and Himmelblau, a non-linear variant must be developed

/* ---------------------------------------------- */

double Rosenbrock(double x, double y) 
{
    return (1 - x) * (1 - x) + 100 * (y - x * x) * (y - x * x);
}

void matr_vec(double A[2][2], double x[2], double r[2]) 
{
    r[0] = A[0][0] * x[0] + A[0][1] * x[1];
    r[1] = A[1][0] * x[0] + A[1][1] * x[1];
}

double vect_transXvect(double vec1[2], double vec2[2]) 
{
    double out = 0;
    for (int i = 0; i < 2; i++) {
        out = out + vec1[i] * vec2[i];
    }
    return out;
}

void vec_matr(double punct[2], double A[2][2], double sol[2]) 
{
    sol[0] = punct[0] * A[0][0] + punct[1] * A[1][0];
    sol[1] = punct[0] * A[0][1] + punct[1] * A[1][1];
}

double norma(double vect[2]) 
{
    double suma = 0;
    for (int i = 0; i < 2; i++) {
        suma = suma + vect[i] * vect[i];
    }
    return sqrt(suma);
}

void scale_add(double coef, double veca[2], double vecb[2], double out[2]) 
{
    for (int i = 0; i < 2; i++) {
        out[i] = veca[i] + coef * vecb[i];
    }
}

double vec_mat_vec(double vec1[2], double matr[2][2], double vec2[2]) 
{
    double sol[2];
    double out;
    vec_matr(vec1, matr, sol);
    out = vect_transXvect(sol, vec2);
    return out;
}

void sum_vectors(int n, double point[2], double step[2], double next[2]) 
{
    for (int i = 0; i < n; i++) {
        next[i] = point[i] + step[i];
    }
}

void a_scale(int n, double coef, double in[2], double out[2]) 
{
    int i;
    for (i = 0; i < n; i++)
        out[i] = coef * in[i];
}

double golden_search(double f(double, double), double dir[], double x[], double tol) 
{
    
	  double xnew[2];
    double gr = (1 + sqrt(5)) / 2;
    double step[2];
    double alphar = 1 / gr;
	
    a_scale(2, alphar, dir, step);
    sum_vectors(2, x, step, xnew);
	
    double fr = f(xnew[0], xnew[1]);
    double alphal = 1 / (gr * gr);
	
    a_scale(2, alphal, dir, step);
    sum_vectors(2, x, step, xnew);
	
    double fl = f(xnew[0], xnew[1]);
    double ngrad = norma(dir);
    double dist = (alphar - alphal);
	
    while (ngrad * dist > tol) 
	{
        dist = (alphar - alphal) / gr;
        if (fr > fl) 
		{
            alphar = alphal;
            fr = fl;
            alphal -= dist;
            a_scale(2, alphal, dir, step);
            sum_vectors(2, x, step, xnew);
            fl = f(xnew[0], xnew[1]);
        }
        else 
		{
            alphal = alphar;
            fl = fr;
            alphar += dist;
            a_scale(2, alphar, dir, step);
            sum_vectors(2, x, step, xnew);
            fr = f(xnew[0], xnew[1]);
        }
    }
    return (alphal + alphar) / 2;
}

void gradient(double f(double, double), double point[2], double grad[2], double tol) 
{
    double f0;
    double f1;
    double h;
    double eps = sqrt(tol);
    double x[2];
	
    a_scale(2, 1, point, x);
    f0 = f(x[0], x[1]);
	
    for (int i = 0; i < 2; i++) 
	{
        h = fabs(x[i]) * sqrt(eps) + 0.0000000000000001;
        x[i] += h;
        f1 = f(x[0], x[1]);
        x[i] -= h;
        grad[i] = (f1 - f0) / h;
    }
}

void nonLinear_GC(double f(double, double), double point[2], double tol, double n) 
{
    
    double r[2];
    double r1[2];
    double d[2];
    double lambda;
    bool found = false;
    double beta;
	
    gradient(f, point, r, tol);
	
    r[0] = (-1) * r[0];
    r[1] = (-1) * r[1];
    d[0] = r[0];
    d[1] = r[1];
	
    do 
	{
        lambda = golden_search(f, d, point, tol);
        scale_add(lambda, point, r, point);
		
        cout << "point 0 " << point[0] << " point 1 " << point[1] << "\n";
        gradient(f, point, r1, tol);
		
        r1[0] = (-1) * r1[0];
        r1[1] = (-1) * r1[1];
		
        if (norma(r1) < tol) 
		{
            found = true;
        }
        else 
		{
            beta = (norma(r1) * norma(r1)) * (1 / (norma(r) * norma(r)));
            scale_add(beta, r1, d, d);
        }
        n--;
        r[0] = r1[0];
        r[1] = r1[1];
		
    } while ((found == false) && (n > 0));
}

int main() 
{
  double tol = 0.00001;
    
  double start_point_R[] = { 0, 0 };
  double start_point_H[] = { 1, 5 };
	
	cout << " Rosenbrock " << endl;
  nonLinear_GC(Rosenbrock, start_point_R, tol, 1000);
	
	cout << "------------------------" << endl;
	cout << " Himmelblau " << endl;
	
	nonLinear_GC(Himmelblau, start_point_H, tol, 1000);
    
}
