#include <string>

#include <io/FifoInputStream.h>
#include <system/InitializedSemaphore.h>

int main (int argc, char **argv)
{
	if (argc != 2)
		return 1;

	/* inicializar lock */
	InitializedSemaphore sem(IPCName(argv[1], 'L'), 1, 0666 | IPC_CREAT);
	sem.set (0, 1);

	/* desbloquear clientes */
	FifoInputStream fifo( (std::string (argv[1])) );

	try {
		char buffer;
		while (true) {
			fifo.read (1, &buffer);
			write (1, &buffer, 1);
		}
	} catch (...) { }

	return 0;
}
