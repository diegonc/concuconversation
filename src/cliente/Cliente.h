#ifndef CLIENTE_H
#define CLIENTE_H

#include <ArgParser.h>
#include <ConsoleManager.h>
#include <SalonRemoto.h>
#include <UsuarioImpl.h>
#include <system/EventHandler.h>

class Cliente : public ConsoleListener, public EventHandler
{
	private:
		ConsoleManager console;
		SalonRemoto salon;
		UsuarioImpl usuario;

		void setupSignals ();

	public:
		Cliente (const ArgParser& args);
		~Cliente ();

		void run ();

		void onInputLine (const std::string& text);
		void handleSignal (int signum);
};

#endif
