/*Author: Lindsay Duncan, UIN: 676814251, ldunc4@uis.edu
  Compile: gcc project1.c -o project1
  Description: This program takes a command line argument to determine the number of commands
  to be processed, the commands given are run on a child process until the number of commands
  has been met or the user quits.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_CMD_NUM 10		//max number of commands permitted
#define MAX_CMD_LENGTH 40	//max length per each command

int main(int argc, char *argv[]){
	int i, command_num, process;
	char command[MAX_CMD_LENGTH];
	
	//check for correct number of arguments
	if (argc != 2){
		printf("The command line has %d arguments excluding the command.\n", argc - 1);
		printf("Requires one argument.\n");
		return -1;
	}
	
	command_num = atoi(argv[1]); 	//convert string input to int
	
	//check for appropriate number of commands (between 1 and 10)
	if(command_num < 1 || command_num > MAX_CMD_NUM){
		printf("Usage: integer between 1 and 10, inclusive.\n");
		
	}
	
	else{
		for(i = 0; i < command_num; i++){
			printf("COMMAND-> ");
			fflush(stdout);			
			scanf("%s", command);
			
			//terminate if "quit" is input
			if(strcmp(command, "quit") == 0){
				i = command_num;
			}
			
			else{
				process = fork();
				
				if (process < 0){
					//fork failed
					fprintf(stderr, "fork failed\n");
					exit(1);
				}
				
				else if(process == 0){
					//child process										
					char *myargs[2];
					myargs[0] = (strdup(command));	//copy command to array
					myargs[1] = NULL;
					execvp(myargs[0], myargs);	//run command program
				}
				
				else{
					//parent process
					fflush(stdout);
					int wc = wait(NULL);	//wait for child to complete										
				}
			}				
		}
	}	
	return 0;	
}

