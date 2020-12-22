# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "room.h"
//# include "item.h"


struct Character {
	char* name;
	struct Room *location;
	struct Item *bag;
};

struct Character* character(char* name, struct Room* location, struct Item* bag);

void move_character(struct Character* avatar, char *direction);
