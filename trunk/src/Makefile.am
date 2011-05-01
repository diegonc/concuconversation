AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -O0 -g
AM_CPPFLAGS = -I$(srcdir)/lib

libSources = \
	lib/FifoOutputStream.cc \
	lib/FifoOutputStream.h \
	lib/File.cc \
	lib/File.h \
	lib/FileExistsException.h \
	lib/JoinMessage.cc \
	lib/JoinMessage.h \
	lib/TextMessage.cc \
	lib/TextMessage.h \
	lib/QuitMessage.cc \
	lib/QuitMessage.h \
	lib/Message.h \
	lib/OutputStream.h \
	lib/Packet.h \
	lib/Packet.cc \
	lib/Salon.cc \
	lib/Salon.h \
	lib/System.cc \
	lib/System.h

clienteSources = \
	cliente/Cliente.cc \
	cliente/Cliente.h \
	cliente/SalonRemoto.cc \
	cliente/SalonRemoto.h \
	cliente/main.cc

salonSources = \
	salon/main.cc

bin_PROGRAMS = cliente/cliente salon/salon

cliente_cliente_SOURCES = $(clienteSources) $(libSources)
cliente_cliente_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/cliente
cliente_cliente_LDADD = -lncurses

salon_salon_SOURCES = $(salonSources) $(libSources)
salon_salon_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/salon

