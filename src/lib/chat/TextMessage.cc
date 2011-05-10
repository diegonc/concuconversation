#include <sstream>
#include <stdexcept>

#include <chat/TextMessage.h>
#include <chat/Packet.h>

TextMessage::TextMessage (const std::string& name, const std::string& text)
	: name (name),
	  text (text)
{
}

TextMessage::TextMessage (Packet &pkt)
{
	if (pkt.readInt () != TextMessage::MESSAGE_ID)
		throw std::runtime_error ("Unexpected message id.");
	
	name = pkt.readString ();
	text = pkt.readString ();
}

void TextMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.pushInt (TextMessage::MESSAGE_ID);
	pkt.pushString (name);
	pkt.pushString (text);

	pkt.write (stream);
}

std::string TextMessage::toString () const
{
	std::ostringstream oss;
	oss << name << "> " << text << std::endl;
	return oss.str ();
}

void TextMessage::accept (MessageVisitor& v) const
{
	v.visit (*this);
}
