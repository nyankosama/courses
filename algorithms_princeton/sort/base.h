/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified: 2014-05-19 08:00
#
# Filename: base.h
#
# Description: 
#
=============================================================================*/
#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include <time.h>
#include <sys/time.h>


#define show(array) _show(array, array_size(array))
#define isSorted(array) _isSorted(array, array_size(array))

template <class T>
using sortFunction = void(T t[], int size);

long getCurrentTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return time;
}

template<class T> 
bool less(T t1, T t2){
    return t1 < t2; 
}

template<class T>
void exch(T* t1, T* t2){
    T t = *t2;
    *t2 = *t1;
    *t1 = t;
}

template<class T, std::size_t Size>
std::size_t array_size(T(&)[Size]){return Size;}

template<class T>
void _show(T t[], int size){
    for (int i=0; i<size; i++){
        std::cout << t[i] << " ";
    }
    std::cout << std::endl;
}


template<class T>
bool _isSorted(T t[], int size){
    for (int i=0; i<size - 1; i++){
        if (less(t[i+1], t[i])) return false;
    }
    return true;
}

template<class T>
void sortCompare(sortFunction<T> func, T t[], int size, int sortNum){
    long time_sum = 0;
    for (int i=0; i<sortNum; i++){
        long begin_time = getCurrentTime(); 
        func(t, size);
        long end_time = getCurrentTime();
        time_sum += (end_time - begin_time);
    }
    std::cout << "total_time:" << time_sum << "ms" << std::endl;
    long avg_time = time_sum / sortNum;
    std::cout << "avg_time:" << avg_time << "ms" << std::endl;
}


#endif
