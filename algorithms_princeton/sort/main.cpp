/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified: 2014-05-19 08:45
#
# Filename: main.cpp
#
# Description: 
#
=============================================================================*/
#include <iostream>
#include <random>
#include <functional>
#include "sort.h"
#include "base.h"

const int MAX_INT = 10000000;
const int SORT_SIZE = 10000;
const int SORT_NUM = 50;


using namespace std;


int main(){
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1,MAX_INT);
    auto int_gen = bind(distribution, generator);
    int num[SORT_SIZE];
    for (int i=0; i<SORT_SIZE; i++){
        num[i] = int_gen();
    }
    cout << "shellSort" << endl;
    sortCompare(shellSort, copyArray(num, SORT_SIZE), SORT_SIZE, SORT_NUM);
    cout << "insertSort" << endl;
    sortCompare(insertSort,copyArray(num, SORT_SIZE), SORT_SIZE, SORT_NUM);
    cout << "mergesort" << endl;
    sortCompare(mergeSort,copyArray(num, SORT_SIZE), SORT_SIZE, SORT_NUM);

}
