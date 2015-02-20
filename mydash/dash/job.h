#ifndef JOB_H
#define JOB_H

#include <common.h>

struct job
{
        int jobNumber;
        pid_t pid;
        char* command;
};

typedef struct job Job;
typedef struct job *JobPtr;

typedef Boolean (*equal) (const void *object, const void *other);
typedef char * (*toString) (const void *jobObj);
typedef void (*freeJ) (const void *jobObj);


JobPtr createJob(int number, pid_t id, char* comm); 
int jobDone(const void *jobObj); 
void printJobStatus(const void *jobObj);
void printJob(const void *jobObj);
void freeJob(const void *jobObj);
char *jobToString(const void *jobObj);
Boolean jobEqual(const void *object, const void *other);








#endif
