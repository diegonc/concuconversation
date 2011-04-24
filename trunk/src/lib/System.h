#ifndef SYSTEM_H
#define SYSTEM_H

#include <errno.h>
#include <exception>

class SystemrErrorException : public std::exception
{
	private:
		int errno;

	public:
		SystemErrorException () : errno (errno) {}
		virtual ~SystemErrorException ();

		virtual const char *what() const throw()
		{
			return strerror (this->errno);
		}
};

class System
{
	static void spawn (const char *file, char *const argv[]); 
};

#endif
