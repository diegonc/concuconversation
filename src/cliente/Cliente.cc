#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>
#include <system/SignalHandler.h>

#include <log4cxx/CursesAppender.h>
#include <log4cxx/level.h>
#include <log4cxx/logger.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/patternlayout.h>

namespace {
	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger ("Cliente"));
}

LoggingInitialization::LoggingInitialization (ConsoleManager& cm, const ArgParser& args)
{
	bool debug = args.debug ();
	
	log4cxx::LoggerPtr root = log4cxx::Logger::getRootLogger ();
	CursesAppenderPtr appender (new CursesAppender (&cm));
	log4cxx::LogString TTCC_CONVERSION_PATTERN (
		LOG4CXX_STR("%r %p %c - %m%n"));
	log4cxx::LayoutPtr layout (new log4cxx::PatternLayout (
			TTCC_CONVERSION_PATTERN));

	if (debug)
		root->setLevel (log4cxx::Level::getDebug ());
	else
		root->setLevel (log4cxx::Level::getError ());

	appender->setLayout (layout);

	log4cxx::helpers::Pool pool;
	appender->activateOptions (pool);

	root->addAppender (appender);

	log4cxx::LogManager::getLoggerRepository()->setConfigured (true);
	LOG4CXX_DEBUG (root, "log4cxx inicializado.");
};

Cliente::Cliente (const ArgParser& args)
	: mensajes_pendientes (0),
	  salida_requerida (0), 
	  console (*this),
	  loginit (console, args),
	  name (args.nombre ()),
	  message(IPCName(args.salon ().c_str(),getpid()),0666 | IPC_CREAT),
	  messageLock(IPCName(args.salon ().c_str(),getpid()),2,0666 | IPC_CREAT),
	  salon (args.salon ())
{
	messageLock.initialize();
	messageLock.set(0,1);
	messageLock.set(1,0);

	LOG4CXX_DEBUG(logger, "Join salon [" << args.salon() << "] with name [" << args.nombre() << "].");
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
		LOG4CXX_DEBUG(logger, "Lanzando fork lector");
		while (1){
			LOG4CXX_DEBUG(logger, "Esperando mensaje");
			messageLock.wait(1,1);
			message.get().accept(*this);
			LOG4CXX_DEBUG(logger, "Mensaje recibido");
			messageLock.signal(0,1);
		}
	}else{
		LOG4CXX_DEBUG(logger, "Lanzando fork escritor");
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
	LOG4CXX_DEBUG (logger, "JOIN: " << msg.toString());

	console.append("JOIN");
	console.append(msg.toString());
}

void Cliente::visit (const QuitMessage& msg){
	LOG4CXX_DEBUG(logger, "QUIT: " <<msg.toString());
	console.append("QUIT");
	console.append(msg.toString());
}

void Cliente::visit (const TextMessage& msg){
	LOG4CXX_DEBUG(logger, "TEXTO: " << msg.toString());
	console.append("TEXTO");
	console.append(msg.toString());
}
