#=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-03-11 01:42
#
# Filename:		unionFind.py
#
# Description: UnionFind operation data structure
#
#=============================================================================*/

class UnionFind:
    def __init__(self, num):
        self.idArray = range(num)
        self.size = [1] * num
    
    def union(self, node1, node2):
        #use weighted union-find
        root1 = self.__root(node1)
        root2 = self.__root(node2)
        if root1 == root2:
            return
        if self.size[root1] < self.size[root2]:
            self.idArray[root1] = root2
            self.size[root2] += self.size[root1]
        else:
            self.idArray[root2] = root1
            self.size[root1] += self.size[root2]

    def connected(self, node1, node2):
        if self.__root(node1) == self.__root(node2):
            return True
        else:
            return False

    #find the root of a given node
    def __root(self, node):
        while self.idArray[node] is not node:
            #use path compression
            self.idArray[node] = self.idArray[self.idArray[node]]
            node = self.idArray[node]
        return node


if __name__=="__main__":
    #test cases
    uf = UnionFind(10)
    uf.union(0,5)
    uf.union(5,6)
    uf.union(6,1)
    uf.union(1,2)
    uf.union(2,7)

    uf.union(8,3)
    uf.union(3,4)
    uf.union(4,9)

    print uf.connected(0,5)#True
    print uf.connected(0,7)#True
    print uf.connected(1,2)#True
    print uf.connected(5,8)#False

    print uf.connected(8,9)#True
    print uf.connected(2,9)#False

