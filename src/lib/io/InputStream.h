#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <sys/types.h>

class InputStream
{
	public:
		virtual void read (size_t n, char *data) = 0;
};

#endif
