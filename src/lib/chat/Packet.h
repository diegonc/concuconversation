#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include <string>

#include <io/OutputStream.h>

class Packet
{
	private:
		std::vector<char> buffer;

		void update_size ();

	public:
		Packet ();

		void push (int i);
		void push (const std::string& s);

		void write (OutputStream& stream);
};

#endif
