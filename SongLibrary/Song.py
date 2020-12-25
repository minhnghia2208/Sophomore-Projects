"""
UMass ECE 241 - Advanced Programming
Project #1     Fall 2019
Song.py - Song class
"""

class Song:

    """
    Intial function for Song object.
    parse a given songRecord string to song object.
    For an example songRecord such as "0,Qing Yi Shi,Leon Lai,203.38893,5237536"
    It contains attributes (ID, title, artist, duration, trackID)
    """
    def __init__(self, songRecord):
        #
        # Write your code here
        #
        alist = songRecord.split(",")
        self.ID = alist[0]
        self.title = alist[1]
        self.artist = alist[2]
        self.duration = alist[3]
        self.trackID = alist[4]
    def toString(self):
        return "Title: " + self.title + ";  Artist: " + self.artist

# WRITE YOUR OWN TEST UNDER THAT IF YOU NEED
if __name__ == '__main__':

    sampleSongRecord = "0,Qing Yi Shi,Leon Lai,203.38893,5237536"
    sampleSong = Song(sampleSongRecord)
    print(sampleSong.toString())