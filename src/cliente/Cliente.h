#ifndef CLIENTE_H
#define CLIENTE_H

#include <ConsoleManager.h>
#include <SalonRemoto.h>
#include <utils/ArgParser.h>

class Cliente : public ConsoleListener
{
	private:
		ConsoleManager console;
		SalonRemoto salon;

	public:
		Cliente (const ArgParser& args);
		~Cliente ();

		void run ();

		void onInputLine (const std::string& text);
};

#endif
