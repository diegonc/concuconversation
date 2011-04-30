#ifndef JOINMESSAGE_H
#define JOINMESSAGE_H

#include <string>

#include <Message.h>

class QuitMessage : public Message
{
	public:
		static const int MESSAGE_ID = 3;

	private:
		std::string name;

	public:
		QuitMessage (const std::string& name);

		void write (OutputStream& stream) const;
};

#endif
