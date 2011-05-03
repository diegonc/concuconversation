#include <sstream>

#include <chat/JoinMessage.h>
#include <chat/Packet.h>

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

std::string JoinMessage::toString () const
{
	std::ostringstream oss;
	oss << name << " ha entrado a la sala." << std::endl;
	return oss.str();
}   
