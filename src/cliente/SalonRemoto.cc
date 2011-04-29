#include <sys/stat.h>

#include <SalonRemoto.h>
#include <System.h>

SalonRemoto::SalonRemoto (const std::string& salon)
{
	fifo = iniciar (salon);	
}

SalonRemoto::~SalonRemoto ()
{
	delete fifo;
}

/**
 * Inicia el salón remoto si este no ha sido iniciado.
 */
FifoOutputStream* SalonRemoto::iniciar (const std::string& salon)
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
	if (err == 0) {
		char *const argv[] = { "salon",
			const_cast<char *> (salon.c_str ()), NULL };
		System::spawn ("salon", argv);
	} else if (err == -1 && errno != EEXIST) {
		throw SystemErrorException ();
	}

	/*
	 * Abre el fifo durmiendo hasta que el salón haya terminado
	 * su inicialización y abrá su extremo.
	 */
	return new FifoOutputStream (salon);
}

void SalonRemoto::post (const Message& msg)
{
	msg.write (*fifo);
}
