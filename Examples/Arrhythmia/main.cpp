#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define sc_bpm 1.0e-1
#define sc_oxy 1.0e-3
#define e 2.71828

struct Aritmie {
  double b0,b1,b2;
  double err;
  double alfa = 0.01;

  Aritmie()
  {
    b0 = 0;
    b1 = 0;
    b2 = 0;
  }

  void regresie(vector<double> bpm, vector<double> oxy,vector<int> arit)
  {
    for(auto& x: bpm)
      x *= sc_bpm;
    for(auto& x: oxy)
      x *= sc_oxy;
    
    for(int i=0;i<100;i++)
    {
      for(int j=0;j<arit.size();j++)
      {
        double r = 1 / (1 + pow(e, -(b0 + b1*bpm[j] + b2*oxy[j])));
        err = arit[j] - r;
        b0 = b0 + alfa * err * r * (1-r);
        b1 = b1 + alfa * err * r * (1-r) * bpm[j];
        b2 = b2 + alfa * err * r * (1-r) * oxy[j];


      }
      
    }
    cout << "Parametrii optimi: " << endl;
    cout << "b0 : " << b0 << endl;
    cout << "b1 : " << b1 << endl;
    cout << "b2 : " << b2 << endl;
  }
};

int main() {
  
vector<double> bpm = {102, 100, 72, 124, 71, 65, 111, 118, 70, 69};
vector<double> oxy = {79, 85, 92, 86, 88, 96, 93, 95, 85, 95};

vector<int> arit = {1, 1, 0, 1, 0, 0, 1, 1, 0, 0};

Aritmie a;
a.regresie(bpm, oxy, arit);

cout << "Exemplu: " << endl;
double batai = 105*sc_bpm, oxigen = 92*sc_oxy;

cout << "Pentru " << batai/sc_bpm << "batai si " << oxigen/sc_oxy << "% nivel oxigen" << endl;
double aritmie = 1 / (1 + pow(e, -(a.b0 + a.b1 * batai + a.b2 * oxigen)));

if (aritmie > 0.5)
  cout << "Pacientul are aritmie" << endl;
else
  cout << "Pacientul nu are aritmie" << endl;

return 0;




}
