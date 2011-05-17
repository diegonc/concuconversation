#ifndef CLIENTE_H
#define CLIENTE_H

#include <ArgParser.h>
#include <ConsoleManager.h>
#include <SalonRemoto.h>
#include <system/EventHandler.h>
#include <chat/Message.h>
#include <system/SharedVariable.h>
#include <system/Semaphore.h>

class LoggingInitialization
{
	friend class Cliente;
	WINDOW *wnd;
	LoggingInitialization (ConsoleManager& cm, const ArgParser& args);
};

class Cliente : public ConsoleListener, public EventHandler, public MessageVisitor
{
	private:
		volatile sig_atomic_t mensajes_pendientes;
		volatile sig_atomic_t salida_requerida;
		ConsoleManager console;
		LoggingInitialization loginit;

		std::string name;
		Semaphore messageLock;
		SharedVariable<Message> message;
		SalonRemoto salon;

		void setupSignals ();

	public:
		Cliente (const ArgParser& args);
		~Cliente ();

		void run ();

		void onInputLine (const std::string& text);
		void handleSignal (int signum);

		void visit (const JoinMessage& msg);
		void visit (const QuitMessage& msg);
		void visit (const TextMessage& msg);
};

#endif
