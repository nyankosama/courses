#include "unionFind.h"

template<int NODE_NUM>
UnionFind<NODE_NUM>::UnionFind(){
    for (int i = 0; i < NODE_NUM; i++) {
        _node_array[i] = i;
        _root_size[i] = 1;
    }
}

template<int NODE_NUM>
void UnionFind<NODE_NUM>::createUnion(int node1, int node2){
    int root1 = _root(node1);
    int root2 = _root(node2);
    if (root1 == root2)
        return;

    if (_root_size[root1] < _root_size[root2]){
        _node_array[root1] = root2;
        _root_size[root2] += _root_size[root1];
    }
    else {
        _node_array[root2] = root1;
        _root_size[root1] += _root_size[root2];
    }
}

template<int NODE_NUM>
bool UnionFind<NODE_NUM>::connected(int node1, int node2){
    if (_root(node1) == _root(node2))
        return true;
    else
        return false;
}

template<int NODE_NUM>
int UnionFind<NODE_NUM>::_root(int node){
    while (_node_array[node] != node){
        _node_array[node] = _node_array[_node_array[node]];
        node = _node_array[node];
    }
    return node;
}
