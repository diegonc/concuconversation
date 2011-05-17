#include <stdexcept>

#include <assert.h>
#include <errno.h>

#include <io/FifoInputStream.h>
#include <system/System.h>
#include <iostream>


log4cxx::LoggerPtr FifoInputStream::logger (log4cxx::Logger::getLogger ("FifoInputStream"));

FifoInputStream::FifoInputStream (const std::string &path)
	: fifo (path, O_RDONLY)
{
}

void FifoInputStream::read (size_t n, char *data)
{
	LOG4CXX_DEBUG(logger,"faltan ?" << n );
	ssize_t ret;
	int attempts = 5;
	while (attempts-- > 0 && n > 0) {
		do {
			ret = fifo.read (n, data);

			if (ret == -1 && errno != EINTR){
				throw SystemErrorException();
			}
			LOG4CXX_DEBUG(logger,"ret " << ret  << "errno " << errno);

			n -= ret;
			data += ret;
		} while (n > 0 && ret != 0 );
	}

	if (n > 0){
		LOG4CXX_DEBUG(logger,"faltan ?" << n );
		throw std::runtime_error (std::string("TODO: crear excepcion. (") + __PRETTY_FUNCTION__ + ")");
	}
}
