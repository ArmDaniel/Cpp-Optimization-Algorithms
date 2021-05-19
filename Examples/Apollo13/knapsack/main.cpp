#include <bits/stdc++.h>

using namespace std;

// Abordare conform problemei Knapsack
// Aflam scorul maxim de importanta - alegem modulele corespunzatoare

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int apolloInventar(int cons, int consum[], int importanta[], int n)
{
  if( n == 0 || cons == 0)
    return 0;
  
  if(consum[n-1] > cons)
    return apolloInventar(cons, consum, importanta,n-1);
  else
    return max(importanta[n-1] + 
    apolloInventar(cons - consum[n-1],consum, importanta,n-1),
    apolloInventar(cons,consum,importanta,n-1));
  
  
}

int main() {

  int importanta[] = {8,2,2,7,10,4,9,8,6};
  int consum[] = {3,1,5,2,4,3,3,4,2};
  string module[] = {"calculator bord","bec cabina","incalzire scaune","accelerometru","sistem oxigen","dezumidificator","giroscop","control orientare","sistem navigatie"};

  int cons = 13;

  int n = sizeof(importanta)/sizeof(importanta[0]);
  cout << "Importanta maxima: ";
  cout << apolloInventar(cons,consum,importanta,n) << endl;

  cout << "Se pastreaza: " << endl;
  cout << module[4] << ", " << module[6] << ", " << module[0] << ", " << module[3] << ", " << module[1] << endl;
  
  return 0;

}
