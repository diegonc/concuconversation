#ifndef USUARIO_H
#define USUARIO_H

#include <string>

#include <chat/Salon.h>
#include <chat/Message.h>

class Usuario
{
	private:
		std::string nombre;
		Salon *salon;

	public:
		Usuario (const std::string& nombre)
			: nombre (nombre),
			  salon (NULL) {}
		virtual ~Usuario () {}

		const std::string& getNombre () const
		{
			return nombre;
		}

		virtual void unirse (Salon *salon) = 0;
		virtual void recibir (const Message& m) = 0;
		virtual void enviar (const Message& m) = 0;
};

#endif
