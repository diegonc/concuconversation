#include <Cliente.h>

int main (int argc, char **argv)
{
	Cliente c (ArgParser (argc, argv));
	c.run ();
	return 0;
}
