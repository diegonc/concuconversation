#include <FifoOutputStream.h>

FifoOutputStream::FifoOutputStream (std::string &path)
	: File (path, O_WRONLY)
{
}
