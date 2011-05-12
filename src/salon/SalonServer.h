#ifndef SALONSERVER_H
#define SALONSERVER_H

#include <map>

#include <ArgParser.h>
#include <UsuarioRemoto.h>

#include <chat/MessageReader.h>
#include <chat/MessageVisitor.h>
#include <system/InitializedSemaphore.h>

class SalonServer : public MessageVisitor
{
	private:
		InitializedSemaphore lockForWriters;
		MessageReader messages;

		typedef std::map<std::string, UsuarioRemoto *> MapUsuarios;
		MapUsuarios usuarios;

	public:
		SalonServer (const ArgParser &args);
		~SalonServer ();

		void run ();

		void visit (const JoinMessage& msg);
		void visit (const QuitMessage& msg);
		void visit (const TextMessage& msg);
};

#endif