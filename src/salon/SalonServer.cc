#include <iostream>
#include <memory>

#include <SalonServer.h>
#include <chat/MessageFactory.h>
#include <chat/PacketReader.h>
#include <io/InputStream.h>
#include <io/FifoInputStream.h>

SalonServer::SalonServer (const ArgParser &args)
	: lockForWriters (IPCName (args.salon ().c_str (), 'L'), 1,
		0666 | IPC_CREAT | IPC_EXCL),
	  messages (new PacketReader (new FifoInputStream (args.salon ())),
		new MessageFactory ()),
	  roomUnlinker (args.salon ())
{
	/* Permite a los clientes comenzar a escribir. */
	lockForWriters.initialize ();
	lockForWriters.signal ();
}

SalonServer::~SalonServer ()
{
	for (MapUsuarios::iterator it = usuarios.begin ();
			it != usuarios.end (); ++it)
		delete it->second;
}

void SalonServer::run ()
{
	while (true) {
		std::auto_ptr<Message> msg (messages.readMessage ());
		/* TODO: escribir mensaje en log. */
		std::cout << msg->toString ();
		msg->accept (*this);
	}
}

void SalonServer::visit (const JoinMessage& msg)
{
	MapUsuarios::iterator it = usuarios.find (msg.getNombre ());
	/* TODO: si ya esta no hace nada 8´| */
	if (it == usuarios.end ()) {
		UsuarioRemoto *u = new UsuarioRemoto (msg.getNombre (), msg.getPID ());
		usuarios.insert (MapUsuarios::value_type (msg.getNombre (),
			u));
	}
}

void SalonServer::visit (const QuitMessage& msg)
{
	int salio = usuarios.erase (msg.getNombre ());
	if (salio == 0)
		return;

	for (MapUsuarios::iterator it = usuarios.begin ();
			it != usuarios.end (); ++it) {
		it->second->recibir (msg);
	}
}

void SalonServer::visit (const TextMessage& msg)
{
	for (MapUsuarios::iterator it = usuarios.begin ();
			it != usuarios.end (); ++it) {
		it->second->recibir (msg);
	}
}
