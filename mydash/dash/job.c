
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "job.h"


void freeJob(job jobObj)
{

	free(jobObj.command);

}


void printJob(job jobObj)
{
	printf("[%d] %d %s", jobObj.jobNumber, (int) jobObj.pid, jobObj.command); 

}

char *jobToString(job jobObj)
{
	char* theString = "";

	sprintf(theString,"[%d] %d %s", jobObj.jobNumber, (int) jobObj.pid, jobObj.command); 

	return theString;
}

int jobEqual(job this, job other)
{
	return this.pid == other.pid;
	
}


void printJobStatus(job jobObj)
{
	
	if (jobDone(jobObj)){
		
		printf("[%d] Done %s", jobObj.jobNumber, jobObj.command); 
	} 
	else {

		printf("[%d] Running %s", jobObj.jobNumber, jobObj.command); 
	}

}

int jobDone(job jobObj){
	int *statusPtr = 0;
	waitpid(jobObj.pid, statusPtr, WNOHANG); 	
	return WIFEXITED(statusPtr);
}

