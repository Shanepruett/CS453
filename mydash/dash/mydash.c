
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <List.h>
#include <Node.h>
#include "git_version.h"
#include "job.h"
#include "mydash.h"


int main()
{
    char *line;
    char *DASH_PROMPT = "mydash>";

    char *args[2049];
    int backgroundCheck = 0;


    char *unmodLine = "";

    ListPtr jobList = createList(&jobEqual, &jobToString, &freeJob);

    using_history();
    while ((line = readline(DASH_PROMPT))) {
	if (line == NULL){
		break;	   
	}
        printDoneJobs(jobList);
	if (*line) {
	    add_history(line);
	    if (line[strlen(line) - 1] == '&') {
		backgroundCheck = 1;

		unmodLine = malloc(sizeof(char) * (strlen(line) + 1));
		strcpy(unmodLine, line);

		line[strlen(line) - 1] = '\0';
	    }
	    parseString(line, args);
	    if (strcmp(args[0], "exit") == 0)
		break;
	    if (strcmp(args[0], "cd") == 0) {
		changeDirectory(args);
		free(line);
		continue;
	    }
	    if (strcmp(args[0], "-v") == 0) {
		printf("Version: %s \n", git_version());
		free(line);
		continue;
	    }
	    if (strcmp(args[0], "jobs") == 0) {
		printAllJobs(jobList);
	    }
	    execute(args, backgroundCheck, unmodLine, jobList);

	    free(line);
	    backgroundCheck = 0;
	}


    }

    freeList(jobList);
    free(line);
    return(0);
}


void printDoneJobs(ListPtr list)
{
    if (list->size == 0)
	return;

    NodePtr temp = list->head;

    while (temp->next != list->head) {
	if (jobDone(temp->obj)) {
	    printJobStatus(temp->obj);
	    temp = temp->prev;
	    freeNode(removeNode(list, temp->next), list->freeObject);
	}
	temp = temp->next;
    }

    if (jobDone(temp->obj)) {
	printJobStatus(temp->obj);
	freeNode(removeNode(list, temp), list->freeObject);
    }

}



void printAllJobs(ListPtr list)
{
    if (list->size == 0)
	return;
    NodePtr temp = list->head;

    while (temp->next != list->head) {
	printJobStatus(temp->obj);
	temp = temp->next;

    }

    printJobStatus(temp->obj);

}


void changeDirectory(char **args)
{

    if (args[1]) {
	chdir(args[1]);
    } else {
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	chdir(homedir);
    }

}


int parseString(char *linea, char **argz)
{
    //printf("made it in to parseString\n");
    int count = -1;
    int isAnArgument;

    if (!linea)
	return 0;

    while (*linea != '\0' && count < 2048) {
	isAnArgument = 0;
	while (*linea == ' ' || *linea == '\n') {
	    *linea++ = '\0';
	}
	*argz++ = linea;

	while (*linea != '\0' && *linea != ' ' && *linea != '\n') {
	    isAnArgument = 1;
	    linea++;
	}
	if (isAnArgument)
	    count++;
	else
	    *argz-- = '\0';
    }
    //printf("%d arguments",count);
    *argz = '\0';
    return count;
}

void execute(char **args, int background, char *unmodLine, ListPtr list)
{

    //printf("made it in to execute\n");

    pid_t pid;
    int status;


    if ((pid = fork()) < 0) {
	exit(1);
    } else if (pid == 0) {
	if (execvp(*args, args) < 0) {
	    printf("Error: execvp failed\n");
	    exit(1);
	}
    } else {
	if (!background) {
	    while (wait(&status) != pid);
	} else {
	    //printf("made it to makingjob\n");             
	    //job newJob = { (list->size == 0) ? 1 : ((job*) (list->tail->obj))->jobNumber + 1 , 
	    //              pid, 
	    //              unmodLine };
	    int num =
		(list->size ==
		 0) ? 1 : ((JobPtr) (list->tail->obj))->jobNumber + 1;
	    //printf("made number\n");
	    JobPtr tempJob = createJob(num, pid, unmodLine);
	    //printf("made job\n");         
	    NodePtr node = createNode(tempJob);
	    //printf("made node\n");
	    addAtRear(list, node);
	    char *tempString = jobToString(tempJob);
	    printf("%s\n", tempString);
	    free(tempString);
	}
    }

}
