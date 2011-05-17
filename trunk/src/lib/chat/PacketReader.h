#ifndef PACKETREADER_H
#define PACKETREADER_H

#include <memory>

#include <chat/Packet.h>
#include <io/InputStream.h>
#include <log4cxx/logger.h>

class PacketReader
{
	private:
	static log4cxx::LoggerPtr logger;
		std::auto_ptr<InputStream> stream;

	public:
		PacketReader (std::auto_ptr<InputStream> stream);
		PacketReader (InputStream *stream);

		std::auto_ptr<Packet> readPacket ();
};

#endif
