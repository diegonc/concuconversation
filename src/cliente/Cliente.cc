#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>
#include <system/SignalHandler.h>

Cliente::Cliente (const ArgParser& args)
	: mensajes_pendientes (0),
	  salida_requerida (0),
	  console (*this),
	  salon (args.salon ()),
	  name (args.nombre ())/*,
	  usuario (console)*/
{
	salon.join (name, getpid (), "" /* usuario.getNamespace () */);
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
		if (mensajes_pendientes != 0) {
			mensajes_pendientes = 0;
			console.append ("SIGUSR1\n");
		}
	} while (salida_requerida == 0 && cause != ConsoleManager::EXIT_REQUESTED);
}

void Cliente::onInputLine (const std::string& text)
{
	salon.post (TextMessage (name, text));
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
	if (signum == SIGINT)
		salida_requerida = 1;
	else if (signum == SIGUSR1)
		mensajes_pendientes = 1;
}
