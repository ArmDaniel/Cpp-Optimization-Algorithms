#ifndef MATH_H
#define MATH_H
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

namespace alg_math 
{ 
    template <typename T> 
    T Math_Mean(std::vector<T>);
    template <typename M>
    double Math_Var (std::vector<M> &);
    double calc_prob(double value,double mean,double stdev);
    template <typename T> 
    std::vector< std::vector<T>> vect_Transpose ( std::vector<std::vector<T>> &input_Vector);
    template <typename T> 
    std::vector< T> vect_Multiply ( std::vector<T>& input_Vector1, std::vector<T>& input_Vector2);
} 

template <typename T> 
T alg_math::Math_Mean (std::vector<T> Data)
{
    T mean = std::accumulate(std::begin(Data), std::end(Data), 0.0) / Data.size();
    return mean;
}

template <typename M> 
double alg_math::Math_Var (std::vector<M> &Data)
{
    M mean = std::accumulate(std::begin(Data), std::end(Data), 0.0) / Data.size();
    
    double accum = 0.0;
    std::for_each (std::begin(Data), std::end(Data), [&](const double d) {
    accum += (d - mean) * (d - mean);
    });

double stdev = sqrt(accum / (Data.size()-1));
    
    
    
    return stdev;
}
template <typename T> 
std::vector< std::vector<T>> alg_math::vect_Transpose ( std::vector<std::vector<T>>& input_Vector)
{
   if(input_Vector.size() > 0)
   {
    std::vector< std::vector<T> > out_Vector(input_Vector[0].size(), std::vector<T>(input_Vector.size()));

    for(int i=0;i<input_Vector.size(); i++) {   
    for (int j=0;j<input_Vector[i].size(); j++){
    out_Vector[j][i] = input_Vector [i][j];
            
	   }
   }
    return out_Vector;

   }
   return input_Vector;
}
template <typename T> 
std::vector<T> alg_math::vect_Multiply ( std::vector<T>& input_Vector1, std::vector<T>& input_Vector2)
{
   if(input_Vector1.size() == input_Vector2.size() && input_Vector1.size() !=0 )
   {
    std::vector< T > out_Vector(input_Vector1.size());

    for(int i=0;i<input_Vector1.size(); i++) { 
        out_Vector[i] = input_Vector1 [i] * input_Vector2 [i] ;
	   }
       return out_Vector;
   }
   return input_Vector1;
}
#endif
