#ifndef FIFOINPUTSTREAM_H
#define FIFOINPUTSTREAM_H

#include <string>

#include <io/InputStream.h>
#include <system/File.h>

class FifoInputStream : public InputStream
{
	private:
		File fifo;

	public:
		FifoInputStream (const std::string &path);

		void read (size_t n, char *data);
};

#endif
