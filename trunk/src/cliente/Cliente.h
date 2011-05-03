#ifndef CLIENTE_H
#define CLIENTE_H

#include <ArgParser.h>
#include <ConsoleManager.h>
#include <SalonRemoto.h>
#include <UsuarioImpl.h>

class Cliente : public ConsoleListener
{
	private:
		ConsoleManager console;
		SalonRemoto salon;
		UsuarioImpl usuario;

	public:
		Cliente (const ArgParser& args);
		~Cliente ();

		void run ();

		void onInputLine (const std::string& text);
};

#endif
