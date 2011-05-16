#include <errno.h>
#include <sys/stat.h>

#include <SalonRemoto.h>
#include <chat/JoinMessage.h>
#include <chat/QuitMessage.h>
#include <system/System.h>
#include <iostream>

SalonRemoto::SalonRemoto (const std::string& salon)
{
	std::cout << "Creando el salon remoto" << std::endl;
	fifo = iniciar (salon);
	std::cout << "Paso el fifo" << std::endl;
	lock = new Semaphore (IPCName (salon.c_str(), 'L'), 1, 0600);
	std::cout << "Paso el lock" << std::endl;
}

SalonRemoto::~SalonRemoto ()
{
	delete lock;
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
	std::cout << "Cree el fifo " << err  << "|" << errno << std::endl;
	/*
	 * Si el fifo no existía se inicia el proceso que administrará
	 * la conversación y que contiene el objeto Salon al que este
	 * proxy accede.
	 */
	if (err == 0) {
		char *const argv[] = { "salon",
			const_cast<char *> (salon.c_str ()), NULL };
		std::cout << "lanzando salon con parametros " << argv << std::endl;
		System::spawn ("../salon/salon", argv);
		/* TODO: limpiar en caso de error. */
	} else if (err == -1 && errno != EEXIST) {
		throw SystemErrorException ();
	}

	/*
	 * Abre el fifo durmiendo hasta que el salón haya terminado
	 * su inicialización y abrá su extremo.
	 */
	return new FifoOutputStream (salon);
}

void SalonRemoto::join (const std::string& name, pid_t pid, const std::string& ipcNamespace)
{
	JoinMessage msg (name, pid, ipcNamespace);
	doPost (msg);
}

void SalonRemoto::quit (const std::string& name)
{
	QuitMessage msg(name);
	doPost (msg);
}

void SalonRemoto::post (const TextMessage& msg)
{
	doPost (msg);
}

void SalonRemoto::doPost (const Message& msg)
{
	lock->wait ();
	msg.write (*fifo);
	lock->signal ();
}
