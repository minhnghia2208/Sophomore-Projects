# include <stdio.h>
# include <stdlib.h>
# include <string.h>


struct Item {

	char* name;
	char* description;
	struct Item *next;
};

struct Item *item (char* name, char* description, struct Item *next);

char* item_name(struct Item* item);
char* item_description(struct Item* item);
struct Item* item_next(struct Item* item);

struct Item *drop_item(char* name, struct Item *items);
struct Item *add_item(struct Item* add, struct Item *items);
