#include <string>
#include <vector>

#include <curses.h>

#include <Cliente.h>

Cliente::Cliente (int arg, char **argv)
	: console (*this)
{

}

Cliente::~Cliente ()
{

}

void Cliente::run ()
{
	ConsoleManager::cause cause;
	do {
		cause = console.run ();
	} while (cause != ConsoleManager::EXIT_REQUESTED);
}

void Cliente::onInputLine (const std::string& text)
{
	// salon.post (TextMessage (text))
	console.append (text);
}

