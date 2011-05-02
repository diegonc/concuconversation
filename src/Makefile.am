AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -O0 -g
AM_CPPFLAGS = -I$(srcdir)/lib

libSources = \
	lib/chat/JoinMessage.cc \
	lib/chat/JoinMessage.h \
	lib/chat/Message.h \
	lib/chat/Packet.cc \
	lib/chat/Packet.h \
	lib/chat/QuitMessage.cc \
	lib/chat/QuitMessage.h \
	lib/chat/Salon.cc \
	lib/chat/Salon.h \
	lib/chat/TextMessage.cc \
	lib/chat/TextMessage.h \
	lib/io/FifoOutputStream.cc \
	lib/io/FifoOutputStream.h \
	lib/io/OutputStream.h \
	lib/system/File.cc \
	lib/system/File.h \
	lib/system/FileExistsException.h \
	lib/system/IPCName.h \
	lib/system/Semaphore.cc \
	lib/system/Semaphore.h \
	lib/system/SharedBuffer.cc \
	lib/system/SharedBuffer.h \
	lib/system/System.cc \
	lib/system/System.h

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

