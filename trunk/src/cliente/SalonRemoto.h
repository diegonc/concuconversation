#ifndef SALONREMOTO_H
#define SALONREMOTO_H

#include <string>

#include <chat/Message.h>
#include <chat/Salon.h>
#include <chat/TextMessage.h>
#include <chat/Usuario.h>
#include <io/FifoOutputStream.h>
#include <system/Semaphore.h>

class SalonRemoto : public Salon
{
	private:
		FifoOutputStream *fifo;
		Semaphore *lock;

		FifoOutputStream *iniciar (const std::string& salon);

		void doPost (const Message& msg);

	public:
		SalonRemoto (const std::string& salon);
		virtual ~SalonRemoto ();

		virtual void join (Usuario& u);
		virtual void quit (Usuario& u);
		virtual void post (const TextMessage& msg);
};

#endif
