#include <bits/stdc++.h>

using namespace std;


int minimax(int depth, int nodeIdx, bool isMax, int scor[], int h)
{
  if(depth == h)
    return scor[nodeIdx];

  if(isMax)
    return max(minimax(depth+1, nodeIdx*2, false, scor, h), minimax(depth+1, nodeIdx*2 + 1, false, scor, h));
  else
    return min(minimax(depth+1,nodeIdx*2,true,scor,h), minimax(depth+1, nodeIdx*2+1, true, scor, h));

}

int log2(int n)
{
  return (n==1)? 0 : 1 + log2(n/2);
}

int get_min(int list[])
{
  int min = 99999;
  int sz = sizeof(list)/sizeof(list[0]);
  for(int i=0;i<sz;i++)
  {
    if(min > list[i])
      min = list[i];
  }
  return min;
}

int* importanta(int scor[], map<int,int> ic, int h)
{
  int sz = sizeof(scor)/sizeof(scor[0]);

  if(sz % 2 == 0)
  {
    minimax(0,0,true,scor,h);
  }
  else
  {
    // gasire minim
    // eliminare pereche
    // verificare consum
  }
}

int main() {
  

  int scor[] = {8,2,7,10,4,9,8,6};
  int consum[] = {3,1,2,4,3,3,4,2};
  map<int, int> ic; // mapeaza importanta la consum

  int n = sizeof(scor)/sizeof(scor[0]);

  int h = log2(n);

  int optim = minimax(0,0, true, scor, h);
  // se repeta prin functia "importanta"
  cout << "Valoarea optima este: " << optim << endl;

  return 0;


}
