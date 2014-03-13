#include <cstdlib>
#include "percolation.h"

template<int GIRD_NUM>
Percolation<GIRD_NUM>::Percolation():
    _vtop_index(GIRD_NUM * GIRD_NUM),
    _vbottom_index(GIRD_NUM * GIRD_NUM + 1){
        for (int i = 0; i < GIRD_NUM; i++){
            _gird.createUnion(_vtop_index, i);
        }
        for (int i = GIRD_NUM * (GIRD_NUM - 1); i < GIRD_NUM * GIRD_NUM; i++){
            _gird.createUnion(_vbottom_index, i);
        }
        for (int i = 0; i < GIRD_NUM; i++){
            for (int j = 0; j < GIRD_NUM; j++){
                _gird_stat[i][j] = 0;
            }
        }
}

template<int GIRD_NUM>
void Percolation<GIRD_NUM>::open(int row, int column){
    _gird_stat[row][column] = 1;
    add_union(row - 1, column, row, column);
    add_union(row + 1, column, row, column);
    add_union(row, column - 1, row, column);
    add_union(row, column + 1, row, column);
}


template<int GIRD_NUM>
void Percolation<GIRD_NUM>::add_union(int row, int column, int ox, int oy){
    if (row < 0 || row >= GIRD_NUM || column < 0 || column >= GIRD_NUM)
        return;

    if (_gird_stat[row][column] == 1){
        _gird.createUnion(getIndexFromGird(ox,oy), getIndexFromGird(row,column));
    }
}


template<int GIRD_NUM>
void PercolationStat<GIRD_NUM>::doStat(){
    doPercolate();
}

template<int GIRD_NUM>
void PercolationStat<GIRD_NUM>::doPercolate(){
    cout << "percolation starts!" << endl;
    for (int i = 0; i < _time; i++){
        Percolation<GIRD_NUM> p;
        int open_num = 0;

        while (!p.percolates() && open_num <= GIRD_NUM * GIRD_NUM){
            int row = rand() % GIRD_NUM;
            int column = rand() % GIRD_NUM;
            if (!p.isOpen(row, column)){
                p.open(row, column);
                open_num ++;
            }
        }

        double fraction = double(open_num) / double(GIRD_NUM * GIRD_NUM);
        _fraction_list.push_back(fraction);
        cout << "fraction=" << fraction << endl;
    }
}


template<int GIRD_NUM>
void PercolationStat<GIRD_NUM>::report(){
    cout << "============REPORT==========" << endl;
    double sum = 0;
    for (vector<double>::iterator iter = _fraction_list.begin(); iter != _fraction_list.end(); ++iter){
        sum += *iter;
    }
    cout << "AVERAGE THREASHHOLD:" << sum / _time << endl;
}

