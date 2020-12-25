import sys
import os
import unittest

class Vertex:
    def __init__(self, artist):
        self.id = artist
        self.songs = []
        self.coArtists = {}
        self.distance = 0
        self.color = 'white'
        self.dist = sys.maxsize
        self.pred = None
        self.disc = 0
        self.fin = 0

    def addNeighbor(self, nbr, weight=0):
        self.coArtists[nbr] = weight

    def __str__(self):
        return str(self.id) + ' connectedTo: ' + str([x.id for x in self.coArtists])

    def getConnections(self):
        return self.coArtists.keys()

    def getId(self):
        return self.id

    def getWeight(self, nbr):
        return self.coArtists[nbr]


    def setColor(self, color):
        self.color = color


    def setDistance(self, d):
        self.dist = d


    def setPred(self, p):
        self.pred = p


    def setDiscovery(self, dtime):
        self.disc = dtime


    def setFinish(self, ftime):
        self.fin = ftime


    def getFinish(self):
        return self.fin


    def getDiscovery(self):
        return self.disc


    def getPred(self):
        return self.pred


    def getDistance(self):
        return self.dist


    def getColor(self):
        return self.color


class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)


class Graph:
    def __init__(self):
        self.vertList = {}
        self.numVertices = 0

    def addVertex(self,key):
        self.numVertices = self.numVertices + 1
        newVertex = Vertex(key)
        self.vertList[key] = newVertex
        return newVertex

    def getVertex(self,n):
        if n in self.vertList:
            return self.vertList[n]
        else:
            return None

    def __contains__(self,n):
        return n in self.vertList

    def addEdge(self,f,t,cost=0):
        if f not in self.vertList:
            nv = self.addVertex(f)
        if t not in self.vertList:
            nv = self.addVertex(t)
        self.vertList[f].addNeighbor(self.vertList[t], cost)


    def getVertices(self):
        return self.vertList.keys()


    def __iter__(self):
        return iter(self.vertList.values())


# WRITE YOUR OWN TEST UNDER THAT IF YOU NEED
if __name__ == '__main__':
    g = Graph()
    for i in range(5):
        g.addVertex(i)

    g.addEdge(1,2,1)
    g.addEdge(1,5,2)
    g.addEdge(2,5,3)

    for v in g:
        for w in v.getConnections():
            print("( %s , %s )" % (v.getId(), w.getId()))

    yeet = Vertex("yeet")
    yeet.addNeighbor("Stronk", 1)
    yeet.addNeighbor("Meme", 2)
    print(yeet.getConnections())