#ifndef SALONREMOTO_H
#define SALONREMOTO_H

#include <string>

#include <chat/Salon.h>
#include <io/FifoOutputStream.h>

class SalonRemoto : public Salon
{
	private:
		FifoOutputStream *fifo;

		FifoOutputStream *iniciar (const std::string& salon);

	public:
		SalonRemoto (const std::string& salon);
		virtual ~SalonRemoto ();

		virtual void join (Usuario& u);
		virtual void quit (Usuario& u);
		virtual void post (const TextMessage& msg);
};

#endif
