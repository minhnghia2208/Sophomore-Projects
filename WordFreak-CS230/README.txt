Name: Pham Minh Nghia 
SID: 32507133

	There are two files: bst.c 	and 	wordfreak.c

bst.c:	Overall, this is a modified version of BST so there is not much to talk about.
	This file is where program creates Word Node, BST.
	Hash functions: search, insert.
	
wordfreak.c:
	This file is where program reads inputs and applies BST.
	Hash functions: print_list.
	Functions: 	separate(string, len): is used to take words out of string and put said word to BST
			count_bytes(filename): counts number of bytes in file content. 
						So program don't need to check '\0'
			add_list(filename):	add node to the list. Separate function is the helper function of this function.
			main(): where program take various type of input: environment variables, pipe, manual terminal input,
				and line arguments.

link: https://www.youtube.com/watch?v=j2SYZl4Y_ZU&feature=youtu.be

