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

		void inicializar (const char *path, int flags, mode_t mode);

	public:
		File (const std::string &path, int flags);
		File (const std::string &path, int flags, mode_t mode);
		File (const char *path, int flags);
		File (const char *path, int flags, mode_t mode);
		~File ();

		int write (size_t n, const char *data);
		int read (size_t n, char *data);
};

#endif
