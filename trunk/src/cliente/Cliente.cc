#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>

Cliente::Cliente (const ArgParser& args)
	: console (*this),
	  salon (args.salon ()),
	  usuario (console, args.nombre ())
{
	usuario.unirse (&salon);
}

Cliente::~Cliente ()
{

}

void Cliente::run ()
{
	ConsoleManager::cause cause;
	do {
		cause = console.run ();
	} while (cause != ConsoleManager::EXIT_REQUESTED);
}

void Cliente::onInputLine (const std::string& text)
{
	salon.post (TextMessage (usuario.getNombre (), text));
	/* TODO: quitar cuando se lea el mensaje desde el salon. */
	console.append (text);
}

