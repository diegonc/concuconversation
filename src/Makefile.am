AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -O0 -g -Wall -Wextra -Wconversion
AM_CPPFLAGS = -I$(srcdir)/lib

libSources = \
	lib/chat/JoinMessage.cc \
	lib/chat/JoinMessage.h \
	lib/chat/Message.h \
	lib/chat/MessageFactory.cc \
	lib/chat/MessageFactory.h \
	lib/chat/MessageReader.cc \
	lib/chat/MessageReader.h \
	lib/chat/Packet.cc \
	lib/chat/Packet.h \
	lib/chat/PacketReader.cc \
	lib/chat/PacketReader.h \
	lib/chat/QuitMessage.cc \
	lib/chat/QuitMessage.h \
	lib/chat/SharedMessage.cc \
	lib/chat/SharedMessage.h \
	lib/chat/TextMessage.cc \
	lib/chat/TextMessage.h \
	lib/io/EOFException.h \
	lib/io/FifoInputStream.cc \
	lib/io/FifoInputStream.h \
	lib/io/FifoOutputStream.cc \
	lib/io/FifoOutputStream.h \
	lib/io/InputStream.h \
	lib/io/OutputStream.h \
	lib/system/EventHandler.h \
	lib/system/File.cc \
	lib/system/File.h \
	lib/system/FileExistsException.h \
	lib/system/IPCName.h \
	lib/system/Semaphore.cc \
	lib/system/Semaphore.h \
	lib/system/SharedBuffer.cc \
	lib/system/SharedBuffer.h \
	lib/system/SignalHandler.cc \
	lib/system/SignalHandler.h \
	lib/system/System.cc \
	lib/system/System.h \
	lib/utils/NonCopyable.h

clienteSources = \
	cliente/ArgParser.cc \
	cliente/ArgParser.h \
	cliente/Cliente.cc \
	cliente/Cliente.h \
	cliente/ConsoleManager.cc \
	cliente/ConsoleManager.h \
	cliente/SalonRemoto.cc \
	cliente/SalonRemoto.h \
	cliente/log4cxx/CursesAppender.cc \
	cliente/log4cxx/CursesAppender.h \
	cliente/main.cc

salonSources = \
	salon/ArgParser.cc \
	salon/ArgParser.h \
	salon/SalonServer.cc \
	salon/SalonServer.h \
	salon/UsuarioRemoto.cc \
	salon/UsuarioRemoto.h \
	salon/main.cc

bin_PROGRAMS = cliente/cliente salon/salon

cliente_cliente_SOURCES = $(clienteSources) $(libSources)
cliente_cliente_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/cliente $(LOG4CXX_CFLAGS)
cliente_cliente_LDADD = -lncurses $(LOG4CXX_LIBS)

salon_salon_SOURCES = $(salonSources) $(libSources)
salon_salon_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/salon $(LOG4CXX_CFLAGS)
salon_salon_LDADD = $(LOG4CXX_LIBS)
