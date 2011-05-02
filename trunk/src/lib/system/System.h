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

class System
{
	public:
		static void spawn (const char *file, char *const argv[]);

		static void check (int err)
		{
			if (err == -1) throw SystemErrorException ();
		}
};

#endif
