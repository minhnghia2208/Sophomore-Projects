# include "bst.h"
int lgi = 0;
struct Word *init (char word[], int count, struct Word *left, struct Word *right) {
	struct Word *newWord = (struct Word *) malloc(sizeof(struct Word));
	if (newWord == NULL)	
		return NULL;

	strcpy(newWord->word, word);
	newWord->count = count;
	newWord->left = left;
	newWord->right = right;
	return newWord;
}

struct Word* search(struct Word* root, char word[]) {
	// if there is none then return NULL
	if (root == NULL)
		return NULL;

	int compare = strcmp(root->word, word);
	if (compare == 0)
		return root;
	// if given word is smaller than node then go left
	if (compare > 0)
		return search(root->right, word);
	// if given word is bigger than node then go right
	if (compare < 0)
		return search(root->left, word);
}

struct Word* insert(struct Word* root, char word[]){
	// if tree is empty then create new tree
	if (root == NULL)
		return init(word, 1, NULL, NULL);

	int compare = strcmp(root->word, word);
	// if word already exists, increase count
	if (compare == 0){
		root->count++;
		if (root != NULL)
		if (root->count > lgi)
			lgi = root->count;
	}
	// if given word is smaller than node then go left
	if (compare > 0)
		root->left = insert(root->left, word);
	// if given word is bigger than node then go right
	if (compare < 0)
		root->right = insert(root->right, word);

	return root;
}

// I don't use this function, but it is nice to have it here
void print_bst(struct Word *root) {
	if (root != NULL) {
		print_bst(root->left);
		printf("%-5s : %5i\n", root->word, root->count);
		print_bst(root->right);
	}
}
/*
void main() {
	struct Word *root = NULL;
	root = insert(root, "can");
	insert(root, "plus");
	insert(root, "and");
	insert(root, "d");
	print_bst(root);
}
*/
