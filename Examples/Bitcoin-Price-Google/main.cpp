#include "Math.h"
#include "linear_reg.h"
#include <iostream>

int main()
{

	std::vector<float> X{122110,113137.5,117110,114052.5,96398,97440,96032,90616.35,94597.8}; // var indep
	std::vector<float> Y{48844,45255,46844,45621,48199,48720,48016,54919,57332}; // var dep

	float B1;
	float B0;

	std::vector<std::vector<float>> Z(10);
	Z[0] = X;
	Z[1] = Y;

	Linear_Regression <float,float> reg_cls;
	reg_cls.fit(Z);

	std::cout << std::endl;
	std::cout << "Est: \n b0 = { " << reg_cls.b0 << " } \
	\nb1 = { " << reg_cls.b1 <<" }" << std::endl;

	std::vector<float> predict;
	for(int i = 0; i < X.size(); i++)
		predict.push_back(reg_cls.predict(X[i]));
  	for(int i = 0; i < X.size(); i++)
   		std::cout << predict[i] << std::endl;
	return 0;

}
