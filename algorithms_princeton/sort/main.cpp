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
#include <cstring>
#include "sort.h"
#include "base.h"

#define MAX_INT 10000000
#define SORT_SIZE 10000
#define SORT_NUM 50

using namespace std;


int* copyArray(int* p, int size){
    int* dest = new int[size];
    memcpy(dest, p, size);
    return dest;
}

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
    cout << "selectionSort" << endl;
    sortCompare(selectionSort, copyArray(num, SORT_SIZE), SORT_SIZE, SORT_NUM);
}
