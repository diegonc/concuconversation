#ifndef SALONSERVER_H
#define SALONSERVER_H

#include <map>

#include <ArgParser.h>
#include <UsuarioRemoto.h>

#include <chat/Message.h>
#include <chat/MessageReader.h>
#include <chat/MessageVisitor.h>
#include <system/FileUnlinker.h>
#include <system/Semaphore.h>

class SalonServer : public MessageVisitor
{
	private:
		std::string salonName;
		Semaphore lockForWriters;
		MessageReader messages;

		typedef std::map<std::string, UsuarioRemoto *> MapUsuarios;
		MapUsuarios usuarios;

		FileUnlinker roomUnlinker;

	public:
		SalonServer (const ArgParser &args);
		~SalonServer ();

		void run ();

		void visit (const JoinMessage& msg);
		void visit (const QuitMessage& msg);
		void visit (const TextMessage& msg);
};

#endif
