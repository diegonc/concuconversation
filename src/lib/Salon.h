#ifndef SALON_H
#define SALON_H

#include <Message.h>

class Salon
{
	public:
		virtual ~Salon();

		virtual void post (const Message& msg) = 0;
};

#endif
