#ifndef SYSTEM_H
#define SYSTEM_H

#include <exception>

#include <errno.h>
#include <string.h>

class SystemErrorException : public std::exception
{
	private:
		int number;

	public:
		SystemErrorException () throw ();
		virtual ~SystemErrorException () throw () { }

		virtual const char *what() const throw()
		{
			return strerror (this->number);
		}
};

SystemErrorException::SystemErrorException () throw ()
{
	this->number = errno;
}

class System
{
	static void spawn (const char *file, char *const argv[]); 
};

#endif
