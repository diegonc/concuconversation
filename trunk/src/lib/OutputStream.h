#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

class OutputStream
{
	public:
		virtual void write (size_t n, const char *data) = 0;
};

#endif
