#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include <memory>

#include <chat/Packet.h>

class MessageFactory
{
	public:
		std::auto_ptr<Message> createMessage (Packet &pkt);
};

#endif
