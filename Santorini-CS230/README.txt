Name: Pham Minh Nghia
SID: 32507133

Project 1 progress:
Santorini game is a turn-base game. The game allows you to play against an AI. 
For more information about the game please visit: https://docs.google.com/document/d/1KPE4H0HRjvO59zdKGDExr8pozJQXnieaf2wYykdtmBA/edit#
Youtube Link: https://www.youtube.com/watch?v=jcwreTM-WMA&feature=youtu.be  

The program can be optimized to be shorter. However, due to technical difficulties, the actually length is 451 lines.

The most important part is Move function. The function will take 5 parameters: char arr, char pl[], int c_pos[], int n_pos[], int op_pos[].
arr is the board. 
pl is to keep track of player type (P or A) and also value underneath the player type; so when we move the player,
we can insert the original value back, and hold new value from new location.
c_pos is to hold current player location.
n_pos is to hold next location.
op_pos is to hold opponent location so we won't have overlapse situation.
This function moves the player from c_pos to n_pos, replaces player type (P or A) into underneath value, and increase (P) or decrease (A)
value around player new location.
To increase or decrease value, the program will go from the player location and go outward and +1 or -1. If it meet opponent location, 
the program won't go further. 

The AI method is second important. The AI method is a modified version of Move method. To find the new optimal location, it will start
at the AI current location. Then, it will move outward, increase count for each non '0' tile. It then choose the tile which has the max
count value. 

The check_move method is quite straight forward. It will check if the move is valid.
The check_AI method is a copy of the check_move. However, it will not inform errors like check_move. This method is used only for AI

The winner and print_board methods are straight forward and can be easily understood.

For the main method. It first initialize the board, and variables. Then, it would ask for input value. The process is straight forward.
However, inside main method, there is a "Start point for AI" section. This section does what it is called: Find the starting point.
It is not complicated. The starting point will either be on the left or on the right of the player location. Because the AI will win most
of the time, the program will not need to find the optimal starting point.
