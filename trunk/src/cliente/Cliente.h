#ifndef CLIENTE_H
#define CLIENTE_H

#include <vector>

#include <curses.h>

class Cliente
{
	private:
		int input_size;
		WINDOW* msg;
		WINDOW* input;

		std::vector<char> input_buffer;

	public:
		Cliente ();
		~Cliente ();

		void run ();
};

#endif
