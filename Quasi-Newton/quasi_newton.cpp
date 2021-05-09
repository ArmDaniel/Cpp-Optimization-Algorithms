#include <iostream>
#include <math.h>

using namespace std;

/* ---------------------------------- */

// QUASI-NEWTON METHOD

/* 
TODO:
    * translate terms to English
    * format and style code
    * add explanations, code too verbose
*/

/* ---------------------------------- */

double f1_paraboloid(double x, double y) 
{
	return x*x + y*y - x*y - x - y; 
}

double f1_paraboloid_Dx(double x, double y) 
{
	return 2*x - y - 1; 
}

double f1_paraboloid_Dy(double x, double y) 
{
	return -x + 2*y - 1; 
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

void adunare_vectori(int n, double punct[2], double pas[2], double next[2]) 
{
    for (int i = 0; i < n; i++) {
        next[i] = punct[i] + pas[i];
    }
}

void a_scale(int n, double coef, double in[2], double out[2]) 
{
    int i;
    for (i = 0; i < n; i++)
        out[i] = coef * in[i];
}

void adunare_vectori(int n, double punct[2],double pas[2],double next[2])
{
	int i=0;
	for(i=0;i<n;i++){
		next[i]=punct[i]+pas[i];
	}
}

void adunare_matrici(double coef,double matr1[2][2],double matr2[2][2],double matr_out[2][2])
{
	for(int i=0;i<2;i++)
	  for(int j=0;j<2;j++)
	    matr_out[i][j]=matr1[i][j]+coef*matr2[i][j];
}

void inmultire_matrici(double matr1[2][2],double matr2[2][2],double matr_out[2][2])
{
	for(int i=0;i<2;i++)
	   for(int j=0;j<2;j++)
	     matr_out[i][j]=matr1[i][0]*matr2[0][j]+matr1[i][1]*matr2[1][j];
}

void scalarXmatrice(double scalar,double matr_in[2][2],double matr_out[2][2])
{
	int i=0;
	int j=0;
	  for( i=0;i<2;i++)
		  for( j=0;j<2;j++)
			  matr_out[i][j]=scalar*matr_in[i][j];
}

double gold_search(double f(double,double), double dir[], double x[], double tol)
{
	
		double xnew[2];
		double gr=(1+sqrt(5))/2;
		double step[2];
		double alphar =  1/gr;
		
		a_scale(2, alphar, dir, step);
		adunare_vectori(2,x,step,xnew);
		
		double fr = f(xnew[0],xnew[1]);
		double alphal =  1/(gr*gr);
		
		a_scale(2, alphal, dir, step);
		adunare_vectori(2,x,step,xnew);
		
		double fl = f(xnew[0],xnew[1]);
		double ngrad = norma(dir);
		double dist = (alphar-alphal);
		
		while(ngrad*dist>tol)
		{
			dist = (alphar-alphal)/gr;
			if(fr > fl)
			{
				alphar = alphal;
				fr = fl;
				alphal -= dist;
				a_scale(2, alphal, dir, step);
				adunare_vectori(2,x,step,xnew);
				fl = f(xnew[0],xnew[1]);
			}
			else
			{
				alphal = alphar;
				fl = fr;
				alphar += dist;
				a_scale(2, alphar, dir,step);
				adunare_vectori(2,x,step,xnew);
				fr = f(xnew[0],xnew[1]);
			}
		}
		return (alphal+alphar)/2;
}

void gradient(double f(double,double),double punct[2],double grad[2],double tol)
{
	double h;
	double eps=sqrt(tol);
	double f0;
	double f1;
	double x[2];
	
	a_scale(2,1,punct,x);
	f0=f(x[0],x[1]);
	
	for(int i=0;i<2;i++)
	{
	    h=fabs(x[i])*sqrt(eps)+0.00000000001;

		x[i]+=h;
		f1=f(x[0],x[1]);
		x[i]-=h;
		grad[i]=(f1-f0)/h;
	}
}

void vectXvect_trans(double vec1[2],double vec2[2],double matr[2][2])
{
	for(int i=0;i<2;i++)
	  for(int j=0;j<2;j++)
	     matr[i][j]=vec1[i]*vec2[j];
}



void Quasi_Newton(
	double f(double,double),
	double punctcurent[2],
	double tol,
	double n)
{
    
	fprintf("%f,%f\n",punctcurent[0],punctcurent[1]);
	
    double gradpred[2];
    double gradcurent[2];
    double B[2][2]={1,0,0,1};
    double B1[2][2];
    double B2[2][2];
    double k;
    double aflat=false;
    double s[2];
    double alfa;
    double q[2];
    double p[2];
    double punctpred[2];
	
    gradient(f,punctcurent,gradpred,tol);
    a_scale(2,1,punctcurent,punctpred);
	
    while((aflat==false)&&(n>0))
	{
        matr_vec(B,gradpred,s);
        s[0]=(-1)*s[0];
        s[1]=(-1)*s[1];
		
        alfa=gold_search(f,s,punctpred,tol);
        scale_add(alfa,punctpred,s,punctcurent);
		
        fprintf("%f,%f\n",punctcurent[0],punctcurent[1]);
		
        gradient(f,punctcurent,gradcurent,tol);
        scale_add(-1,gradcurent,gradpred,q);
        scale_add(-1,punctcurent,punctpred,p);
		
        k=vect_transXvect(p,q);
        vectXvect_trans(p,p,B1);
        scalarXmatrice(1/k,B1,B1);
        adunare_matrici(1,B,B1,B);
        k=vec_mat_vec(q,B,q);
		
        double r[2];
		
        matr_vec(B,q,r);
        vectXvect_trans(r,q,B2);
        inmultire_matrici(B2,B,B2);
        scalarXmatrice(1/k,B2,B2);
        adunare_matrici(-1,B,B2,B);
		
        if(norma(gradcurent)<tol)
		{
            aflat=true;
        }
		else
		{
			a_scale(2,1,gradcurent,gradpred);
			a_scale(2,1,punctcurent,punctpred);
		}
        n--;
    }
}

int main()
{
	
	int n = 2;
	double tol = 1e-3;
	double x_start[2] = {9, 7};
	
	Quasi_Newton(
				f1_paraboloid,
				x_start,
				tol,
				n
				);
	
	return 0;
}
