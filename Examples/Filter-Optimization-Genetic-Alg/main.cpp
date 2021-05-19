#include <bits/stdc++.h>
#include <math.h>

using namespace std;
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

class Individ
{
public:
  vec chromo;
  double fitness;
  Individ(vec chromo);
  Individ mate(Individ parinte2);
  double cal_fitness();
};

Individ::Individ(vec chromo)
{
  this->chromo = chromo;
  fitness = cal_fitness();
};

Individ Individ::mate(Individ p2)
{
  vec copil;
  int len = chromo.size();
  for(int i =0;i<len;i++)
  {
    float p = random_num(0,100)/100;
    if(p < 0.45)
      copil.push_back(chromo[i]);
    else if(p < 0.90)
      copil.push_back(p2.chromo[i]);
    else
      copil.push_back(mutated_genes());
  }

  return Individ(copil);
};

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

bool operator<(const Individ &ind1, const Individ &ind2)
{
  return ind1.fitness < ind2.fitness;
}

int main() {
  
  srand((unsigned)(time(0)));

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
  cout << "Generatia: " << generation << "\t";
  cout << "Parametrii: " << endl;
  for(int i=0;i<6;i++)
  {
    cout << population[0].chromo[i] << endl;
  }
  cout << "\t";
  cout << "Fitness: " << population[0].fitness << "\t";
  cout << endl;


}
