#ifndef FIFOOUTPUTSTREAM_H
#define FIFOOUTPUTSTREAM_H

#include <string>

#include <io/OutputStream.h>
#include <system/File.h>
#include <log4cxx/logger.h>

class FifoOutputStream : public OutputStream
{
	private:
		static log4cxx::LoggerPtr logger;
		File fifo;

	public:
		FifoOutputStream (const std::string &path);

		void write (size_t n, const char *data);
};

#endif
