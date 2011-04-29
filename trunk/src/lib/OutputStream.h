#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

#include <sys/types.h>

class OutputStream
{
	public:
		virtual void write (size_t n, const char *data) = 0;
};

#endif
