#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

class TextMessage;

#include <string>

#include <chat/Message.h>
#include <chat/MessageVisitor.h>
#include <chat/Packet.h>

class TextMessage : public Message
{
	public:
		static const int MESSAGE_ID = 2;

	private:
		std::string name;
		std::string text;

	public:
		TextMessage (const std::string& name, const std::string& text);
		TextMessage (Packet &pkt);

		void write (OutputStream& stream) const;
		std::string toString () const;

		void accept (MessageVisitor& v) const;
};

#endif
