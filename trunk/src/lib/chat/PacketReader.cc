#include <chat/PacketReader.h>
#include <io/EOFException.h>

log4cxx::LoggerPtr PacketReader::logger (log4cxx::Logger::getLogger ("PacketReader"));

PacketReader::PacketReader (std::auto_ptr<InputStream> stream)
	: stream (stream)
{
}

PacketReader::PacketReader (InputStream *stream)
	: stream (stream)
{
}

std::auto_ptr<Packet> PacketReader::readPacket ()
{
	union {
		char bytes[4];
		int  number;
	} packet_size = {{0}};
	LOG4CXX_DEBUG(logger,"tomando cosas del stream.");
	if (!stream->read (4, &packet_size.bytes[0]))
		throw EOFException ();
	packet_size.number = packet_size.bytes[0]
		| (packet_size.bytes[1] << 8)
		| (packet_size.bytes[2] << 16)
		| (packet_size.bytes[3] << 24);

	std::auto_ptr<Packet> pkt (new Packet ());

	for (int i=0; i < packet_size.number - 4; i++) {
		char c;

		if (!stream->read (1, &c))
			throw EOFException ();
		pkt->pushByte (c);
	}
	return pkt;
}
