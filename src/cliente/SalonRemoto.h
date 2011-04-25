#ifndef SALONREMOTO_H
#define SALONREMOTO_H

#include <string>

#include <FifoOutputStream.h>
#include <Salon.h>

class SalonRemoto : public Salon
{
	private:
		FifoOutputStream *fifo;

		FifoOutputStream *iniciar (std::string& salon);

	public:
		SalonRemoto (std::string& salon);
		virtual ~SalonRemoto ();
};

#endif
