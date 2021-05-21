# Optimizarea coeficientilor unui filtru astfel incat acesta sa fie liniar si invariant in timp ( SLIT )


## Introducere


Pentru rezolvarea problemei am ales folosirea unui algoritm genetic, acesta fiind foarte eficient in problemele de optimizare. Un algoritm genetic consta intr-un
"pool" de candidati ( gene ) ce evolueaza conform unui criteriu de fitness si doresc atingerea unui scop ( in cazul problemei de fata, diferenta dintre semnalul de iesire
si intrare sa fie cat mai aproape de 0 ). 

Pasii principali au constat in definirea setului de candidati si a "target-ului", combinarea genelor si aplicarea functiei de fitness pana se ajunge la un rezultat satisfacator.

## Mod de implementare ( + comentarii cod )

```cpp
using vec = vector<double>;

#define POPULATION_SIZE 100
#define pi 3.1415926
#define toleranta 0.1

/* 
Initializam random, unde target-ul reprezinta un set de coeficienti
pentru care sistemul este SLIT;
Ne dorim sa atingem aceasta stare
Algoritm:
* Functia de fitness va calcula diferenta dintre iesire si intrare,
avand in vedere o toleranta ( aproximativ aproape de 0)
* Fitness-ul va creste cat timp diferenta este mai mare decat toleranta
data
*/

// Gene valide - coeficienti
const vec gene = {2.0, 1.02, -0.25, 1.0, 1.1, 0.67, 0.25, -0.37, 2.2, 1.56, 0.23, 1.67, -0.98, -2.06, -2.0, 1.31};
const vec target = {1.0, 2.0, 1.0, 1.0, 0.25, -0.37};

double input_sig(int n)
{
  double x = 2 * cos(2*pi*0.1*n) - 3 * cos(2*pi*0.4*n);
  return x;
}

int random_num(int start, int end)
{
  int range = (end-start) + 1;
  int rand_int = start + (rand()%range);
  return rand_int;
}

double mutated_genes()
{
  int len = gene.size();
  int r = random_num(0,len-1);
  return gene[r];
}

vec create_chromo()
{
  int len = target.size();
  vec chromo;
  for(int i=0;i<len;i++)
    chromo.push_back(mutated_genes());
  return chromo;
}
```

In codul de mai sus au fost definite functiile: semnal la intrare, random_num (  ofera random un numar intr-un range dat ), mutated_genes ( returnarea unui element random din
setul de gene ), create_chromo ( "crearea cromozomilor", combinatii de gene in vederea atingerii "target-ului" ).

```cpp
class Individ
{
public:
  vec chromo;
  double fitness;
  Individ(vec chromo);
  Individ mate(Individ parinte2);
  double cal_fitness();
};

...

double Individ::cal_fitness()
{
  int len = target.size();
  int r = random_num(0,gene.size()-1);
  int n = 40;
  double y = 0;
  double fitness = 0;

  for(int i=0;i<6;i++)
  {
    y += gene[r]*input_sig(n-i);
    
    if (y - input_sig(n) > toleranta)
      fitness += 1.0;
    
  }
  
  return fitness;
};
```
S-a definit clasa Individ cu functiile necesare ( mate - de combinare, cal_fitness - calculul gradului de fitness si ajustarea coeficientilor pe masura ). 
Functia ce calcula gradul de fitness implementeaza si ajustarea parametrilor, conform criteriului specificat la inceput: ca diferenta dintre semnalul la iesire si intrare
sa fie cat mai aproape de 0.

In codul ce urmeaza este prezentata aplicarea notiunilor de mai sus, conform principiului de "elitism" - doar 10% din candidati trec mai departe, iar 50% din cei mai
"fit" vor produce alte solutii "copil".

```cpp
 int generation = 0;
  vector<Individ> population;
  bool found = false;

  for(int i = 0 ;i < POPULATION_SIZE; i++)
  {
    vec chromo = create_chromo();
    population.push_back(Individ(chromo));
  }

  while(!found)
  {
    sort(population.begin(), population.end());

    if(population[0].fitness <= 0.0 || generation == 10)
    {
      found = true;
      break;
    }
    vector<Individ> new_generation;

    // elitism - doar 10% trec mai departe

    int s = (10*POPULATION_SIZE)/100;
    for(int i = 0; i<s;i++)
      new_generation.push_back(population[i]);

    // din 50% ai celor mai "fit", indivizii se vor combina pentru a produce copii
    s = (90*POPULATION_SIZE)/100;

    for(int i=0;i<s;i++)
    {
      int len = population.size();
      int r = random_num(0,50);
      Individ parinte1 = population[r];

      r = random_num(0, 50);
      Individ parinte2 = population[r];
      Individ copil = parinte1.mate(parinte2);
      new_generation.push_back(copil);
    }
    population = new_generation;
    cout << "Generatia: " << generation << "\t";
    cout << "Parametrii: " << endl;
    for(int i=0;i<6;i++)
    {
      cout << population[0].chromo[i] << endl;
    }
    cout << "\t";
    cout << "Fitness: " << population[0].fitness << "\t";
    cout << endl;
    generation++;

  }
  ```
  ## Rezultate
  
  ![Genetic-Filter-Opt](https://github.com/Motanovici/Cpp-Optimization-Algorithms/blob/main/Examples/Filter-Optimization-Genetic-Alg/img/results.png)
  
  Dupa ordonarea lor, s-au obtinut rezultatele:
  a = 1.02, b = 1.56, c = 1.02, e = 1.31, f = 0.67, g = -0.25
  
