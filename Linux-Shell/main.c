#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>


int wordCounter(char str[]){		// To count the number of tokens in the user's command
	int i = 0, wrdCnt = 0;
	while(str[i] != '\0'){
		if(str[i] == ' ')
			wrdCnt++;
		i++;
	}
	return wrdCnt+1;
}


void signalHandler(int signal)		// To handle the SIGCHLD signal to indicate every child termination
{
	FILE *fp;
	fp = fopen("terminated.txt", "a");
	char str[] = "Child is terminated!\n";
	
	if (signal==SIGCHLD) {
		fprintf(fp, "%s\n", str);
	}
} 

int main(){

	printf("\n**Welcome to 6297 Shell**\n");
	FILE *fp;
	fp = fopen("terminated.txt", "w");
	signal(SIGCHLD, signalHandler);
	while(1){
		int i = 0, wrdCnt = 0, exitCheck, numOfArgs;
		char command[50];
	        memset(command, 0, strlen(command));
	        printf("\nShell>> ");
		scanf("%[^\n]%*c", command);
		numOfArgs = wordCounter(command);
	
		if(numOfArgs == 1){
			char *args[] = {command, NULL};
		
			if(strcmp(command, "exit") == 0){
				fclose(fp);
				exit(0);
			}
			else{
				pid_t pid = fork();
				int status;
				if(pid == 0){
					execvp(args[0], args); 	// Direct to desired command file
				}
				else if(pid > 0){
					waitpid(pid, &status, WUNTRACED|WCONTINUED);	// To wait for specific child
				}
				else{ 
					printf("Error in command exection\n");
				}
			}
		}	
		else if(numOfArgs == 2){
			char *command0;
			char *command1;
		
			command0 = strtok(command, " ");
			command1 = strtok(NULL, " ");
			
			char *args[] = {command0, command1, NULL};
			if(strcmp(command1, "&") == 0){
				strcpy(args[0], command0);
				args[1] = NULL;
			}
			pid_t pid = fork();
			int status;
			if(pid == 0){
				execvp(args[0], args);		// Direct to desired command file
			}
			else if(pid > 0){
				if(strcmp(command1, "&") != 0){
					waitpid(pid, &status, WUNTRACED|WCONTINUED);	// To wait for specific child
				}
			}
			else{
				printf("Error in command execution\n");
			}
		}
		else{
			int i=0;
			char *args[10];
			char *token = strtok(command, " ");
			while(token != NULL){
				args[i] = token;
				i++;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			pid_t pid = fork();
			int status;
			if(pid == 0){
				execvp(args[0], args);
			}
			else if(pid > 0){
				waitpid(pid, &status, WUNTRACED|WCONTINUED);	// To wait for specific child
			}
			else{
				printf("Error in command execution\n");
			}
		}
	}
}
