#ifndef FILE_H
#define FILE_H

#include <string>

#include <unistd.h>

class File
{
	private:
		int fd;

	public:
		File (std::string &path, int flags);
		File (std::string &path, int flags, mode_t mode);
		File (const char *path, int flags);
		File (const char *path, int flags, mode_t mode);
		~File ();
};

#endif
