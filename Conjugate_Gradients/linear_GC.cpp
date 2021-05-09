#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

using vec = vector<double>;
using matrix = vector<vec>;

const double near_zero = 1.0e-10;

// prototypes

void print( string title, const vec &V );
void print( string title, const matrix &A );

vec matriceXvector( const matrix &A, const vec &V);
vec vectorCombination( double a, const vec &U, double b, const vec &V );
vec conjugate_gradients( const matrix &A, const vec &B);

double innerProd( const vec &U, const vec &V );
double vectorNorm( const vec &V );

int main()
{
	

	matrix A = { { 2, -1 }, { -1, 2 } };
	vec B = { 1, 1 };

	vec X = conjugate_gradients( A, B );

	print("\nA:", A);
	print("\nB:", B);
	cout << "Solution: " << endl;
	print("\nX:", X);

	return 0;
}


void print( string title, const vec &V )
{
	cout << title << '\n';

	int n = V.size();
	for( int i = 0; i < n; i++ )
	{
		double x = V[i];
		if ( abs(x) < near_zero )
			x = 0.0;
		cout << x << '\t';
	}
	cout << '\n';
}

void print ( string title, const matrix &A )
{
	cout << title << '\n';

	int m = A.size(), n = A[0].size();
	for ( int i = 0; i < m; i++ )
	{
		for ( int j = 0; j < n; j++ )
		{
			double x = A[i][j];
			if ( abs(x) < near_zero )
				x = 0.0;
			cout << x << '\t';
		}
		cout << '\n';
	}
}

double innerProd( const vec &U, const vec &V )
{
	return inner_product( U.begin(), U.end(), V.begin(), 0.0 );
}

double vectorNorm( const vec &V )
{
	return sqrt( innerProd( V, V ) );
}


vec matriceXvector( const matrix &A, const vec &V )
{
	int n = A.size();
	vec C(n);
	for ( int i = 0; i < n; i++ )
		C[i] = innerProd( A[i], V);

	return C;
}

vec vectorCombination( double a, const vec &U, double b, const vec &V )
{
	int n = U.size();
	vec Y(n);
	for ( int j = 0; j < n; j++ )
		Y[j] = a * U[j] + b * V[j];

	return Y;
}

vec conjugate_gradients( const matrix &A, const vec &B )
{
	double tolerance = 1.0e-10;

	int n = A.size();

	vec X( n, 0.0 );

	vec R = B;
	vec P = R;
	int k = 0;

	while ( k < n )
	{
		vec Rvechi = R; // old residual
		vec AP = matriceXvector(A, P);

		double alfa = innerProd( R, R ) / max(
											innerProd( P, AP ), near_zero);
		// next estimate
		X = vectorCombination( 1.0, X, alfa, P );
		// residual
		R = vectorCombination( 1.0, R, -alfa, AP);

		// convergence test
		if ( vectorNorm ( R ) < tolerance )
			break;

		double beta = innerProd( R, R) / max(
											innerProd( Rvechi, Rvechi ), near_zero);
		// next gradient
		P = vectorCombination( 1.0, R, beta, P );
		k++;
	}

	return X;
}
