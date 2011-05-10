#include <chat/PacketReader.h>

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
	} packet_size = {0};

	stream->read (4, &packet_size.bytes[0]);
	packet_size.number = packet_size.bytes[0]
		| (packet_size.bytes[1] << 8)
		| (packet_size.bytes[2] << 16)
		| (packet_size.bytes[3] << 24);

	std::auto_ptr<Packet> pkt (new Packet ());

	for (int i=0; i < packet_size.number - 4; i++) {
		char c;

		stream->read (1, &c);
		pkt->pushByte (c);
	}
	return pkt;
}
