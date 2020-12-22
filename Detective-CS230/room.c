# include "room.h"


struct Room* room(char* description, struct Item* items,	
	struct Room *north, struct Room *south,
	struct Room *east, struct Room *west)
{

	struct Room *newRoom = NULL;
	newRoom = (struct Room *) malloc(sizeof(struct Room));
	if (newRoom == NULL)	
		return NULL;
	newRoom->description = description;
	newRoom->items = items;
	newRoom->north = north;
	newRoom->south = south;
	newRoom->east = east;
	newRoom->west = west;
	return newRoom;
}


char* room_description(struct Room* room) {
	return room->description;
}


void  room_go_north(struct Room* room) {
	room = room->north;
}
void room_go_south(struct Room* room) {
	room = room->south;
}
void room_go_west(struct Room* room) {
	room = room->west;
}
void room_go_east(struct Room* room) {
	room = room->east;
}


void room_exit_north(struct Room* current, struct Room* other){
	current->north = other;
}
void room_exit_south(struct Room* current, struct Room* other){
	current->south = other;
}
void room_exit_east(struct Room* current, struct Room* other){
	current->east = other;
}
void room_exit_west(struct Room* current, struct Room* other){
	current->west = other;
}

