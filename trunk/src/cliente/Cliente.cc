#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>
#include <system/SignalHandler.h>

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

	setupSignals ();

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

void Cliente::setupSignals ()
{
	sigset_t blocked;

	sigemptyset (&blocked);
	sigaddset (&blocked, SIGINT);
	sigaddset (&blocked, SIGUSR1);
	sigprocmask (SIG_SETMASK, &blocked, NULL);

	SignalHandler& sig = SignalHandler::getInstance ();
	sig.registrarHandler (SIGINT, this);
	sig.registrarHandler (SIGUSR1, this);
}

void Cliente::handleSignal (int signum)
{
}
