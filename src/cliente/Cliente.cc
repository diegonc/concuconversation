#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>
#include <system/SignalHandler.h>

#include <log4cxx/CursesAppender.h>
#include <log4cxx/level.h>
#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
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
		LOG4CXX_STR("%6r %5p %c - %m%n"));
	log4cxx::LayoutPtr layout (new log4cxx::PatternLayout (
			TTCC_CONVERSION_PATTERN));
	log4cxx::FileAppenderPtr fileAppender(new log4cxx::FileAppender(layout, "cliente.txt", true));

	if (debug)
		root->setLevel (log4cxx::Level::getDebug ());
	else
		root->setLevel (log4cxx::Level::getError ());

	appender->setLayout (layout);

	log4cxx::helpers::Pool pool;
	appender->activateOptions (pool);

	root->addAppender (appender);
	root->addAppender (fileAppender);

	log4cxx::LogManager::getLoggerRepository()->setConfigured (true);
	LOG4CXX_DEBUG (root, "log4cxx inicializado.");
};

Cliente::Cliente (const ArgParser& args)
	: mensajes_pendientes (0),
	  salida_requerida (0), 
	  console (*this),
	  loginit (console, args),
	  name (args.nombre ()),
	  salon (args.salon ()),
	  messageLock(IPCName(args.salon().c_str(),getpid()),1,0666 | IPC_CREAT),
	  message(IPCName(args.salon().c_str(),getpid()),0666 | IPC_CREAT)
{
	messageLock.initialize();
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
	messageLock.signal (0, 1);

	do {
		cause = console.run ();
		if (mensajes_pendientes != 0) {
			mensajes_pendientes = 0;

			LOG4CXX_DEBUG(logger, "Esperando mensaje");
			message.get()->accept(*this);
			LOG4CXX_DEBUG(logger, "Mensaje recibido");
			messageLock.signal(0,1);
		}
	} while (salida_requerida == 0 && cause != ConsoleManager::EXIT_REQUESTED);
	salon.quit (name);
}

void Cliente::onInputLine (const std::string& text)
{
	LOG4CXX_DEBUG (logger, "Postenado mensaje: " << text);
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
	console.append(msg.toString());
}

void Cliente::visit (const QuitMessage& msg){
	LOG4CXX_DEBUG(logger, "QUIT: " <<msg.toString());
	console.append(msg.toString());
}

void Cliente::visit (const TextMessage& msg){
	LOG4CXX_DEBUG(logger, "TEXTO: " << msg.toString());
	console.append(msg.toString());
}
