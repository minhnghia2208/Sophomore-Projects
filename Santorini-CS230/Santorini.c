// CompSci 230 - Project 1: Santorini Game
// Name: Pham Minh Nghia - SID: 32507133
// This game allows only 2 players: Human and AI.
// For further description, please read README.txt

#include <stdio.h>

int check_move(int c_pos[], int n_pos[], int op_pos[]) { // check if next move is valid
// c_pos: current position, n_pos: next position, op_pos: opponent position
	int check = 0;
	if (c_pos[0] - n_pos[0] <= 1 && c_pos[0] - n_pos[0] >= -1) {
		if (c_pos[1] - n_pos[1] <= 1 && c_pos[1] - n_pos[1] >= -1) {	
			check = 1;
		}
		else {
			printf("Invalid move: Can only move to adjacent location.\n");
			check = 0;
		}
	}
	else { 				
			printf("Invalid move: Can only move to adjacent location.\n");
			check = 0;
	}
	if (c_pos[0] == n_pos[0] && c_pos[1] == n_pos[1]) {
		printf("Invalid move: Cannot move to the same location.\n");
		check = 0;
	}
	if (n_pos[0] == op_pos[0] && n_pos[1] == op_pos[1]) {
		printf("Invalid move: Cannot move to opponent location.\n");
		check = 0;
	}
	if (n_pos[0] < 0 || n_pos[0] > 5 || n_pos[1] < 0 || n_pos[1] > 5) {
		printf("Invalid move: Cannot move out of bound.\n");
		check = 0;
	}
	return check;
		 
}
 	 
void move(char arr[6][6], char pl[], int c_pos[], int n_pos[], int op_pos[]) {  // this function will move player to designated location
// pl[0]: player type, pl[1]: value underneath, c_pos: current position, n_pos: next position, op_pos: opponent position
	
	// destroy or build up
	int chg = 0;
	char op;
	if (pl[0] == 'A') {
		chg = -1;
		op = 'P';
	}
	else {
		chg = 1;
		op = 'A';
	}


	arr[c_pos[0]][c_pos[1]] = pl[1]; // Change current position to underneath value
	pl[1] = arr[n_pos[0]][n_pos[1]]; // Save next position to value underneath
	arr[n_pos[0]][n_pos[1]] = pl[0]; // Change next position to current player

	// go right
	int i = 1;
	while (n_pos[1] + i < 6) {
		if (arr[n_pos[0]][n_pos[1]+i] != op) { 
			int convert = arr[n_pos[0]][n_pos[1]+i] - '0';
			if (chg == 1 && convert < 4) {
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]][n_pos[1]+i] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}

	// go down
	i = 1;
	while (n_pos[0] + i < 6) {
		if (arr[n_pos[0]+i][n_pos[1]] != op) { 
			int convert = arr[n_pos[0]+i][n_pos[1]] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]+i][n_pos[1]] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}
	
	// go left
	i = 1;
	while (n_pos[1] - i >= 0) {
		if (arr[n_pos[0]][n_pos[1]-i] != op) { 
			int convert = arr[n_pos[0]][n_pos[1]-i] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]][n_pos[1]-i] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}

	// go up
	i = 1;
	while (n_pos[0] - i >= 0) {
		if (arr[n_pos[0]-i][n_pos[1]] != op) { 
			int convert = arr[n_pos[0]-i][n_pos[1]] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]-i][n_pos[1]] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}
	
	// go SE
	i = 1;
	while (n_pos[0] + i < 6 && n_pos[1] + i < 6) {
		if (arr[n_pos[0]+i][n_pos[1]+i] != op) { 
			int convert = arr[n_pos[0]+i][n_pos[1]+i] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			} 
			arr[n_pos[0]+i][n_pos[1]+i] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}

	// go NE
	i = 1;
	while (n_pos[0] + i < 6 && n_pos[1] - i >= 0) {
		if (arr[n_pos[0]+i][n_pos[1]-i] != op) { 
			int convert = arr[n_pos[0]+i][n_pos[1]-i] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]+i][n_pos[1]-i] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}

	// go SW
	i = 1;
	while (n_pos[0] - i >= 0 && n_pos[1] + i < 6) {
		if (arr[n_pos[0]-i][n_pos[1]+i] != op) { 
			int convert = arr[n_pos[0]-i][n_pos[1]+i] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]-i][n_pos[1]+i] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}

	// go NW
	i = 1;
	while (n_pos[0] - i >= 0 && n_pos[1] - i >= 0) {
		if (arr[n_pos[0]-i][n_pos[1]-i] != op) { 
			int convert = arr[n_pos[0]-i][n_pos[1]-i] - '0';
			if (chg == 1 && convert < 4){
				convert = convert + chg;
			}
			if (chg == -1 && convert > 0) {
				convert = convert + chg;
			}
			arr[n_pos[0]-i][n_pos[1]-i] = '0' + convert;
		}
		else {
			i = 100;
		}
		i++;
	}

}

