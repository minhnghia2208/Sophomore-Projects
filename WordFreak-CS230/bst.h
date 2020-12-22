#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word {	
	char word[40];
	int count;
	struct Word *left;
	struct Word *right;
};

struct Word *init (char word[], int count, struct Word *left, struct Word *right);

struct Word* search(struct Word* root, char word[]);

struct Word* insert(struct Word* root, char word[]);

void print_bst(struct Word *root);

