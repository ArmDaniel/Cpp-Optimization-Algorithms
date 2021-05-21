# Apollo 13 - maximizarea importantei/valorii obiectelor ce se pastreaza, minimizand consumul total



## Introducere



Avand in vedere ca Apollo 13 trebuie sa aiba suficiente resurse pentru a face drumul de intoarcere, trebuie hotarat ce module raman in functiune, maximizand importanta
acestora , insa avand un consum de maxim 13A.

Abordarea problemei: metoda recursiva a.k.a. 'exhaustive search'

## Mod de implementare


```cpp
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
```

* prima conditie reprezinta cazul de baza, avut in vedere pentru a avea conditie de stop pentru metoda recursiva
* a doua conditie vizeaza: a) daca consumul este mai mare decat consumul maxim admis, solutia este respinsa din start; b) altfel , se alege valoarea maxima dintre 2 cazuri: daca modulul n este inclus sau nu

## Rezultate


Au fost obtinute urmatoarele rezultate in urma rularii algoritmului:

![Apollo13](https://github.com/Motanovici/Cpp-Optimization-Algorithms/blob/main/Examples/Apollo13/knapsack/img/results.png)

Importanta maxima a modulelor este 36, prin urmare s-au pastrat: sistemul de oxigen, giroscopul, calculatorul de bord, accelerometrul si becul de cabina.

1. OBS: o varianta alternativa a vizat folosirea algoritmului minimax, insa trebuie asigurat un numar par de elemente in listele de "importanta" si "consum", insa abordarea fiind tot recursiva, s-a ales "exhaustive search" pentru simplitatea codului si concizia sa

