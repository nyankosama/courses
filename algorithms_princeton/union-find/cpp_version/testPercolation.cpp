#include "percolation.h"
#include "percolation.cpp"

int main(){
    PercolationStat<500> pc(10);
    pc.report();
}
