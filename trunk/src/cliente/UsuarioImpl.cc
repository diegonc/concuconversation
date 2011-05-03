#include <UsuarioImpl.h>

UsuarioImpl::UsuarioImpl (ConsoleManager& console, const std::string& nombre)
	: Usuario (nombre),
	  console (console)
{
}

void UsuarioImpl::recibir (const Message& m)
{
	console.append (m.toString ());
}
