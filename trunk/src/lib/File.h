#ifndef FILE_H
#define FILE_H

#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

class File
{
	private:
		int fd;

	public:
		File (const std::string &path, int flags);
		File (const std::string &path, int flags, mode_t mode);
		File (const char *path, int flags);
		File (const char *path, int flags, mode_t mode);
		~File ();

		int write (size_t n, const char *data);
};

#endif
