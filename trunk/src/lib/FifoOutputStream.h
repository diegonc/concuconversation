#ifndef FIFOOUTPUTSTREAM_H
#define FIFOOUTPUTSTREAM_H

#include <string>

#include <File.h>
#include <OutputStream.h>

class FifoOutputStream : public OutputStream
{
	private:
		File fifo;

	public:
		FifoOutputStream (const std::string &path);

		void write (size_t n, const char *data);
};

#endif
