# Pretul Bitcoin raportat la numarul de cautari pe Google si la indicele NASDAQ

---

## Introducere

Tema a avut in vedere analiza pretului BTC atunci cand il raportam la numarul de cautari pe Google sau la indicele NASDAQ. Mai precis, am avut de prezis pretul BTC avand in vedere evolutia sa intr-un timp dat ( baza de date a fost oferita ). In prealabil, a fost necesara plotarea a 2 grafice, pentru a stabili daca intre seturile de date oferite exista o relatie liniara sau nu. Pentru a realiza acest lucru, trebuie sa ne asiguram ca datele, plotate una in functie de cealalta, rezida pe o linie ce respecta ecuatia:

y = a * x + b,

Unde y reprezinta valoarea variabilei dependente(pretul bitcoin) , iar x este valoarea variabilei independente(nr cautari Google/indicele NASDAQ).

Setul de date fiind oferit, graficul pretului bitcoin - nr cautari Google arata astfel:

![BTC-Google](https://github.com/Motanovici/Cpp-Optimization-Algorithms/blob/main/Examples/Bitcoin-Price-Google/img/bitcoingoogle.JPG)

Observam ca setul de date respecta criteriul de mai sus si se afla intr-o relatie liniara.

Acelasi lucru poate fi spus si despre pretul BTC raportat la indicele NASDAQ:

![BTC-NASDAQ](https://github.com/Motanovici/Cpp-Optimization-Algorithms/blob/main/Examples/Bitcoin-Price-Google/img/bitcoinnasdaq.JPG)

## Mod de implementare

Pentru a putea prezice valoarea unei variabile in functie de evolutia celeilalte, ne vom folosi de metoda regresiei liniare.

Programul este alcatuit din 3 fisiere principale:

* Math.h : fisier header ce se ocupa de operatiile matematice asociate vectorilor ( inmultire, transpusa etc. ), precum si statistica ( medie, probabilitati )
* linear_reg.h : fisier header ce implementeaza clasa asociata regresiei lineare, cat si functia ce se ocupa de estimarea coeficientilor asociati acesteia
* main.cpp : fisierul main ofera un exemplu de aplicare a regresiei liniare, constand in fitarea datelor si afisarea prezicerii conform acestor calcule

Exemple Cod:

1. Math.h ( defineste namespace-ul alg_math, ce contine functii matematice utile pentru multiplicare vectori, calcul medie etc. )

```cpp
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
```
2. linear_reg.h ( functia Linear_Regression ce contine cele 2 functii esentiale asociate acesteia -> fit: potrivirea datelor conform coeficientilor; predict: prezicerea acestora pe dreapta de regresie )

```cpp
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
```
3. main.cpp ( exemplu din setul de date pe care aplicam regresia liniara )

```cpp
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
```

## Rezultate

In urma rularii programului, am obtinut urmatoarele rezultate ( IDE: repl.it )

![Rezultate](https://github.com/Motanovici/Cpp-Optimization-Algorithms/blob/main/Examples/Bitcoin-Price-Google/img/results.png)
