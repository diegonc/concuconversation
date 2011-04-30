#include <Packet.h>

Packet::Packet ()
{
	/* Reserva el primer entero para el tamaño. */
	push (0);
}

void Packet::push (int i)
{
	buffer.push_back ( (i >>  0) & 0xFF );
	buffer.push_back ( (i >>  8) & 0xFF );
	buffer.push_back ( (i >> 16) & 0xFF );
	buffer.push_back ( (i >> 24) & 0xFF );
}

void Packet::push (const std::string& s)
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
