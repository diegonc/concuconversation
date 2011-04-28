#include <File.h>

File::File (std::string &path, int flags)
{
}

File::File (std::string &path, int flags, mode_t mode)
{
}

File::File (const char *path, int flags)
{
}

File::File (const char *path, int flags, mode_t mode)
{
}

File::~File()
{
	if (fd != -1)
		close (fd);
}

int File::write (size_t n, const char *data)
{
	return ::write (fd, data, n);	
}
