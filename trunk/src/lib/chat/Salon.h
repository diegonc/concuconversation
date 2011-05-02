#ifndef SALON_H
#define SALON_H

#include <chat/TextMessage.h>
#include <chat/Usuario.h>

class Salon
{
	public:
		virtual ~Salon();

		virtual void join (Usuario& u) = 0;
		virtual void quit (Usuario& u) = 0;

		virtual void post (const TextMessage& msg) = 0;

};

#endif
