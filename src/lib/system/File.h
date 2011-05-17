#ifndef FILE_H
#define FILE_H

#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <log4cxx/logger.h>

class File
{
	private:
		static log4cxx::LoggerPtr logger;
		int fd;
		char nombre[255];
		void inicializar (const char *path, int flags);

	public:
		File (const std::string &path, int flags);
		File (const char *path, int flags);
		~File ();

		int write (size_t n, const char *data);
		int read (size_t n, char *data);
};

#endif
