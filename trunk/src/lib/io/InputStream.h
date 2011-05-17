#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <sys/types.h>

class InputStream
{
	public:
		virtual bool read (size_t n, char *data) = 0;
};

#endif
