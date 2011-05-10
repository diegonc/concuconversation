#ifndef SALONIMPL_H
#define SALONIMPL_H

#include <map>

#include <chat/Salon.h>

class SalonImpl : public Salon
{
	private:
		std::map<std::string, Usuario *> usuarios;

	public:



};

#endif
