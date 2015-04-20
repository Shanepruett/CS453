#ifndef __BOOGA_H
#define __BOOGA_H

#ifndef BOOGA_MAJOR
#define BOOGA_MAJOR 0
#endif

#ifndef BOOGA_NR_DEVS
#define BOOGA_NR_DEVS 4
#endif

#define TYPE(dev)	(MINOR(dev) >> 4)	// high nibble
#define NUM(dev)	(MINOR(dev) & 0xf)	// now nibble


struct booga_dev {
    char *data;
    unsigned minor;
};
typedef struct booga_dev booga_dev;

extern booga_dev Booga_Dev;


#endif
