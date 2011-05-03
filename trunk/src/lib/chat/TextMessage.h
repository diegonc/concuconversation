#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <string>

#include <chat/Message.h>

class TextMessage : public Message
{
	public:
		static const int MESSAGE_ID = 2;

	private:
		std::string name;
		std::string text;

	public:
		TextMessage (const std::string& name, const std::string& text);

		void write (OutputStream& stream) const;
		std::string toString () const;
};

#endif
