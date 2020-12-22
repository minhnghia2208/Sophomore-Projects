# include "item.h"
# include "character.h"
# include <time.h>

int get_random_number(int max){
	
	int random = rand() % max;

    	return random;
}


char* get_random_room(char* list[]){
//	srand(time(0));
	int random = rand() % 9;
	while (strcmp(list[random], "USED") == 0)
		random = rand() % 9;
		
	char* location = list[random];
	list[random] = "USED";
    	return location;
}

int item_index = -1;
char* get_random_item(char* list[]){
//	srand(time(0));
	int random = rand() % 9;
	while (strcmp(list[random], "USED") == 0)
		random = rand() % 9;
		
	char* location = list[random];
	list[random] = "USED";
	item_index = random;
	if (random > 5)
		return NULL;
    	return location;
}

// Generating Rooms, Characters, and Items
/*
	1--2--3     N
	|  |  |
	4--5--6 W    	E
	|  |  |
	7--8--9     S
*/
struct Character* arr_character[6];
struct Item* arr_item[9];
struct Room* arr_room[3][3];

struct Room* init() {
// Generating Items

	char* list_item[9] = {"Battery", "Key", "Cola", "Laptop", "Milk", "Iphone", NULL, NULL, NULL};
	char* list_desc[9] = {"Leaking", "Rusted", "Pepsi Inside", "Window Vista", "Extra Vitamin D", "Android OS", NULL, NULL, NULL};	

//	struct Item* arr_item[9];
	arr_item[0] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[1] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[2] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[3] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[4] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[5] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[6] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[7] = item(get_random_item(list_item), list_desc[item_index], NULL);
	arr_item[8] = item(get_random_item(list_item), list_desc[item_index], NULL);


// Generating Rooms
//	struct Room* arr_room[3][3];
	char* list_room[9] = {"Vault Door", "Dining Room", "Bath Room", "Recreation Center", "Security Room", "Power Plant", "Bed Room", "Laboratory", "Meeting Hall"};

