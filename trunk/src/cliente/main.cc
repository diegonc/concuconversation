#include <Cliente.h>

int main (int argc, char **argv)
{	
	ArgParser args (argc, argv);
	Cliente c (args);
	c.run ();
	return 0;
}
