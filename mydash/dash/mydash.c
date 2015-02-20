
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include <List.h>

#include "job.h"

int parseString(char* line, char** args);
void execute (char** args, int background);
void changeDirectory(char** args);
void showVersion();

int main() {
	
	
	
	char *line;
	char *DASH_PROMPT = "mydash>";
		
	char *args[2049];
	int backgroundCheck = 0;	
	
	//ListPtr jobList = createList(
	
	using_history();
	while ((line=readline(DASH_PROMPT))) {
		if (line == NULL) break;
		if (*line)
		{
			printf("%s\n",line);
			add_history(line);
			if (line[strlen(line)-1] == '&'){
				backgroundCheck = 1;
				
				line[strlen(line) - 1] = '\0';
			}
			parseString(line,args);
			if (strcmp(args[0], "exit") == 0)
				break;
			if (strcmp(args[0], "cd") == 0){
				changeDirectory(args);
				free(line);
				continue;
			}		
			if (strcmp(args[0], "-v") == 0){
				showVersion(args);
				free(line);
				continue;
			}
			execute(args, backgroundCheck);
			free(line);
			backgroundCheck = 0;
		}

	
	}
	//int i;
	//for (i = 0; i < 2048; i++)
	//{
	//	if (args[i]) free(args[i]);
	//}
	//free(args);
	free(line);
	exit(0);

}

void changeDirectory(char** args)
{

	if (args[1]){
		chdir(args[1]);
	}
	else {
		struct passwd *pw = getpwuid(getuid());
		const char *homedir = pw->pw_dir;
		chdir(homedir);
	}
	
}

void showVersion(char** args)
{
	FILE *fileStream;
	fileStream = fopen("version-number.txt", "r");
	char fileText[100];
	fgets (fileText, 100, fileStream);
	fclose(fileStream);
	
	printf("Version Number: %s",fileText);

}

int parseString(char* linea, char** argz){
	
	int count = -1;
	int isAnArgument;

	if (!linea) return 0;
	
	while (*linea != '\0' && count < 2048)
	{
		isAnArgument = 0;
		while (*linea == ' ' || *linea == '\n') 
		{
			*linea++ = '\0';
		}
		*argz++ = linea;
		
		while (*linea != '\0' && *linea != ' ' && *linea != '\n')
		{
			isAnArgument = 1;
			linea++;
		}
		if (isAnArgument) count++;
		else *argz-- = '\0';
	}
	//printf("%d arguments",count);
	*argz = '\0';
	return count;	
}

void execute (char** args, int background){
	
	pid_t	pid;
	int	status;
	
	if ((pid = fork()) < 0) 
	{
		exit(1);
	}
	else if (pid == 0) 
	{
		if (execvp(*args, args) < 0)
		{
			printf("Error: execvp failed\n");
			exit(1);
		}
	}
	else 
	{
		if (!background)
			while (wait(&status) != pid);
	}
	
}
