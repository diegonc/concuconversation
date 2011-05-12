#ifndef USUARIOREMOTO_H
#define USUARIOREMOTO_H

#include <unistd.h>

#include <chat/Message.h>
#include <system/SharedVariable.h>

class UsuarioRemoto
{
	pid_t owner;
	/* SharedVariable<off_t> proximaLectura; */

	public:
		UsuarioRemoto (const std::string& name, pid_t owner);

		void recibir(const Message&);

};

#endif
