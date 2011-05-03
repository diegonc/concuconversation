#include <stdexcept>

#include <assert.h>
#include <errno.h>

#include <io/FifoInputStream.h>
#include <system/System.h>

FifoInputStream::FifoInputStream (const std::string &path)
	: fifo (path, O_RDONLY)
{
}

void FifoInputStream::read (size_t n, char *data)
{
	ssize_t ret;
	int attempts = 5;

	while (attempts-- > 0 && n > 0) {
		do {
			ret = fifo.read (n, data);

			if (ret == -1 && errno != EINTR)
				throw SystemErrorException();

			n -= ret;
			data += ret;
		} while (n > 0 && ret != 0 );
	}

	if (n > 0)
		throw std::runtime_error (std::string("TODO: crear excepcion. (") + __PRETTY_FUNCTION__ + ")");
}
