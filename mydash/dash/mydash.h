#ifndef MYDASH_H
#define MYDASH_H

#include <List.h>



int parseString(char *line, char **args);


void execute(char **args, int background, char *unmodLine, ListPtr list);


void changeDirectory(char **args);


void printDoneJobs(ListPtr list);


void printAllJobs(ListPtr list);


#endif
