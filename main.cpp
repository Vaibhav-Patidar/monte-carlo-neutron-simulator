#include <iostream>
#include "random_utils.h"
#include <vector>
#include "simulation.h"
#include <fstream>
using namespace std;

int main(){
    ofstream file("k_results.csv");
    file << "keff\n";
    for (int i = 0; i < 10000; i++)
    {
        double k = runSim();
        file << k << "\n";
    }
    file.close();
    return 0;
} 