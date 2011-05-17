#ifndef EOFEXCEPTION_H
#define EOFEXCEPTION_H

#include <exception>

class EOFException : public std::exception
{
	public:
		EOFException () throw () { }
		virtual ~EOFException () throw () { }

		virtual const char *what() const throw()
		{
			return "Se alcanzo el final de archivo.";
		}
};

#endif
