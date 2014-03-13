#include "percolation.h"
#include "percolation.cpp"

int main(){
    PercolationStat<1500> pc(10);
    pc.doStat();
    pc.report();
}
