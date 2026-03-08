#include <iostream>
#include <vector>
#include "neutron.h"
#include "random_utils.h"
#include <algorithm>
#include <random>
#include <cmath>
using namespace std;

static random_device rd;
static mt19937 rng(rd());

double runSim(){
vector<Neutron> current_generation;
vector<Neutron> next_generation;

double reactor_size = 3.0;
int max_generations = 1000;
int target_population = 500;
int burn_in = 10;
double k = 0;
double sum_next = 0;
double sum_current = 0;

Neutron n;
n.energy = 2.0;
n.positionX = zeroToOne()*2 - 1;
n.positionY = zeroToOne()*2 - 1;
n.positionZ = zeroToOne()*2 - 1;


float scatter = 0.3;
float absorption = 0.3;
float fission = 0.4;

n.alive = true;
for (int i = 0; i < target_population; i++)
{
    Direction dir = randomDirection();
    n.dx = dir.dx;
    n.dy = dir.dy;
    n.dz = dir.dz;
    current_generation.push_back(n);
}

double k_sum = 0.0;
int k_count = 0;

for (int z =0; z < max_generations ; z++){
    if (current_generation.size() == 0){
        break;
    }
    int pop = current_generation.size();
    for (int i = 0; i < pop; i++)
    {
        Neutron n = current_generation[i];
        double xi = zeroToOne();
        double step = -log(xi);

        n.positionX += n.dx * step;
        n.positionY += n.dy * step;
        n.positionZ += n.dz * step;
        if (abs(n.positionX) > reactor_size || abs(n.positionY) > reactor_size || abs(n.positionZ) > reactor_size)
        {
            continue;
        }
        double r = zeroToOne();
        if (r < scatter)
        {
            double factor = randNum(5,9)/10.0;
            Direction d2 = randomDirection();
            n.dx = d2.dx;
            n.dy = d2.dy;
            n.dz = d2.dz;
            n.energy = n.energy * factor;
            next_generation.push_back(n);
        }
        else if (r < scatter+absorption)
        {         
        }
        else{
            int count = randNum(2,3);
            for (int j = 0; j < count; j++)
            {
                Neutron new_neutron;
                new_neutron.energy = 2;

                new_neutron.positionX = n.positionX;
                new_neutron.positionY= n.positionY;
                new_neutron.positionZ = n.positionZ;

                Direction d3 = randomDirection();
                new_neutron.dx = d3.dx;
                new_neutron.dy = d3.dy;
                new_neutron.dz = d3.dz;

                new_neutron.alive = true;
                next_generation.push_back(new_neutron);
            }        
        }      
    }

    sum_next += next_generation.size();
    sum_current += current_generation.size();
    double keff = sum_next / sum_current;
    cout << "Estimated keff: " << keff << endl;
    if (z > burn_in){
        k_sum += keff;
        k_count++;
    }

    if (next_generation.size() > target_population){
        shuffle(next_generation.begin(), next_generation.end(), rng);
        next_generation.resize(target_population);
    }
    if(next_generation.size() == 0)
    {
        return 0;
    }
    while (next_generation.size() < target_population)
    {
        int index = randNum(0, next_generation.size()-1);
        next_generation.push_back(next_generation[index]);
    }
    cout << "Generation " << z
     << " produced: " << next_generation.size()
     << " neutrons\n";
    current_generation = next_generation;
    next_generation.clear();
}
return (k_count > 0) ? k_sum / k_count : 0;
}