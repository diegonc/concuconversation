#ifndef SALONREMOTO_H
#define SALONREMOTO_H

#include <string>

#include <FifoOutputStream.h>
#include <Salon.h>

class SalonRemoto : public Salon
{
	private:
		FifoOutputStream *fifo;

		FifoOutputStream *iniciar (const std::string& salon);

	public:
		SalonRemoto (const std::string& salon);
		virtual ~SalonRemoto ();

		virtual void post (const Message& msg);
};

#endif
