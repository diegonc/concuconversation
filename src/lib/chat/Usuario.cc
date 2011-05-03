#include <chat/Usuario.h>

void Usuario::unirse (Salon *salon)
{
	if (this->salon != NULL) {
		this->salon->quit (*this);
		salon = NULL;
	}

	salon->join (*this);
	this->salon = salon;
}

void Usuario::enviar (const TextMessage& msg)
{
	/* TODO: si null... */
	if (this->salon != NULL)
		this->salon->post (msg);
}
