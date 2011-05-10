#include <stdexcept>

#include <chat/JoinMessage.h>
#include <chat/MessageFactory.h>
#include <chat/TextMessage.h>
#include <chat/QuitMessage.h>

std::auto_ptr<Message> MessageFactory::createMessage (Packet &pkt)
{
	int msgId = pkt.readInt ();

	/* XXX: constructores vuelven a leer el id. */
	pkt.rewind ();

	if (msgId == JoinMessage::MESSAGE_ID)
		return std::auto_ptr<Message> (new JoinMessage (pkt));
	if (msgId == QuitMessage::MESSAGE_ID)
		return std::auto_ptr<Message> (new QuitMessage (pkt));
	if (msgId == TextMessage::MESSAGE_ID)
		return std::auto_ptr<Message> (new TextMessage (pkt));

	throw std::runtime_error ("Unexpected message id.");
}
