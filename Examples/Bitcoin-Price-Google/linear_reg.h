#ifndef LINEAR_REG
#define LINEAR_REG

#include <iostream>
#include <vector>
#include <algorithm>
#include "Math.h"

template<typename T, typename M>
void estimate_coeff(std::vector<T> indep_var, std::vector<T> dep_var, M &B1, M &B0)
{
	M X_mean = alg_math::Math_Mean(indep_var);
	M Y_mean = alg_math::Math_Mean(dep_var);

	M SS_xy = 0;
	M SS_xx = 0;
	int n = indep_var.size();
	{
		std::vector<T> vtemp;
		vtemp = alg_math::vect_Multiply(indep_var,dep_var);
		SS_xx = std::accumulate(vtemp.begin(), vtemp.end(), 0);
		SS_xy = SS_xy - n * X_mean * Y_mean;

	}
	{
		std::vector<T> vtemp;
		vtemp = alg_math::vect_Multiply(indep_var, indep_var);
		SS_xx = std::accumulate(vtemp.begin(), vtemp.end(), 0);
		SS_xx = SS_xx - n * X_mean * X_mean;
	}

	std::cout<< "SS_xy : " << SS_xy <<std::endl;
    	std::cout<< "SS_xx : " << SS_xx <<std::endl;
    	std::cout<< "X_mean : " << X_mean <<std::endl;
    	std::cout<< "Y_mean : " << Y_mean <<std::endl;
    
	B1 = SS_xy / SS_xx;
	B0 = Y_mean - B1 * X_mean;


}

template<typename X, typename Z>
class Linear_Regression
{
public:
	X b0, b1;


	void fit(std::vector<std::vector<Z>> dataset)
	{
		estimate_coeff(dataset[0], dataset[1], b1, b0);
	}

	Z predict(const Z &test_data)
	{
		return b0 + (b1 * test_data);
	}
};
#endif