int winner(char arr[6][6]) { // check winner condition
	int P = 0;
	int A = 0;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			if (arr[i][j] == '0'){
				A++;
			} 
			if (arr[i][j] == '4'){
				P++;
			}
		}
	}
	if (A >= 10) {
		printf("AI win with %i points.\n", A);
		return 1;
	} 
	if (P >= 10) {
		printf("Player win with %i points.\n", P);
		return 1;
	}
	return 0;
}
void print_board(char arr[6][6]) {
	for (int i = 0; i <= 6; i++) {
		if (i ==0){
			printf("   ");
		} else { 
			printf("%i  ", i);
		}
	}
	printf("\n");
	for (int i = 0; i < 6; i++) {
		printf("%i  ", i+1);
		for (int j = 0; j < 6; j++) {
			printf("%c  ", arr[i][j]);
		}
		printf("\n");
	}
}
int check_AI(int c_pos[], int n_pos[], int op_pos[]) { // check if next move is valid
// c_pos: current position, n_pos: next position, op_pos: opponent position
	int check = 0;
	if (c_pos[0] - n_pos[0] <= 1 && c_pos[0] - n_pos[0] >= -1) {
		if (c_pos[1] - n_pos[1] <= 1 && c_pos[1] - n_pos[1] >= -1) {	
			check = 1;
		}
		else {
			check = 0;
		}
	}
	if (n_pos[0] == op_pos[0] && n_pos[1] == op_pos[1]) {
		check = 0;
	}
	if (n_pos[0] < 0 || n_pos[0] > 5 || n_pos[1] < 0 || n_pos[1] > 5) {
		check = 0;
	}
	return check;
}
void AI(char arr[6][6], int AI_n[], int c_pos[], int op_pos[]) {
	int n_pos[] = {100, 100};
	int max = 0;
	for (int k = -1; k <= 1; k++) {
		for (int j = -1; j <= 1; j++) {
			if (k != 0 || j != 0) {
				int count = 0;
				n_pos[0] = c_pos[0] + k;
				n_pos[1] = c_pos[1] + j;
				if (check_AI(c_pos, n_pos, op_pos)) {	
				// go right
				int i = 1;
				while (n_pos[1] + i < 6) {
					if (arr[n_pos[0]][n_pos[1]+i] != 'P') { 
						if (arr[n_pos[0]][n_pos[1]+i] != '0') {
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
				// go down
				i = 1;
				while (n_pos[0] + i < 6) {
					if (arr[n_pos[0]+i][n_pos[1]] != 'P') { 
						if (arr[n_pos[0]+i][n_pos[1]] != '0'){
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
				// go left
				i = 1;
				while (n_pos[1] - i >= 0) {
					if (arr[n_pos[0]][n_pos[1]-i] != 'P') { 
						if (arr[n_pos[0]][n_pos[1]]-i != '0') {
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
				// go up
				i = 1;
				while (n_pos[0] - i >= 0) {
					if (arr[n_pos[0]-i][n_pos[1]] != 'P') { 
						if (arr[n_pos[0]-i][n_pos[1]] != '0') {
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
				// go SE
				i = 1;
				while (n_pos[0] + i < 6 || n_pos[1] + i < 6) {
					if (arr[n_pos[0]+i][n_pos[1]+i] != 'P') { 
						if (arr[n_pos[0]+i][n_pos[1]+i] != '0') {
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
				// go NE
				i = 1;
				while (n_pos[0] + i < 6 && n_pos[1] - i >= 0) {
					if (arr[n_pos[0]+i][n_pos[1]-i] != 'P') { 	
						if (arr[n_pos[0]+i][n_pos[1]-i] != '0'){
							count++;
						}
					}
					else {i = 100;}
					i++;
				}

				// go SW
				i = 1;
				while (n_pos[0] - i >= 0 && n_pos[1] + i < 6) {
					if (arr[n_pos[0]-i][n_pos[1]+i] != 'P') { 
						if (arr[n_pos[0]-i][n_pos[1]+i] != '0'){
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
			
				// go NW
				i = 1;
				while (n_pos[0] - i >= 0 && n_pos[1] - i >= 0) {
					if (arr[n_pos[0]-i][n_pos[1]-i] != 'P') { 
						if (arr[n_pos[0]-i][n_pos[1]-i] != '0'){
							count++;
						}
					}
					else {i = 100;}
					i++;
				}
				}
				if (count > max) {
					max = count;
					AI_n[0] = n_pos[0];
					AI_n[1] = n_pos[1];
				}
				}
			}
		}
}	
			
	
void main() {
	char arr[6][6];
	for (int i = 0; i < 6; i++) {	// Initialize Board
		for (int j = 0; j < 6; j++) {
			arr[i][j] = '2';
		}
	}
	print_board(arr);
	int check = 0;
	int c_pos[2], n_pos[2] = {100, 100};
	char pl[2];

	printf("Welcome to Santorini\n");
	while (check == 0) {
		printf("Choose your starting position (1-6) (row column): ");
		scanf("%i %i", &c_pos[0], &c_pos[1]);
		c_pos[0]--;
		c_pos[1]--;
		if (c_pos[0] < 0 || c_pos[0] > 5 || c_pos[1] < 0 || c_pos[1] > 5) {
			printf("Invalid location.\n");		
			check = 0;
		} else { check = 1; }
	}
	arr[c_pos[0]][c_pos[1]] = 'P';
	pl[0] = 'P';
	pl[1] = '2';
	
	// Start point for AI
	int AI_c[2];
	int AI_n[2] = {100,100};
	if (c_pos[1] <= 2) {
		AI_c[0] = c_pos[0];
		AI_c[1] = c_pos[1]+1;
	} 
	else { 
		AI_c[0] = c_pos[0];
		AI_c[1] = c_pos[1]-1;
	}
	arr[AI_c[0]][AI_c[1]] = 'A';
	print_board(arr);


	char plA[] = {'A','2'};
	while (!winner(arr)) {
		check = 0;
		while (!check){
			printf("Choose your next location (1-6) (row column): ");
			scanf("%i %i", &n_pos[0], &n_pos[1]);
			n_pos[0]--;
			n_pos[1]--;
			check = check_move(c_pos, n_pos, AI_c);
		}
		move(arr, pl, c_pos, n_pos, AI_c); 		
		c_pos[0] = n_pos[0];
		c_pos[1] = n_pos[1];

	
		AI(arr, AI_n, AI_c, c_pos);
		move(arr, plA, AI_c, AI_n, c_pos);
	
		AI_c[0] = AI_n[0];
		AI_c[1] = AI_n[1];
		printf("AI move to: %i %i\n", AI_c[0]+1, AI_c[1]+1); 
		print_board(arr);	
	}
		
}	
