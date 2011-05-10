#ifndef MESSAGEREADER_H
#define MESSAGEREADER_H

#include <chat/Message.h>
#include <chat/MessageFactory.h>
#include <chat/PacketReader.h>

class MessageReader
{
	private:
		std::auto_ptr<PacketReader> packets;
		std::auto_ptr<MessageFactory> factory;

	public:
		MessageReader (std::auto_ptr<PacketReader> packets, std::auto_ptr<MessageFactory> factory);
		MessageReader (PacketReader *packets, MessageFactory *factory);


		std::auto_ptr<Message> readMessage ();
};

#endif
