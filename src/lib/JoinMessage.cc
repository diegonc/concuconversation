#include <JoinMessage.h>
#include <Packet.h>

JoinMessage::JoinMessage (const std::string& name)
	: name (name)
{
}

void JoinMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.push (JoinMessage::MESSAGE_ID);
	pkt.push (name);

	pkt.write (stream);
}
