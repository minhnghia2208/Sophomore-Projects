import random
from .Graph import Vertex, Queue
from .SongLibrary import SongLibrary
import sys
import os
import unittest

class ArtistConnections:

    def __init__(self):
        self.vertList = {}
        self.numVertices = 0


    """
    Load the artist connections graph based on a given song database
    Add the edges based on the last column of the collaborative artists 
    
    """

    def getVertices(self):
        return self.vertList.keys()

    def getVertex(self,n):
        if n in self.vertList:
            return self.vertList[n]
        else:
            return None

    def addVertex(self,key):
        self.numVertices = self.numVertices + 1
        newVertex = Vertex(key)
        self.vertList[key] = newVertex

    def addEdge(self,f,t,cost):
        if f not in self.vertList:
            self.addVertex(f)
        if t not in self.vertList:
            self.addVertex(t)
        self.vertList[f].addNeighbor(self.vertList[t], cost)
        self.vertList[t].addNeighbor(self.vertList[f], cost)    # 2 way weights

    def load_graph(self, songLibrary):

        #
        # Write your code here
        #

        alist = SongLibrary()
        alist.loadLibrary(songLibrary)  # load song library in form
        alist.quickSort()   # sort list

        for i in range(0, alist.size):  # loop through whole TenKSong
            for j in alist.songArray[i].coArtists:   # add connection to co-authors
                if j in self.vertList:
                    num, store = self.search_artist(j)
                    if alist.songArray[i].artist in store:
                        self.addEdge(alist.songArray[i].artist, j,
                        self.vertList[alist.songArray[i].artist].getWeight(self.getVertex(j)) + 1) # increase edge weight if already exists
                    else:
                        self.addEdge(alist.songArray[i].artist, j, 1)  # edge weight is 1 if no connection
                                            # from co-artist to artist
                else:

                    self.addEdge(alist.songArray[i].artist, j, 1) # edge weight is 1 if no connection
                    # from artist to co-artist

            self.vertList[alist.songArray[i].artist].songs.append(alist.songArray[i].title)   # add song into Vertex

        return self.numVertices

    """
    Return song libary information
    """
    def graph_info(self):
        return "Vertex Size: " + str(self.numVertices)

    """
    Search the information of an artist based on the artist name
    Return a tuple (the number of songs he/she wrote, the collaborative artist list)

    """
    def search_artist(self, artist_name):

        numSongs = 0;
        artistLst = []


        #
        # Write your code here
        #
        if artist_name in self.vertList:    # get vertex information from VertList
            store = self.vertList[artist_name].getConnections()
            numSongs = len(self.vertList[artist_name].songs)

        else:
            return None

        for i in store:
            artistLst.append(i.id)  # convert keys dictionary to array
        return numSongs, artistLst

    """
    Return a list of two-hop neighbors of a given artist
    """
    def find_new_friends(self, artist_name):

        two_hop_friends = []

        num, co = self.search_artist(artist_name)
        for i in co:    # go through every co-artist
            num, subco = self.search_artist(i)


            for j in subco: # go through every co of the co-artist
                if j not in two_hop_friends and j not in co and j != artist_name:
                    two_hop_friends.append(j)   # if the co-co-artist is not working with the main artist

        return two_hop_friends

    """
    Search the information of an artist based on the artist name

    """
    def recommend_new_collaborator(self, artist_name):

        artist = ""
        numSongs = 0

        #
        # Write your code here
        #
        if artist_name in self.vertList:
            mark = {}   # dictionary to save the
            mark2 = []  # parallel array to know if co-artist already exists
            for i in self.vertList[artist_name].getConnections(): # go through
                first_hop = self.vertList[artist_name].getWeight(i)
                if i.getId() in self.vertList:

                    for j in self.vertList[i.getId()].getConnections():  # go through every co of the co-artist
                        if j.getId() != artist_name: # if co-coartist is not main artist
                            if j.getId() in mark2:  # if co-co-artist already go through
                                mark[j.getId()] = mark[j.getId()] + self.vertList[i.getId()].getWeight(j)
                            else:
                                mark[j.getId()] = self.vertList[i.getId()].getWeight(j)
                            if numSongs < mark[j.getId()]:  # find the largest
                                numSongs = mark[j.getId()]
                                artist = j.id
                            mark2.append(j.getId())




        return numSongs, artist

    """
    Search the information of an artist based on the artist name

    """

    def shortest_path(self, artist_name): # use BFS for shortest path
        path = {}
        for i in self.getVertices():  # reset Vertices information after each run
            i = self.getVertex(i)
            i.distance = 0
            i.color = 'white'
            i.dist = sys.maxsize
            i.pred = None
            i.disc = 0
            i.fin = 0

        #
        # Write your code here
        #
        start = self.getVertex(artist_name)
        start.setDistance(0)
        start.setPred(None)
        vertQueue = Queue()
        vertQueue.enqueue(start)
        while (vertQueue.size() > 0):
            currentVert = vertQueue.dequeue()
            for nbr in currentVert.getConnections():
                if (nbr.getColor() == 'white'):
                    nbr.setColor('gray')
                    nbr.setDistance(currentVert.getDistance() + 1)
                    nbr.setPred(currentVert)
                    vertQueue.enqueue(nbr)
            currentVert.setColor('black')
        for i in self.getVertices():
            j = self.getVertex(i)
            path[i] = j.dist
        return path


# WRITE YOUR OWN TEST UNDER THAT IF YOU NEED
if __name__ == '__main__':
    artistGraph = ArtistConnections()
    print(artistGraph.load_graph("TenKsongs_proj2.csv"))
    print(artistGraph.search_artist("Mariah Carey"))
    print(artistGraph.find_new_friends("Green Day"))
    print(artistGraph.recommend_new_collaborator("Santana"))
    print(artistGraph.shortest_path("Santana"))
    print(" ")
#    ArtistConnections.generate_data("TenKsongs_proj2.csv")
