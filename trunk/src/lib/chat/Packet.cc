#include <stdexcept>

#include <chat/Packet.h>

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
	buffer.push_back ( (i >>  0) & 0xFF );
	buffer.push_back ( (i >>  8) & 0xFF );
	buffer.push_back ( (i >> 16) & 0xFF );
	buffer.push_back ( (i >> 24) & 0xFF );
}

void Packet::pushString (const std::string& s)
{
	for (int i=0; i < s.size(); i++)
		buffer.push_back (s[i]);
	/* null terminated */
	buffer.push_back (0);
}

void Packet::write (OutputStream& stream)
{
	update_size ();
	stream.write (buffer.size(), &buffer[0]);
}

void Packet::update_size ()
{
	int sz = buffer.size();
	buffer[0] = (sz >>  0) & 0xFF;
	buffer[1] = (sz >>  8) & 0xFF;
	buffer[2] = (sz >> 16) & 0xFF;
	buffer[3] = (sz >> 24) & 0xFF;
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
	int end = cursor;
        while (end < buffer.size () && buffer[end] != 0)
		end++;

	if (end < buffer.size ()) {
		int start = cursor;
		cursor = end + 1;
		return std::string (&buffer[start], end - start);
	}
	throw std::runtime_error ("Cadena sin terminar.");
}
