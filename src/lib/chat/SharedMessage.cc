#include <chat/SharedMessage.h>
#include <chat/MessageReader.h>
#include <io/InputStream.h>
#include <io/OutputStream.h>

class ArrayOutputStream : public OutputStream
{
	unsigned size;
	unsigned cursor;
	char *array;

	public:
		ArrayOutputStream (char *b, unsigned s)
			: size (s), cursor (0), array (b) { }

		void write (size_t n, const char *data);
};

void ArrayOutputStream::write (size_t n, const char *data)
{
	if ( (size - cursor) > n) {
		memcpy (&array[cursor], data, n);
		cursor += n;
	} /*TODO: excepcion si no hay espacio? */
}

class ArrayInputStream : public InputStream
{
	unsigned size;
	unsigned cursor;
	char *array;

	public:
		ArrayInputStream (char *b, unsigned s)
			: size (s), cursor (0), array (b) { }

		bool read (size_t n, char *data);
};

bool ArrayInputStream::read (size_t n, char *data)
{
	if ( (size - cursor) > n) {
		memcpy (data, &array[cursor], n);
		cursor += n;
		return true;
	}
	return false;
}

void SharedMessage::set (const Message& msg)
{
	SharedMessage::Buffer& b = buffer.get ();
	ArrayOutputStream stream (&b[0], sizeof (b));
	msg.write (stream);
}

std::auto_ptr<Message> SharedMessage::get ()
{
	SharedMessage::Buffer& b = buffer.get ();
	MessageReader reader (
		new PacketReader (new ArrayInputStream (&b[0], sizeof (b))),
		new MessageFactory ());

	return reader.readMessage ();
}
