#include <SalonRemoto.h>

#include <sys/stat.h>

SalonRemoto::SalonRemoto (std::string& salon)
{
	fifo = iniciar (salon);	
}

/**
 * Inicia el salón remoto si este no ha sido iniciado.
 */
void SalonRemoto::iniciar (std::string& salon)
{
	int err;

	/*
	 * Crea el fifo a través del qué se comunicará con el
	 * salón.
	 */
	err = mkfifo (salon.c_str (), 0666);

	/*
	 * Si el fifo no existía se inicia el proceso que administrará
	 * la conversación y que contiene el objeto Salon al que este
	 * proxy accede.
	 */
	if (err == -1 && errno == EEXIST) {
		int pid = fork ();
		if (pid == 0) {
		}
		else if (pid == -1) {
	}

	
}
