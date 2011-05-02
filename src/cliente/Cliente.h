#ifndef CLIENTE_H
#define CLIENTE_H

#include <ConsoleManager.h>

class Cliente : public ConsoleListener
{
	private:
		ConsoleManager console;

	public:
		Cliente (int argc, char **argv);
		~Cliente ();

		void run ();

		void onInputLine (const std::string& text);
};

#endif
