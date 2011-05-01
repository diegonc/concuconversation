#include <stdexcept>

#include <assert.h>
#include <errno.h>

#include <io/FifoOutputStream.h>
#include <system/System.h>

FifoOutputStream::FifoOutputStream (const std::string &path)
	: fifo (path, O_WRONLY)
{
}

void FifoOutputStream::write (size_t n, const char *data)
{
	ssize_t written;
	int attempts = 5;

	while (attempts-- > 0 && n > 0) {
		do {
			assert (n > 0);
			written = fifo.write (n, data);

			if (written == -1 && errno != EINTR)
				throw SystemErrorException();

			n -= written;
			data += written;
		} while (n > 0 && written != 0 );
	}

	if (n > 0)
		throw std::runtime_error (std::string("TODO: crear excepcion. (") + __PRETTY_FUNCTION__ + ")");
}
