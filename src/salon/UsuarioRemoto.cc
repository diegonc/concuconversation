#include <UsuarioRemoto.h>

#include <iostream>

#include <signal.h>

UsuarioRemoto::UsuarioRemoto (const std::string& name, pid_t owner)
	: Usuario (name),
	  owner (owner)
{
}

void UsuarioRemoto::recibir(const Message& msg)
{
	std::cout << msg.toString () << std::endl;

	kill (owner, SIGUSR1);
}
