#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>
#include <system/SignalHandler.h>


Cliente::Cliente (const ArgParser& args)
	: mensajes_pendientes (0),
	  salida_requerida (0),
	  name (args.nombre ()),
	  message(IPCName(args.salon ().c_str(),getpid()),0666 | IPC_CREAT),
	  messageLock(IPCName(args.salon ().c_str(),getpid()),2,0666 | IPC_CREAT),
	  salon (args.salon ()),
	  console (*this)
{
	messageLock.initialize();
	messageLock.set(0,0);
	messageLock.set(1,0);
	std::cout << "Join salon [" << args.salon() << "] with name [" << args.nombre() << "]." << std::endl;
	salon.join (name, getpid (), "" /* usuario.getNamespace () */);
}

Cliente::~Cliente ()
{
}

void Cliente::run ()
{
	ConsoleManager::cause cause;

	setupSignals ();

	pid_t pid= fork();
	if (pid==0){
		std::cout << "Lanzando fork lector" << std::endl;
		while (1){
			messageLock.signal(0,1);
			std::cout << "Esperando mensaje" << std::endl;
			messageLock.wait(1,1);
			message.get().accept(*this);
			std::cout << "Mensaje recibido" << std::endl;
		}
	}else{
		std::cout << "Lanzando fork escritor" << std::endl;
		do {
			cause = console.run ();
			if (mensajes_pendientes != 0) {
				mensajes_pendientes = 0;
				//console.append ("SIGUSR1\n");
			}
		} while (salida_requerida == 0 && cause != ConsoleManager::EXIT_REQUESTED);
	}
}

void Cliente::onInputLine (const std::string& text)
{
	salon.post (TextMessage (name, text));
	/* TODO: quitar cuando se lea el mensaje desde el salon. */
	/* console.append (text); */
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

void Cliente::visit (const JoinMessage& msg){
	std::cout << "JOIN" << msg.toString() << std::endl;
	console.append("JOIN");
	console.append(msg.toString());
}

void Cliente::visit (const QuitMessage& msg){
	std::cout << "QUIT" <<msg.toString() << std::endl;
	console.append("QUIT");
	console.append(msg.toString());
}

void Cliente::visit (const TextMessage& msg){
	std::cout << "TEXTO" << msg.toString() << std::endl;
	console.append("TEXTO");
	console.append(msg.toString());
}
