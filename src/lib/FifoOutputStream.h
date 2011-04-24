#ifndef FIFOOUTPUTSTREAM_H
#define FIFOOUTPUTSTREAM_H

#include <string>

#include <File.h>

class FifoOutputStream : public File
{
	public:
		FifoOutputStream (std::string &path);
};

#endif
