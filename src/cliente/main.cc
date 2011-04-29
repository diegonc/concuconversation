#include <SalonRemoto.h>
#include <Message.h>

class MyMessage : public Message
{
	public:
		void write (OutputStream& stream) const
		{
			stream.write (13, "test message\n");
		}
};

int main (int argc, char **argv)
{
	SalonRemoto salon(std::string("test"));

	salon.post (MyMessage());
	return 0;
}
