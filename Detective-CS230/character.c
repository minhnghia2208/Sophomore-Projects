# include "character.h"

struct Character* character(char* name, struct Room* location, struct Item* bag)
{

	struct Character *newCharacter = NULL;
	newCharacter = (struct Character *) malloc(sizeof(struct Character));
	if (newCharacter == NULL)	
		return NULL;
	newCharacter->name = name;
	newCharacter->location = location;
	newCharacter->bag = bag;
	return newCharacter;
}


void move_character(struct Character* avatar, char *direction) {
	if (strcmp(direction, "north") == 0) 
		room_go_north(avatar->location);
	if (strcmp(direction, "south") == 0)
		room_go_south(avatar->location);
	if (strcmp(direction, "west") == 0)
		room_go_west(avatar->location);
	if (strcmp(direction, "est") == 0)
		room_go_east(avatar->location);
}

