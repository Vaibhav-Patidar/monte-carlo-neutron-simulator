#include "random_utils.h"
#include <cmath>
#include <random>
using namespace std;
 
random_device rd;
mt19937 gen(rd());

const double PI = 3.141592653589793;

double zeroToOne(){
    uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}  

int randNum(int min, int max){
    uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

Direction randomDirection(){
    double r1 = zeroToOne();
    double r2 = zeroToOne();

    double theta = 2*r1*PI;
    double phi = acos(2*r2 - 1);
    double dx = sin(phi)*cos(theta);
    double dy = sin(phi)*sin(theta);
    double dz = cos(phi);

    Direction dir;
    dir.dx = dx;
    dir.dy = dy;
    dir.dz = dz;

    return dir;

}