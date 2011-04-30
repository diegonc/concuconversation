#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <string>

#include <Message.h>

class TextMessage : public Message
{
	public:
		static const int MESSAGE_ID = 2;

	private:
		std::string text;

	public:
		TextMessage (const std::string& text);

		void write (OutputStream& stream) const;
};

#endif
