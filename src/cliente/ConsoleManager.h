#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <string>
#include <vector>

#include <curses.h>

#include <signal.h>

class ConsoleListener
{
	public:
		virtual void onInputLine (const std::string& text) = 0;
};

class ConsoleManager
{
	public:
		enum cause {
			ERROR,
			INTERRUPTED,
			EXIT_REQUESTED
		};

	private:
		ConsoleListener& listener;
		/* TODO: mover a Cliente */
		sigset_t mask;
		/*************************/

		int input_size;
		WINDOW* msg;
		WINDOW* input;
		std::vector<char> input_buffer;

		int next_char (WINDOW *w);

	public:
		ConsoleManager (ConsoleListener& listener);
		~ConsoleManager ();

		enum cause run ();

		void append (const std::string& msg);
};

#endif
