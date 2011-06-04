#include <UsuarioRemoto.h>

#include <iostream>

#include <signal.h>
#include <log4cxx/logger.h>

namespace {
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger ("UsuarioRemoto"));
}

UsuarioRemoto::UsuarioRemoto (const std::string& name, pid_t owner, const std::string& salonName)
	: owner (owner),
	  name (name),
	  message (IPCName(salonName.c_str(), owner),0666),
	  lock (IPCName(salonName.c_str(), owner),1,0666)
{

}

void UsuarioRemoto::recibir(const Message& msg)
{
	LOG4CXX_DEBUG(logger, "enviando mensaje a " << name);
	lock.wait(0,1);
	message.set(msg);
	kill(owner, SIGUSR1);
	LOG4CXX_DEBUG(logger, "mensaje enviado a " << name);
}
