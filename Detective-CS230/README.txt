README.txt

Name: Pham Minh Nghia - Project 2

Youtube Link: youtube.com/watch?v=M0YUb4Xuom0

There are 2 big parts in the adventure.c: init() and main()
	The init() is quite straighforward and least bugs
	There were a lot of bugs to handle in the main() because of the take_item and drop_item functions:

		Take_iem and Drop_item required me to manipulate LinkedList thus created a lot of Segmentation Fault Errors

		Look_command is straightforward: print out current room, item, character

		Inventory_command is similar to look_command: instead of print out item in room, we print out item in character->bag
		
		List_command and Help_command are basically printf

		Go_command: I just need to change character->location 

		Clue_command: The process might look straightforward, but I encountered many unexpected bugs

		At the end, I freed all of the variables which use malloc

room.c item.c are just copy-paste from lab.c
	I have not found the use for Struct item -> description. However, I still kept it there

character.c is the combination of room.c and item.c:
	Struct character has 
		struct Room* location: to store character location, 
		struct Item* bag: to keep track of item on character
 		char* name: store the name

In conclusion, the project, even though time consuming, is very fun and enjoyable (for the most parts)
