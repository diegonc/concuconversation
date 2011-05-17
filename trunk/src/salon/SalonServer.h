#ifndef SALONSERVER_H
#define SALONSERVER_H

#include <map>

#include <ArgParser.h>
#include <UsuarioRemoto.h>

#include <chat/Message.h>
#include <chat/MessageReader.h>
#include <chat/MessageVisitor.h>
#include <system/FifoFilesystemObject.h>
#include <system/Semaphore.h>
#include <log4cxx/logger.h>

class SalonServer : public MessageVisitor
{
	private:
		static log4cxx::LoggerPtr logger;

		typedef std::map<std::string, UsuarioRemoto *> MapUsuarios;
		MapUsuarios usuarios;
		std::string salonName;
		FifoFilesystemObject roomNode;
		Semaphore lockForWriters;
		MessageReader messages;

	public:
		SalonServer (const ArgParser &args);
		~SalonServer ();

		void run ();

		void visit (const JoinMessage& msg);
		void visit (const QuitMessage& msg);
		void visit (const TextMessage& msg);
};

#endif
