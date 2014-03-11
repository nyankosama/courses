#=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-03-11 01:55
#
# Filename:		assignment1_percolation.py
#
# Description: the assignment description link: http://coursera.cs.princeton.edu/algs4/assignments/percolation.html
#
#=============================================================================*/

from unionFind import UnionFind
import random

class Percolation:
    #construct a NxN grid to simulate the percolation system
    def __init__(self, girdNum):
        self.vtopIndex = girdNum * girdNum
        self.vbottomIndex = girdNum * girdNum + 1
        self.girdNum = girdNum
        self.girdStat = self.__createGridBlocked(girdNum)
        # 2 virtual nodes for the convenience of checking the connection of top and bottom 
        self.gird = UnionFind(girdNum * girdNum + 2) 
        for i in range(girdNum):
            self.gird.union(self.vtopIndex, i)
        for i in range(girdNum * (girdNum - 1), girdNum * girdNum):
            self.gird.union(self.vbottomIndex, i)
    
    def open(self, row, column):
        self.girdStat[row][column] = 1
        #check the nodes around if they are open. if yes, union with it
        for node in self.__getNodeListAround(row, column):
            if self.girdStat[node["row"]][node["column"]] == 1:
                self.gird.union(self.__getIndexFromGird(row, column),self.__getIndexFromGird(node["row"], node["column"]))

    def isOpen(self, row, column):
        return self.girdStat[row][column] == 1

    def percolates(self):
        return self.gird.connected(self.vtopIndex, self.vbottomIndex)

    def __createGridBlocked(self, girdNum):
        gird = list()
        for i in range(girdNum):
            gird.append(list())
            for j in range(girdNum):
                gird[i].append(0)

        return gird

    def __getIndexFromGird(self, row, column):
        return row * self.girdNum + column

    def __getNodeListAround(self, row, column):
        nodeList = list()
        nodeList.append({"row" : row, "column" : column - 1})
        nodeList.append({"row" : row, "column" : column + 1})
        nodeList.append({"row" : row - 1, "column" : column})
        nodeList.append({"row" : row + 1, "column" : column})
        for node in nodeList:
            if node["row"] < 0 or node["row"] >= self.girdNum or node["column"] < 0 or node["column"] >= self.girdNum:
                nodeList.remove(node)
        
        return nodeList

class PercolationStat:
    def __init__(self, girdNum, t):
        self.time = t
        self.girdNum = girdNum
        self.fractionList = list()

        self.__doPercolate()

    def report(self):
        print "============REPORT============"
        fractionSum = 0
        for num in self.fractionList:
            fractionSum += num
        print "AVERAGE THREASHHOLD:" + str(fractionSum / len(self.fractionList))

    def __doPercolate(self):
        print "percolation starts!"
        for i in range(self.time):
            p = Percolation(self.girdNum)
            
            openNum = 0
            while (p.percolates() is not True) and (openNum <= self.girdNum * self.girdNum) :
                row = random.randrange(0, self.girdNum, 1)
                column = random.randrange(0, self.girdNum, 1)
                if p.isOpen(row, column) is not True:
                    p.open(row, column)
                    openNum += 1
            
            fraction = float(openNum) / (self.girdNum * self.girdNum)
            self.fractionList.append(fraction)
            print "fraction = " + str(fraction)

def test():
    #test cases
    #3x3 gird
    print "==========="
    p = Percolation(3)
    print p.percolates()#False
    p.open(0, 0)
    p.open(1, 0)
    p.open(2, 0)
    print p.percolates()#True

    print "==========="
    p = Percolation(3)
    p.open(0, 0)
    p.open(1, 1)
    p.open(2, 2)
    print p.percolates()#False
    print "========="
    print p.isOpen(0,0)
    print p.isOpen(1,2)


if __name__ == "__main__":
    ps = PercolationStat(1000, 10)
    ps.report()

