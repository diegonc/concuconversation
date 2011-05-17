#ifndef USUARIOREMOTO_H
#define USUARIOREMOTO_H

#include <unistd.h>

#include <chat/SharedMessage.h>
#include <system/Semaphore.h>

class UsuarioRemoto
{
	pid_t owner;
	std::string name;
	SharedMessage message;
	Semaphore lock;

	public:
		UsuarioRemoto (const std::string& name, pid_t owner, const std::string& salonName);

		void recibir(const Message&);

};

#endif
