#include <sstream>
#include <stdexcept>

#include <chat/QuitMessage.h>
#include <chat/Packet.h>

QuitMessage::QuitMessage (const std::string& name)
	: name (name)
{
}

QuitMessage::QuitMessage (Packet &pkt)
{
	if (pkt.readInt () != QuitMessage::MESSAGE_ID)
		throw std::runtime_error ("Unexpected message id.");
	
	name = pkt.readString ();
}

void QuitMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.pushInt (QuitMessage::MESSAGE_ID);
	pkt.pushString (name);

	pkt.write (stream);
}

std::string QuitMessage::toString () const
{
	std::ostringstream oss;
	oss << name << " has salido de la sala." << std::endl;
	return oss.str();
}

void QuitMessage::accept (MessageVisitor& v) const
{
	v.visit (*this);
}
