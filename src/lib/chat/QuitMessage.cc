#include <chat/QuitMessage.h>
#include <chat/Packet.h>

QuitMessage::QuitMessage (const std::string& name)
	: name (name)
{
}

void QuitMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.push (QuitMessage::MESSAGE_ID);
	pkt.push (name);

	pkt.write (stream);
}
