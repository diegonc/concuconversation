#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include <io/OutputStream.h>

class MessageVisitor;

class Message
{
	public:
		virtual ~Message () { }
		virtual void write (OutputStream& stream) const = 0;
		virtual std::string toString () const = 0;

		virtual void accept (MessageVisitor& v) const = 0;
};

#endif
