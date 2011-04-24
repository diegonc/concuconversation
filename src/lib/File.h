#ifndef FILE_H
#define FILE_H

#include <unistd.h>

class File
{
	private:
		int fd;

	public:
		File (const char *path, int flags);
		File (const char *path, int flags, mode_t mode);
		~File ();
};

#endif
