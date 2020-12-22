# include <stdio.h>
# include <stdlib.h>
# include <string.h>


struct Room {
	char* description;
	struct Item* items;
	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
};	


struct Room* room(char* description, struct Item* items,	
	struct Room *north, struct Room *south,
	struct Room *east, struct Room *west);

char* room_description(struct Room* room);


void  room_go_north(struct Room* room);
void room_go_south(struct Room* room);
void room_go_west(struct Room* room);
void room_go_east(struct Room* room);


void room_exit_north(struct Room* current, struct Room* other);
void room_exit_south(struct Room* current, struct Room* other);
void room_exit_east(struct Room* current, struct Room* other);
void room_exit_west(struct Room* current, struct Room* other);

