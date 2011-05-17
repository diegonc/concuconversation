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
	LOG4CXX_DEBUG(logger, "leyendo " << n << " bytes." );
	ssize_t ret;
	int attempts = 5;
	
	do {
		ret = fifo.read (n, data);
		LOG4CXX_DEBUG(logger, "..leidos: " << ret
			<< "(errno: " << errno << ")");

		if (ret == -1 && errno != EINTR){
			throw SystemErrorException();
		}

		n -= ret;
		data += ret;
	} while (n > 0 && ret != 0 );

	if (n > 0 && ret == 0) {
		/* eof */
		LOG4CXX_DEBUG(logger,"..todos los clientes salieron");
		throw std::runtime_error (std::string("TODO: crear excepcion. (") + __PRETTY_FUNCTION__ + ")");
	}
}
