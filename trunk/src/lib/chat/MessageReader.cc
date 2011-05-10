#include <chat/MessageReader.h>

MessageReader::MessageReader (std::auto_ptr<PacketReader> packets, std::auto_ptr<MessageFactory> factory)
	: packets (packets),
	  factory (factory)
{
}

MessageReader::MessageReader (PacketReader *packets, MessageFactory *factory)
	: packets (packets),
	  factory (factory)
{
}

std::auto_ptr<Message> MessageReader::readMessage ()
{
	std::auto_ptr<Packet> pkt (packets->readPacket ());
	return factory->createMessage (*pkt);
}
