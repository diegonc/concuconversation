#ifndef SYSTEM_H
#define SYSTEM_H

#include <errno.h>
#include <exception>

class system_error_exception : public std::exception
{
	private:
		int errno;

	public:
		system_error_exception () : errno (errno) {}
		virtual ~system_error_exception ();

		virtual const char *what() const throw()
		{
			return strerror (this->errno);
		}
};

class system
{
	static void spawn 
};

#endif
