#include <stdexcept>
#include <iostream>

#include <ArgParser.h>
#include <SalonServer.h>

int main (int argc, char **argv)
{
	try {
		SalonServer server (ArgParser (argc, argv));
		server.run ();
	} catch (...) {
		/* correr destructores por favor. */
		return 1;
	}
	return 0;
}
