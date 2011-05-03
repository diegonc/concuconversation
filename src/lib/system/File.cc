#include <system/File.h>

File::File (const std::string &path, int flags)
{
	inicializar (path.c_str(), flags, 0);
}

File::File (const std::string &path, int flags, mode_t mode)
{
	inicializar (path.c_str(), flags, mode);
}

File::File (const char *path, int flags)
{
	inicializar (path, flags, 0);
}

File::File (const char *path, int flags, mode_t mode)
{
	inicializar (path, flags, mode);
}

void File::inicializar (const char *path, int flags, mode_t mode)
{
	fd = open (path, flags, mode);
	/* TODO: errores */
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

int File::read (size_t n, char *data)
{
	return ::read (fd, data, n);	
}
