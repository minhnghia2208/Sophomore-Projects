#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
bool check_rep(char reply[]){	// check reply if it is Math (return 1) or Flag (return 0)
	char flag[2048];
	
	strncpy(flag, reply+6, 6);
	flag[6] = '\0';
	if (strcmp(flag, "STATUS") == 0)
		return 1;
	else return 0;
}
int math(char reply[]){		// Do the math
	char num1_c[2048];
	char num2_c[2048];
	int num1_i, num2_i;
	char op;
	int check = 0;

	for (int i = 13; i <= strlen(reply); i++) {
		
		if (reply[i] == ' ' && check == 0) {
			strncpy(num1_c, reply+13, i-12);
			num1_c[i-12] = '\0';
			num1_i = atoi(num1_c);

			op = reply[i+1];

			check = i + 3;
		}
		if (reply[i] == '\n'){
			i++;
			strncpy(num2_c, reply+check, i-check);
			num2_c[i-check] = '\0';
			num2_i = atoi(num2_c);
		}
	}
	if (op == '+')
		return num1_i + num2_i;
	if (op == '-')
		return num1_i - num2_i;
	if (op == '*')
		return num1_i * num2_i;
	if (op == '/')
		return num1_i / num2_i;
}
int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;	
	char server_reply[2048];
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr(argv[3]);
	server.sin_family = AF_INET;
	server.sin_port = htons( atoi(argv[2]) );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}
        // A warm greeting for initial contact
        char message[2048] = "cs230 HELLO ";
	strcat(message, argv[1]);
	strcat(message, "\n");
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
        	puts("Send failed");
                return 1;
        }
        
	for (int i = 0; i <= 2000; i++) {

		//Receive a reply from the server
	        if( recv(socket_desc, server_reply , 2048 , 0) < 0)
	                puts("recv failed");

	     	puts(server_reply);
		if (check_rep(server_reply)){
			int result = math(server_reply);
			sprintf(server_reply, "%d", result);
			char script[2048] = "cs230 ";
			strcat(script, server_reply);
			strcat(script, "\n");
			puts(script);
			if (send(socket_desc, script, strlen(script), 0) < 0)
				puts("Send failed");
		
		
		}
		else return 0;
	}

	close(socket_desc);
	return 0;
}
