#include <sstream>
#include <stdexcept>

#include <chat/JoinMessage.h>
#include <chat/Packet.h>

JoinMessage::JoinMessage (const std::string& name, pid_t pid, const std::string& ipcNamespace)
	: name (name),
	  pid (pid),
	  ipcNamespace (ipcNamespace)
{
}

JoinMessage::JoinMessage (Packet &pkt)
{
	if (pkt.readInt () != JoinMessage::MESSAGE_ID)
		throw std::runtime_error ("Unexpected message id.");

	pid = pkt.readInt ();
	name = pkt.readString ();
	ipcNamespace = pkt.readString ();
}

void JoinMessage::write (OutputStream& stream) const
{
	Packet pkt;

	pkt.pushInt (JoinMessage::MESSAGE_ID);
	pkt.pushInt (pid);
	pkt.pushString (name);
	pkt.pushString (ipcNamespace);

	pkt.write (stream);
}

std::string JoinMessage::toString () const
{
	std::ostringstream oss;
	oss << name << " ha entrado a la sala." << std::endl;
	return oss.str();
}

void JoinMessage::accept (MessageVisitor& v) const
{
	v.visit (*this);
}
