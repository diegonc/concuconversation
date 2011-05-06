#ifndef QUITMESSAGE_H
#define QUITMESSAGE_H

#include <string>

#include <chat/Message.h>

class QuitMessage : public Message
{
	public:
		static const int MESSAGE_ID = 3;

	private:
		std::string name;

	public:
		QuitMessage (const std::string& name);

		void write (OutputStream& stream) const;
		std::string toString () const;
};

#endif