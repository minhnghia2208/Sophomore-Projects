# include "item.h"


struct Item *item (char* name, char* description, struct Item *next) {

	struct Item *newItem = NULL;
	newItem = (struct Item *) malloc(sizeof(struct Item));
	if (newItem == NULL)	
		return NULL;
	newItem->name = name;
	newItem->description = description;
	newItem->next = next;
	return newItem;
}

char* item_name(struct Item* item) {
	return item->name;
}
char* item_description(struct Item* item) {
	return item->description;
}
struct Item* item_next(struct Item* item) {
	return item->next;
}

struct Item *drop_item(char* name, struct Item *items){
	if (items == NULL)
		return NULL;
	while (items->next != NULL) {
		int result = strcmp(name, item_name(items->next));
		if (result == 0){
		
			struct Item* hold = items->next;
			items->next = items->next->next;

			return hold;
		}
		else 
			items = items->next;
	}
	return NULL;	
}

struct Item *add_item(struct Item* items, struct Item *add){
	add->next = NULL;	// cut tail
	if (items == NULL){
		items = add;
	}
	else {
		add->next = items;
		items = add;
	}
	return items;
}

