#ifndef CYCLIC_BUFFER_H
#define CYCLIC_BUFFER_H

struct buffer
{
	volatile int first;
	volatile int last; 
};

#endif
