#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

#include <curses.h>

class Cliente
{
	private:
		int input_size;
		WINDOW* msg;
		WINDOW* input;

		std::string readstring ();

	public:
		Cliente ();
		~Cliente ();

		void run ();
};

#endif
