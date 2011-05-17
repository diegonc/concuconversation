#ifndef FIFOINPUTSTREAM_H
#define FIFOINPUTSTREAM_H

#include <string>

#include <io/InputStream.h>
#include <system/File.h>
#include <log4cxx/logger.h>

class FifoInputStream : public InputStream
{
	private:
		static log4cxx::LoggerPtr logger;
		File fifo;

	public:
		FifoInputStream (const std::string &path);

		bool read (size_t n, char *data);
};

#endif
