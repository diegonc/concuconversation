#include <ArgParser.h>
#include <SalonServer.h>

int main (int argc, char **argv)
{
	SalonServer server (ArgParser (argc, argv));
	server.run ();
	return 0;
}
