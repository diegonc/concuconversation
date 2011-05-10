#ifndef QUITMESSAGE_H
#define QUITMESSAGE_H

class QuitMessage;

#include <string>

#include <chat/Message.h>
#include <chat/MessageVisitor.h>
#include <chat/Packet.h>

class QuitMessage : public Message
{
	public:
		static const int MESSAGE_ID = 3;

	private:
		std::string name;

	public:
		QuitMessage (const std::string& name);
		QuitMessage (Packet &pkt);

		const std::string& getNombre () const { return name; }

		void write (OutputStream& stream) const;
		std::string toString () const;

		void accept (MessageVisitor& v) const;
};

#endif
