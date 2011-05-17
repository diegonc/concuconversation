#include <stdexcept>

#include <chat/Packet.h>

log4cxx::LoggerPtr Packet::logger (log4cxx::Logger::getLogger ("Packet"));

Packet::Packet ()
{
	/* Reserva el primer entero para el tamaño. */
	pushInt (0);
	cursor = 4;
}

void Packet::pushByte (char c)
{
	buffer.push_back (c);
}

void Packet::pushInt (int i)
{
	buffer.push_back ((char)((i >>  0) & 0xFF) );
	buffer.push_back ((char)((i >>  8) & 0xFF) );
	buffer.push_back ((char)((i >> 16) & 0xFF) );
	buffer.push_back ((char)((i >> 24) & 0xFF) );
}

void Packet::pushString (const std::string& s)
{
	for (unsigned i=0; i < s.size(); i++)
		buffer.push_back (s[i]);
	/* null terminated */
	buffer.push_back (0);
}

void Packet::write (OutputStream& stream)
{
	update_size ();
	LOG4CXX_DEBUG(logger,"Poniendo en el stream.");
	stream.write (buffer.size(), &buffer[0]);
	LOG4CXX_DEBUG(logger,"Ya lo puse en el stream.");
}

void Packet::update_size ()
{
	int sz = buffer.size();
	buffer[0] = (char)((sz >>  0) & 0xFF);
	buffer[1] = (char)((sz >>  8) & 0xFF);
	buffer[2] = (char)((sz >> 16) & 0xFF);
	buffer[3] = (char)((sz >> 24) & 0xFF);
}

void Packet::rewind ()
{
	cursor = 4;
}

int Packet::readInt ()
{
	if ((cursor + 4) < buffer.size ()) {
		int n;

		n =  ((int)buffer [cursor] & 0xff);
		n |= ((int)buffer [cursor +1] & 0xff) << 8;
		n |= ((int)buffer [cursor +2] & 0xff) << 16;
		n |= ((int)buffer [cursor +3] & 0xff) << 24;
		cursor += 4;
		return n;
	}
	throw std::runtime_error ("Entero sin terminar.");
}

std::string Packet::readString ()
{
	unsigned end = cursor;
        while (end < buffer.size () && buffer[end] != 0)
		end++;

	if (end < buffer.size ()) {
		unsigned start = cursor;
		cursor = end + 1;
		return std::string (&buffer[start], end - start);
	}
	throw std::runtime_error ("Cadena sin terminar.");
}
