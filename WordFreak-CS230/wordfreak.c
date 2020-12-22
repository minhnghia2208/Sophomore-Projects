#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>	// for open 
#include <sys/stat.h>	// for open
#include <unistd.h>	// for close
#include <fcntl.h>	// for open and close
#include <string.h>
#include "bst.h"

char alphabet[52] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};	// alphabet table include upper and lower cases
int lgw = 0;	// store longest word
extern int lgi;	// store longest count | extern so I can use in bst.c
struct Word* list[26];	// each letter has its own BST

// Function for taking word from string
void separate (char* string, int len) {
	char temp[40];	// 40 is random number, no words is longer than 40 characters
	int pos = 0;	// used to store character position
	
	for (int i = 0; i <= len; i++) {
		int check = 0;
		char* compare = strchr(alphabet, string[i]);	// check letter is in alphabet table
		if (compare != NULL) {	// if character is an alphabetical character then put character into temp
			if ((int) string[i] < 91) { // if character is uppercase then change to lowercase
				string[i] = (int) string[i] + 32;
				string[i] = (char) string[i];
			}
			temp[pos] = string[i];
			pos++;
/*
			// if end of script
			if (i == len && pos != 0) {
				strncpy(temp, temp, pos-1); // copy temp to arr
				compare = strchr(alphabet, temp[0]);
				temp[pos] = '\0';	// put the stop sign
				int alpha = compare - alphabet;	// find the right BST tree for the word
				list[alpha] = insert(list[alpha], temp);
				if (strlen(temp) > lgw) 	// compare if temp is the longest word
					lgw = strlen(temp);

				pos = 0;
			}
*/
		} else if (pos != 0) {	// if character is not an alphabetical character then word end
				
			strncpy(temp, temp, pos); // copy temp to arr
			compare = strchr(alphabet, temp[0]);
			temp[pos] = '\0';	// put the stop sign
			int alpha = compare - alphabet;	// find the right BST tree for the word
			list[alpha] = insert(list[alpha], temp);

			if (strlen(temp) > lgw) 	// compare if temp is the longest word
				lgw = strlen(temp);

			pos = 0;
		}
	}
}
// BST inorder traversal
void print_list(struct Word *root, int fdout) {
	if (root != NULL) {
		print_list(root->left, fdout);

		char store[100];
		sprintf(store, "%-*s:%*i \n", lgw+1, root->word, lgi+1, root->count);
//		printf("%s", store);	
		write(fdout, store, strlen(store));

		print_list(root->right, fdout);
	}
}
// Function for counting number of bites for .txt file.
int count_byte(char *filename) {
	int fdin = open(filename, O_RDONLY);
  	char *buf = (char *) malloc(1024);
	double count;

  	if (fdin < 0)  
		printf("Cannot open file.\n");  
 	while (read(fdin, buf, 1) > 0){	// count number of bits
		count ++;	
	}
	close(fdin);
	if (fdin <0)
		printf("Cannot close file.\n");
	free(buf);
	return count;
}
// add node to list function
void add_list(char* filename) {	
	int count = count_byte(filename);
		
   	int fdin = open(filename, O_RDONLY);
	char *buf = (char *) malloc(count);

	while (read(fdin, buf, count) > 0){	
	    	separate(buf, strlen(buf)-1);
	}
	close(fdin);
	if (fdin < 0)
		printf("Cannot close file.\n");
	free(buf);	
}

extern char** environ;

void main (int argc, char *argv[]) {
// ENVIRONT VARIABLE
	char *env = getenv("WORD_FREAK");
	if (env != NULL)
		add_list(env);

// COMMAND LINE ARGUMENT
	argv = argv+1;	// skip the first input
	while (argv[0] != NULL) {
		
		int arlen = strlen(argv[0]) - 1;
	
		if (argv[0][arlen] == 't' && argv[0][arlen-1] == 'x' && argv[0][arlen-2] == 't' && argv[0][arlen-3] == '.') 	// if file is .txt
			add_list(argv[0]); 
		argv = argv + 1;
	}
	
	int fdout = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644); // output
		if (fdout < 0)
			printf("Cannot open output.txt.\n");

// TERMINAL DIRECT INPUT
	char store[999999]; 	// string for storing file content

//	if (argc == 1 && env == NULL){	// no command line argument and no environtment variable
	char buffer[999999];
	int count = 0;
	while (read(0, buffer, sizeof(buffer))>0)
		for (long i = 0; i < 999999; i++){ 
			if (buffer[i] == '\0'){		// if EOF then stop
				strncpy(store, buffer, i);	// copy buffer to store
				separate(store, strlen(store));
				i = 1000000;
			}
	
			if (i == 999998) {
//				separate(buffer, strlen(buffer));
				strcpy(store, buffer);
				separate(store, strlen(store));
			}
		}

	
// FIND THE LONGEST SPACING FOR COUNT
	int space = 1;
	while (lgi > 9) {
		space++;
		lgi = lgi / 10;
	}
	lgi = space;

// PRINT OUT BST	
	for (int i = 0; i <= 25; i++) 
		if (list[i] != NULL){
			print_list(list[i], fdout);
//			printf(".......\n");
			write(fdout, "......\n", 7);
		}
	close(fdout);
	if (fdout < 0)
		printf("Cannot close file.\n");
	
}
