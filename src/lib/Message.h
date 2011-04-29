#ifndef MESSAGE_H
#define MESSAGE_H

#include <OutputStream.h>

class Message
{
	public:
		virtual void write (OutputStream& stream) const = 0;
};

#endif
