#ifndef USUARIOIMPL_H
#define USUARIOIMPL_H

#include <ConsoleManager.h>
#include <chat/Usuario.h>


class UsuarioImpl : public Usuario
{
	private:
		ConsoleManager& console;

	public:
		UsuarioImpl (ConsoleManager& console, const std::string& nombre);

		void recibir (const Message& m);
};

#endif
