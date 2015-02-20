
CC=gcc
CFLAGS=-g -Wall
IFLAGS=-I../include -I.
LIBS=-lreadline -lncurses 
OBJECTS=mydash.o job.o
CUSTOM_LIBS_DIR=-L../lib
CUSTOM_LIBS=-lmylib


BUILD_NUMBER_FILE=version-number.txt

PROGS=mydash 

all: $(PROGS) 

.c.o:
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

#mydash.o: mydash.c 
#	$(CC) $(CFLAGS) $(IFLAGS) -o $@ mydash.c $(LIBS) -L$(CUSTOM_LIBS_DIR) -l$(CUSTOM_LIBS)

#job.o:	job.c 
#	$(CC) $(CFLAGS) $(IFLAGS) -o $@ job.c $(LIBS)

mydash: $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) -o ../$@  $(OBJECTS) $(LIBS) $(CUSTOM_LIBS_DIR) $(CUSTOM_LIBS)

clean:
	/bin/rm -f *.o $(PROGS) a.out core  *.log
	/bin/rm -fr docs
	/bin/rm -fr docs doxygen.log

dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config >& doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"

