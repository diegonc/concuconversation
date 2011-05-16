#include <UsuarioRemoto.h>

#include <iostream>

#include <signal.h>

UsuarioRemoto::UsuarioRemoto (const std::string& name, pid_t owner, const std::string& salonName)
	: owner (owner),
	  name (name),
	  message (IPCName(salonName.c_str (), owner),0666),
	  lock (IPCName(salonName.c_str (), owner),2,0666)
{

}

void UsuarioRemoto::recibir(const Message& msg)
{
	std::cout << "enviando mensaje a " << name << std::endl;
	lock.wait(0,1);
	sleep(3);
	message.set(msg);
	lock.signal(1,1);
	std::cout << "mensaje enviado a " << name << std::endl;
}
