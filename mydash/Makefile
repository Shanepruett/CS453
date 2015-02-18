
CC=gcc
CFLAGS= -g   -Wall 
LIBS=-lreadline -lncurses 
OBJECTS=test-readline.o
CUSTOM_LIBS_DIR=./lib/
CUSOM_LIBS=mylib

BUILD_NUMBER_FILE=version-number.txt

PROGS=test-readline loop 

all: $(PROGS) dox library testcode

loop: loop.o
	$(CC) $(CFLAGS) -o $@  $<

test-readline: $(OBJECTS) $(BUILD_NUMBER_FILE)
	$(CC) $(CFLAGS) $(BUILD_NUMBER_LDFLAGS) -o mydash  $< $(LIBS) -L$(CUSTOM_LIBS_DIR) -l$(CUSTOM_LIBS)

include buildnumber.mak


dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config > doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"


clean:
	/bin/rm -f *.o $(PROGS) a.out core  *.log
	/bin/rm -fr docs
	cd libsrc; make clean
	cd testsuite; make clean
	/bin/rm -fr docs doxygen.log


library:        
	cd libsrc; make install 

testcode:
	cd testsuite; make


dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config >& doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"

