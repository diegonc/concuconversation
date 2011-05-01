#ifndef JOINMESSAGE_H
#define JOINMESSAGE_H

#include <string>

#include <chat/Message.h>

class JoinMessage : public Message
{
	public:
		static const int MESSAGE_ID = 1;

	private:
		std::string name;

	public:
		JoinMessage (const std::string& name);

		void write (OutputStream& stream) const;
};

#endif
