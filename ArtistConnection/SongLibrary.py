
class Song:

    def __init__(self, songRecord):
        tokens = songRecord.split(',')
        if len(tokens) != 6:
            print("incorrect song record")
        else:
            self.title = tokens[1]
            self.artist = tokens[2]
            self.duration = tokens[3]
            self.trackID = tokens[4]
            tokens[5] = tokens[5][:len(tokens[5])-1].split(';')
            self.coArtists = tokens[5]


    def toString(self):
        return "Title: " + self.title + ";  Artist: " + self.artist


class SongLibrary:

    def __init__(self):
        self.songArray = list()
        self.isSorted = False
        self.size = 0
    def quickSort(self):
        self.quickSortHelper(self.songArray, 0, len(self.songArray) - 1)
        self.isSorted = True

    def quickSortHelper(self, alist, first, last):
        if first < last:
            splitpoint = self.partition(alist, first, last)

            self.quickSortHelper(alist, first, splitpoint - 1)
            self.quickSortHelper(alist, splitpoint + 1, last)

    def partition(self, alist, first, last):    # a typical quick sort but we are comparing 2
        pivotvalue = alist[first].artist
        leftmark = first + 1
        rightmark = last

        done = False
        while not done:
            while leftmark <= rightmark and alist[leftmark].artist <= pivotvalue:
                leftmark = leftmark + 1

            while rightmark >= leftmark and alist[rightmark].artist >= pivotvalue:
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

    def loadLibrary(self, inputFilename):

        with open(inputFilename, 'r') as file:
            lines = file.readlines()
            for line in lines:
                song = Song(line)
                self.songArray.append(song)
                self.size += 1

        file.close()

    """
    Return song libary information
    """
    def libraryInfo(self):
        return "Size: " + str(self.size) + ";  isSorted: " + str(self.isSorted)


# WRITE YOUR OWN TEST UNDER THAT IF YOU NEED
if __name__ == '__main__':
    songLib = SongLibrary()
    songLib.loadLibrary("TenKsongs_proj2.csv")
    print(songLib.libraryInfo())
