#include <chat/TextMessage.h>
#include <chat/Packet.h>

TextMessage::TextMessage (const std::string& text)
	: text (text)
{
}

void TextMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.push (TextMessage::MESSAGE_ID);
	pkt.push (text);

	pkt.write (stream);
}
