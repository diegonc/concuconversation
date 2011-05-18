#include <Cliente.h>
#include <typeinfo>

int main (int argc, char **argv)
{
	try {
		ArgParser args (argc, argv);
		Cliente c (args);
		c.run ();
	} catch (std::exception& e) {
		std::cout << typeid (e).name () << ": " << e.what () << std::endl;
		return 1;
	} catch (...) {
		/* correr destructores por favor. */
		return 1;
	}
	return 0;
}
