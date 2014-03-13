/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-03-11 06:20
#
# Filename:		percolation.h
#
# Description: 
#
=============================================================================*/
#ifndef _PERCOLATION_H_
#define _PERCOLATION_H_

#include <iostream>
#include <vector>
#include "unionFind.h"
#include "unionFind.cpp"

using namespace std;

template<int GIRD_NUM>
class Percolation{
    public:
        
        Percolation();       
        
        void open(int row, int column);

        bool isOpen(int row, int column){
            return _gird_stat[row][column] == 1;
        }

        bool percolates(){
            return _gird.connected(_vtop_index, _vbottom_index);
        }

    private:
        int _vtop_index;
        int _vbottom_index;
        int _gird_stat[GIRD_NUM][GIRD_NUM];
        UnionFind<GIRD_NUM*GIRD_NUM+2> _gird;
        
        void add_union(int row, int column, int ox, int oy);
        int getIndexFromGird(int row, int column){
            return row * GIRD_NUM + column; 
        }
};

template<int GIRD_NUM>
class PercolationStat{
    public:
        PercolationStat(int t):_time(t){}
        void doStat();
        void report();
    private:
        int _time;
        vector<double> _fraction_list;
        void doPercolate();
};



#endif


