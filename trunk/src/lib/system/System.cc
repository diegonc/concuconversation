#include <system/System.h>

#include <unistd.h>

SystemErrorException::SystemErrorException () throw ()
	: number (errno)
{
}

SystemErrorException::SystemErrorException (int err) throw ()
	: number (err)
{
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
