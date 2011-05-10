#ifndef PACKETREADER_H
#define PACKETREADER_H

#include <memory>

#include <chat/Packet.h>
#include <io/InputStream.h>

class PacketReader
{
	private:
		std::auto_ptr<InputStream> stream;

	public:
		PacketReader (std::auto_ptr<InputStream> stream);
		PacketReader (InputStream *stream);

		std::auto_ptr<Packet> readPacket ();
};

#endif
