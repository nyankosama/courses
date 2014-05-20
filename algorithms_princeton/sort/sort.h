/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified: 2014-05-19 18:27
#
# Filename: sort.h
#
# Description: 
#
=============================================================================*/
#ifndef _SORT_H_
#define _SORT_H_

#include "base.h"

template<class T>
    void selectionSort(T t[], int size){
        for (int i=0; i<size; i++) {
            int min = i;
            for (int j=i+1; j<size; j++){
                if (less(t[j], t[min])) min = j;
            }
            exch(&t[i], &t[min]);
        }
    }

template<class T>
    void insertSort(T t[], int size){
        for (int i=1; i<size; i++){
            T val = t[i];
            int j = i;
            for (; j>0 && less(val, t[j-1]); j--){
                t[j] = t[j-1];
            }
            t[j] = val;
        }
    }

template<class T>
    void shellSort(T t[], int size){
        int h = 1;
        while (h < size/3) h = h*3+1;
        while(h >= 1){
            for (int i=h; i<size; i++){
                T val = t[i];
                int j = i;
                for (; j>=h && less(val, t[j-h]); j-=h){
                    t[j] = t[j-h];
                }
                t[j] = val;
            }
            h = h/3;
        }
    }

template<class T>
    void _merge(T t[], int lo, int mid, int hi, int aux[]){ 
        int i = lo;
        int j = mid + 1;
        for (int k = lo; k <= hi; k++){
            aux[k] = t[k];
        }

        for (int k = lo; k <= hi; k++){
            if (i > mid) t[k] = aux[j++];
            else if(j > hi) t[k] = aux[i++];
            else if(less(aux[i], aux[j])) t[k] = aux[i++];
            else t[k] = aux[j++];
        }
    } 

template<class T>
    void _mergeSort(T t[], int lo, int hi, int aux[]){
        if (lo >= hi) return;
        int mid = lo + (hi - lo)/2;
        _mergeSort(t, lo, mid, aux);
        _mergeSort(t, mid+1, hi, aux);
        _merge(t, lo, mid, hi, aux);
    }

template<class T>
    void mergeSort(T t[], int size){
        int* aux = new int[size];
        _mergeSort(t, 0, size-1, aux);
        delete aux;
    }


#endif
