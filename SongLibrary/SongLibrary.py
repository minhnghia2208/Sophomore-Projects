"""
UMass ECE 241 - Advanced Programming
Project #1     Fall 2019
SongLibrary.py - SongLibrary class
"""

from .Song import Song
from .binarySearchTree import BinarySearchTree
from .binarySearchTree import TreeNode
from .AVLTree import AVLTree
import random
import time


class SongLibrary:

    def __init__(self):
        self.songArray = list()
        self.songBST = None
        self.isSorted = False
        self.size = 0
    def append(self, song):     # create to append 100 random song objects
        self.songArray.append(song)

    def loadLibrary(self, inputFilename):
        f = open(inputFilename, "r")    # Open file
        fl = f.readlines()
        for line in fl: # read each lines in excel
            self.size += 1  # increase size by one for each line
            self.songArray.append(Song(line)) # insert to the code

    def linearSearch(self, query, attribute):
        found = -1
        for line in self.songArray:
            if attribute == "title":
                if line.title == query:
                    found += 1
                    return found + 1    # title is unique so no need to go any further
            else:
                if line.artist == query:
                    found += 1

        if found != -1:
            found += 1  # because I set found = -1 so I need to increase by one to match
        return found


    """
    Build a BST from your Song library based on the song title. 
    Store the BST in songBST variable
    """

    def buildBST(self):
        self.songBST = AVLTree()
        for i in range(len(self.songArray) - 1):
            self.songBST[self.songArray[i].title] = self.songArray[i]
    """
    Implement a search function for a query song (title) in the songBST.
    Return the song information string
    (After you find the song object, call the toString function)
    or None if no such song is found.
    """

    def searchBST(self, query):
        found = False
        current = self.songBST.root
        while not found and current != None:
            if current.key == query: # found and stop
                found = True
                return (self.songBST[current.key].toString())
            else:
                if current.key > query:     # if value is smaller than key then go left
                    current = current.hasLeftChild()
                else:
                    current = current.hasRightChild()   # else go right
        return None


    def libraryInfo(self):
        return "Size: " + str(self.size) + ";  isSorted: " + str(self.isSorted)


    def quickSort(self):
        self.quickSortHelper(self.songArray, 0, len(self.songArray) - 1)
        self.isSorted = True

    def quickSortHelper(self, alist, first, last):
        if first < last:
            splitpoint = self.partition(alist, first, last)

            self.quickSortHelper(alist, first, splitpoint - 1)
            self.quickSortHelper(alist, splitpoint + 1, last)

    def partition(self, alist, first, last):    # a typical quick sort but we are comparing 2
        pivotvalue = alist[first].title
        leftmark = first + 1
        rightmark = last

        done = False
        while not done:
            while leftmark <= rightmark and alist[leftmark].title <= pivotvalue:
                leftmark = leftmark + 1

            while rightmark >= leftmark and alist[rightmark].title >= pivotvalue:
                rightmark = rightmark - 1

            if rightmark < leftmark:
                done = True
            else:
                temp = alist[leftmark]
                alist[leftmark] = alist[rightmark]
                alist[rightmark] = temp

        temp = alist[first]
        alist[first] = alist[rightmark]
        alist[rightmark] = temp

        return rightmark

# WRITE YOUR OWN TEST UNDER THAT IF YOU NEED
if __name__ == '__main__':
    songLib = SongLibrary()
    songLib.loadLibrary("TenKsongs.csv")

    time_arr = list()
    songLib.quickSort()


# 10k songs search
    print("10k songs")

# Time to find element using linearSearch
    start_time = time.time()
    for i in range(101):
        song = random.choice(songLib.songArray)
        song = song.title
        songLib.linearSearch(song, "title")
    print("linear search:")
    t = (time.time() - start_time) * 1000
    print(t, "ms")

# Time to build BST
    start_time = time.time()
    songLib.buildBST()
    print("Building BST:")
    t1 = (time.time() - start_time) * 1000
    print(t1, "ms")
    t2 = 0
# Time to find element using BST
    start_time = time.time()
    for i in range(101):
        song = random.choice(songLib.songArray)
        song = song.title
        songLib.searchBST(song)
    print("searchBST:")
    t2 = (time.time() - start_time) * 1000
    print(t2, "ms")

# Total time for BST:
    print("Total time for BST: ", t1 + t2, "ms")

# Number of linearSearch to match search BST
    if t != 0:
        n = float(t1+t2)/float(t)
        print("n = ", n, " times")
    else:
        print("time for linear search is too small")

    print(songLib.libraryInfo())