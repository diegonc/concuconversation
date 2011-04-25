#include <System.h>

#include <unistd.h>

SystemErrorException::SystemErrorException () throw ()
{
	this->number = errno;
}

void System::spawn (const char *file, char *const argv[])
{
	int err;

	err = fork ();
	if (err == 0) {
		err = execvp (file, argv);
		/* TODO: log error */
		_exit (1);
	}
	else if (err == -1)
		throw SystemErrorException ();
}