	arr_room[0][0] = room(get_random_room(list_room), arr_item[0], NULL, NULL, NULL, NULL);
	arr_room[0][1] = room(get_random_room(list_room), arr_item[1], NULL, NULL, NULL, NULL);
	arr_room[0][2] = room(get_random_room(list_room), arr_item[2], NULL, NULL, NULL, NULL);
	arr_room[1][0] = room(get_random_room(list_room), arr_item[3], NULL, NULL, NULL, NULL);
	arr_room[1][1] = room(get_random_room(list_room), arr_item[4], NULL, NULL, NULL, NULL);
	arr_room[1][2] = room(get_random_room(list_room), arr_item[5], NULL, NULL, NULL, NULL);
	arr_room[2][0] = room(get_random_room(list_room), arr_item[6], NULL, NULL, NULL, NULL);
	arr_room[2][1] = room(get_random_room(list_room), arr_item[7], NULL, NULL, NULL, NULL);
	arr_room[2][2] = room(get_random_room(list_room), arr_item[8],  NULL, NULL, NULL, NULL);

// Generating Characters
//	struct Character* arr_character[6];
	int check[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
	int x, y = 0;
	
	x = get_random_number(3);	// Generating random room location to put character in
	y = get_random_number(3);

	while (check[x][y] == 1){ // if check[x][y] == 1 then room is occupied by someone
		x = get_random_number(3);	// Random other room
		y = get_random_number(3);
	}
	check[x][y] = 1;	// Set room is occupied
	arr_character[0] = character("Jisoo", arr_room[x][y], NULL);

	// Rinse and Repeat for other characters
	x = get_random_number(3);
	y = get_random_number(3);
	while (check[x][y] == 1){
		x = get_random_number(3);
		y = get_random_number(3);
	}

	check[x][y] = 1;

	arr_character[1] = character("Jong-Suk", arr_room[x][y], NULL);

	x = get_random_number(3);
	y = get_random_number(3);
	while (check[x][y] == 1){
		x = get_random_number(3);
		y = get_random_number(3);
	}
	check[x][y] = 1;

	arr_character[2] = character("Nghia", arr_room[x][y], NULL);

	x = get_random_number(3);
	y = get_random_number(3);
	while (check[x][y] == 1){
		x = get_random_number(3);
		y = get_random_number(3);
	}
	check[x][y] = 1;

	arr_character[3] = character("Cavill", arr_room[x][y], NULL);
	
	x = get_random_number(3);
	y = get_random_number(3);
	while (check[x][y] == 1){
		x = get_random_number(3);
		y = get_random_number(3);
	}
	check[x][y] = 1;

	arr_character[4] = character("Emma", arr_room[x][y], NULL);
	arr_character[5] = character("Player", arr_room[get_random_number(3)][get_random_number(3)], NULL);


	// Connect 1 to 2
	room_exit_east(arr_room[0][0], arr_room[0][1]);
	room_exit_west(arr_room[0][1], arr_room[0][0]);
	// Connect 1 to 4
	room_exit_south(arr_room[0][0], arr_room[1][0]);
	room_exit_north(arr_room[1][0], arr_room[0][0]);

	// Connect 2 to 3
	room_exit_east(arr_room[0][1], arr_room[0][2]);
	room_exit_west(arr_room[0][2], arr_room[0][1]);
	// Connect 2 to 5
	room_exit_south(arr_room[0][1], arr_room[1][1]);
	room_exit_north(arr_room[1][1], arr_room[0][1]);

	// Connect 3 to 6
	room_exit_south(arr_room[0][2], arr_room[1][2]);
	room_exit_north(arr_room[1][2], arr_room[0][2]);

	// Connect 4 to 5
	room_exit_east(arr_room[1][0], arr_room[1][1]);
	room_exit_west(arr_room[1][1], arr_room[1][0]);
	// Connect 4 to 7
	room_exit_south(arr_room[1][0], arr_room[2][0]);
	room_exit_north(arr_room[2][0], arr_room[1][0]);

	// Connect 5 to 6
	room_exit_east(arr_room[1][1], arr_room[1][2]);
	room_exit_west(arr_room[1][2], arr_room[1][1]);
	// Connect 5 to 8
	room_exit_south(arr_room[1][1], arr_room[2][1]);
	room_exit_north(arr_room[2][1], arr_room[1][1]);

	// Connect 6 to 9
	room_exit_south(arr_room[1][2], arr_room[2][2]);
	room_exit_north(arr_room[2][2], arr_room[1][2]);
	
	// Connect 7 to 8
	room_exit_east(arr_room[2][0], arr_room[2][1]);
	room_exit_west(arr_room[2][1], arr_room[2][0]);

	// Connect 8 to 9
	room_exit_east(arr_room[2][1], arr_room[2][2]);
	room_exit_west(arr_room[2][2], arr_room[2][1]);

}

void help_command() {
	printf("List of commands: \n");
	printf("-	help		to see list of commands.\n");
	printf("-	list		to see list of items, characters, and rooms. \n");
	printf("-	look		to see the room character is in and other characters, items in the room. \n");
	printf("-	go 'Direction'	to move character to designated direction. \n");
	printf("-	take 'ITEM'	to pick up item in the current room. \n");
	printf("-	drop 'ITEM'	to drop item in inventory. \n");
	printf("-	Inventory	to check character inventory. \n");
	printf("-	clue 'Character'to move designated character to player. \n");
}

void list_command() {
	printf("List of Items: ");
	printf("Battery, Key, Cola, Laptop, Milk, Iphone.\n");
	
	printf("List of Rooms: ");
	printf("Vault Door, Dining Room, Bath Room, Recreation Center, Security Room, Power Plant, Bed Room, Laboratory, Meeting Hall.\n");

	printf("List of Character: ");
	printf("Jisoo, Jong-Suk, Nghia, Cavill, Emma.\n");
}
void look_command() {
	printf("Character is in %s.\n", arr_character[5]->location->description);

	// Check others room
	if (arr_character[5]->location->north != NULL)
		printf("North Room: %s.\n", arr_character[5]->location->north->description);
	if (arr_character[5]->location->south != NULL)
		printf("South Room: %s.\n", arr_character[5]->location->south->description);
	if (arr_character[5]->location->west != NULL)
		printf("West Room: %s.\n", arr_character[5]->location->west->description);
	if (arr_character[5]->location->east != NULL)
		printf("East Room: %s.\n", arr_character[5]->location->east->description);

	// Check item inside room	
	if (arr_character[5]->location->items != NULL && arr_character[5]->location->items->name != NULL){
		if (arr_character[5]->location->items->name != "Empty")
			printf("%s\n", arr_character[5]->location->items->name);

		struct Item* hold = arr_character[5]->location->items;
		while (hold->next != NULL && hold->next->name != NULL){
			if (hold->next->name != "Empty")
				printf("%s\n", hold->next->name);
			hold = hold->next;
		}
	}
	else printf("Room does not have any item.\n");
	// Check character inside room

	for (int i = 0; i <= 4; i++){
		if (strcmp(arr_character[i]->location->description, arr_character[5]->location->description) == 0)
			printf("Characters: %s.\n", arr_character[i]->name);
	}
}

void Inventory_command() {
	if (arr_character[5]->bag == NULL || arr_character[5]->bag->name == NULL) 
		printf("Your inventory is Empty.\n");
	else{
		if (arr_character[5]->bag->name != "Empty")
			printf("%s\n", arr_character[5]->bag->name);
		struct Item* hold = arr_character[5]->bag;
		while (hold->next != NULL && hold->next->name != NULL) {
			if (hold->next->name != "Empty")
				printf("%s\n", hold->next->name);
			hold = hold->next;
		}
	}	
}

void go_command(char* dir){

	if (strcmp(dir, "north") == 0) {
		if (arr_character[5]->location->north != NULL)
			arr_character[5]->location = arr_character[5]->location->north;
		else printf("Invalid Move.\n");
	}
	else
	if (strcmp(dir, "south") == 0) {
		if (arr_character[5]->location->south != NULL)
			arr_character[5]->location = arr_character[5]->location->south;
		else printf("Invalid Move.\n");
	}
	else
	if (strcmp(dir, "east") == 0) {
		if (arr_character[5]->location->east != NULL)
			arr_character[5]->location = arr_character[5]->location->east;
		else printf("Invalid Move.\n");
	}
	else
	if (strcmp(dir, "west") == 0) {
		if (arr_character[5]->location->west != NULL)
			arr_character[5]->location = arr_character[5]->location->west;
		else printf("Invalid Move.\n");
	}
	else printf("Invalid Input.\n");
 
}

void take_command(char* it){

	struct Item* hold = drop_item(it, arr_character[5]->location->items);	// remove item from room
	arr_character[5]->bag = add_item(arr_character[5]->bag, hold);		// add item to inventory
}

void drop_command(char* it){  

	struct Item* hold = drop_item(it, arr_character[5]->bag);		// remove item from Iventory
	arr_character[5]->location->items = add_item(arr_character[5]->location->items, hold);	// add item to room
}

void clue_command(char* character) {
	for (int i = 0; i <= 4; i++)
		if (strcmp(arr_character[i]->name, character) == 0)
			arr_character[i]->location = arr_character[5]->location;	// summon designated character to player location
}
void main() {
	srand(time(0));
	struct Room* set = init();
	
	// Generate Winning Condition
	int room_x,room_y;
	room_x = get_random_number(3);	// Winning Room
	room_y = get_random_number(3);
	
	int char_pos = get_random_number(5); // Winning avatar

	int item_pos = get_random_number(6); // Winning item

	// Input
	char cmd[20];

	printf("Welcome to the maze.\n");
	help_command();

int check = 0;
int count = 0;
while (check < 10 && count < 3) {
	printf("\nPlease type in your command: ");
	scanf("%s", cmd);
	if (strcmp(cmd, "help") == 0)
		help_command();
	else if (strcmp(cmd, "list") == 0)
		list_command();
	
	else if (strcmp(cmd, "look") == 0)
		look_command();

	else if (strcmp(cmd, "Inventory") == 0)
		Inventory_command();

	else if (strcmp(cmd, "go") == 0){
		char dir[20];
		//printf("Please type in Direction (north, south, east, west): ");
		scanf("%s", dir);
		go_command(dir);
	}

	else if (strcmp(cmd, "take") == 0){
		printf("List of Items to take: \n");
		struct Item* hold = arr_character[5]->location->items;

		if (hold != NULL && hold->name != NULL){
			while (hold != NULL && hold->name != NULL){
				if (hold->name != "Empty")	// HELP ME!!!!!!!!!!!!!!!!!!!!!!
					printf("%s\n", hold->name);
				hold = hold->next;
			}
			printf("\n");

			char it[20];
			
			scanf("%s", it);
			if (arr_character[5]->location->items->name != "Empty")			
				arr_character[5]->location->items = item("Empty", "Empty", arr_character[5]->location->items);	// Create dummy head to remove item from room
			take_command(it);
		} else 
			printf("Cannot take anything. Room is empty.\n");

	}

	else if (strcmp(cmd, "drop") == 0){

		printf("List of Items to drop:\n");
		struct Item* hold = arr_character[5]->bag;
		if (hold != NULL && hold->name != NULL){
			while (hold != NULL && hold->name != NULL){
				if (hold->name != "Empty")
					printf("%s\n", hold->name);
				hold = hold->next;
			}
			printf("\n");

			char it[20];
			//printf("Please type in Item name: ");
			scanf("%s", it);
			if (arr_character[5]->bag->name != "Empty")
				arr_character[5]->bag = item("Empty", "Empty", arr_character[5]->bag);	// Create dummy head to remove item from character
			drop_command(it);
		} else 
			printf("Cannot drop anything. Inventory is empty.\n");
	}

	
	else if (strcmp(cmd, "clue") == 0){
		char cha[20];
		count = 0; 	// winning count
		
		scanf("%s", cha);
		clue_command(cha);
		check  ++;	// increase clue count
		printf("You have guessed %i times.\n", check);

		// check room if match
		if (strcmp(arr_room[room_x][room_y]->description, arr_character[5]->location->description)==0){
			printf("ROOM Match.\n");
			count++;
		}

		// check characters if match

		if (count == 1) 	// if room match then check charecter in room
			for (int i = 0; i < 5; i++)
				if (strcmp(arr_character[i]->location->description, arr_character[5]->location->description) == 0) // check if character in player room
					if (i == char_pos)	// if character is a winning condition
						count++;
		// check moved in character
		if (strcmp(cha, arr_character[char_pos]->name) == 0){
			printf("Character Match.\n");			
			if (count == 1)	// don't need to increase again if we already increase to 2 for character
				count++;
		}


		// check items if match
		struct Item* hold = arr_character[5]->bag;
		
		while (hold != NULL){
			if (hold->name != NULL)
				
				if (strcmp(hold->name, arr_item[item_pos]->name) == 0){
					printf("Item Match.\n");
					count++;
					break;
				}
			hold = hold->next;	
		}
		if (count == 3)
			printf("YOU WIN!\n");
		if (count == 0)
			printf("NO MATCH!\n");
	}

	else printf("Invalid Command");
}
if (check >= 10 && count < 3)
	printf("YOU LOSE!\n");

// Free open variables
for (int i = 0; i < 3; i++)
	for (int j = 0; j <3; j++)
		free(arr_room[i][j]);
for (int i = 0; i < 9; i++)
	free(arr_item[i]);
for (int i = 0; i < 6; i++)
	free(arr_character[i]);

}
