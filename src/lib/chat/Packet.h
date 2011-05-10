#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include <string>

#include <io/OutputStream.h>

class Packet
{
	private:
		std::vector<char> buffer;
		int cursor;

		void update_size ();

	public:
		Packet ();

		void pushByte (char c);
		void pushInt (int i);
		void pushString (const std::string& s);

		void write (OutputStream& stream);

		void rewind ();
		int readInt ();
		std::string readString ();
};

#endif
