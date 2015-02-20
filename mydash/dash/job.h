#ifndef JOB_H
#define JOB_H


typedef struct job
{
        int jobNumber;
        pid_t pid;
        char* command;
}job;

int jobDone(job jobObj); 
void printJobStatus(job jobObj);
void printJob(job jobObj);
void freeJob(job jobObj);
char *jobToString(job jobObj);
int jobEqual(job this, job other);







#endif
