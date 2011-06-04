#include <errno.h>
#include <sys/stat.h>

#include <SalonRemoto.h>
#include <chat/JoinMessage.h>
#include <chat/QuitMessage.h>
#include <system/System.h>
#include <iostream>

#include <log4cxx/logger.h>

namespace {
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger ("SalonRemoto"));
}

SalonRemoto::SalonRemoto (const std::string& salon)
{
	LOG4CXX_DEBUG(logger, "Creando el salon remoto");
	fifo = iniciar (salon);
	LOG4CXX_DEBUG(logger, "Paso el fifo");
	lock = (new Semaphore (IPCName (salon.c_str(), 'L'), 1, 0666))
		->persist ();
	LOG4CXX_DEBUG(logger, "Paso el lock");
}

SalonRemoto::~SalonRemoto ()
{
	delete lock;
	delete fifo;
}

FifoOutputStream* SalonRemoto::iniciar (const std::string& salon)
{
	/*
	 * Abre el fifo durmiendo hasta que el salón haya terminado
	 * su inicialización y abrá su extremo.
	 */
	return new FifoOutputStream (salon);
}

void SalonRemoto::join (const std::string& name, pid_t pid, const std::string& ipcNamespace)
{
	JoinMessage msg (name, pid, ipcNamespace);
	doPost (msg);
}

void SalonRemoto::quit (const std::string& name)
{
	QuitMessage msg(name);
	doPost (msg);
}

void SalonRemoto::post (const TextMessage& msg)
{
	doPost (msg);
}

void SalonRemoto::doPost (const Message& msg)
{
	lock->wait ();
	LOG4CXX_DEBUG(logger, "Enviando mensaje");
	msg.write (*fifo);
	LOG4CXX_DEBUG(logger, "Mensaje enviado");
	lock->signal ();
}
