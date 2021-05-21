# Optimizarea coeficientilor dintr-o regresie logistica pe baza unui set de date ( batai pe minut, nivel oxigen, aritmie da/nu )


## Introducere

Metoda regresiei logistice se foloseste de regula in probleme de clasificare, cum este si cazul problemei de fata.
Problema a vizat optimizarea coeficientilor b0, b1, b2 astfel incat procentajul predictiilor corecte sa fie maxim.

Valoarea de iesire respecta ecuatia: b0 + b1 * x1 + b2 * x2

Setul de date este oferit

## Mod de implementare

```cpp
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
```

S-a avut in primul rand vedere de scalarea setului de date - a numarului de batai pe minut si a nivelului de oxigen. Initial coeficientii au fost setati la 0 si optimizati
in functia "regresie", prin calculul erorii predictiilor si ajustarea conforma a acestora. S-a ales un numar de iteratii standard: 100.

In functia main se ofera valoarea optima a coeficientilor, cat si un exemplu de predictie al aritmiei.

```cpp
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
```

## Rezultate

![Aritmie](https://github.com/Motanovici/Cpp-Optimization-Algorithms/blob/main/Examples/Arrhythmia/img/results.png)
