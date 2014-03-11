/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-03-11 05:22
#
# Filename:		unionFind.h
#
# Description: UnionFind operation data structure
#
=============================================================================*/
#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_

template<int NODE_NUM>
class UnionFind{
    public:
        UnionFind<NODE_NUM>();
        void createUnion(int node1, int node2);
        bool connected(int node1, int node2);

    private:
        int _root(int node);
        int _node_array[NODE_NUM];
        int _root_size[NODE_NUM];
};

#endif
