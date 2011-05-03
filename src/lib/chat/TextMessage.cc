#include <sstream>

#include <chat/TextMessage.h>
#include <chat/Packet.h>

TextMessage::TextMessage (const std::string& name, const std::string& text)
	: name (name),
	  text (text)
{
}

void TextMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.push (TextMessage::MESSAGE_ID);
	pkt.push (text);

	pkt.write (stream);
}

std::string TextMessage::toString () const
{
	std::ostringstream oss;
	oss << name << "> " << text << std::endl;
	return oss.str ();
}
