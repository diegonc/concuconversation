AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -O0 -g
AM_CPPFLAGS = -I$(srcdir)/lib

libSources = \
	lib/System.cc \
	lib/File.h \
	lib/File.cc \
	lib/FifoOutputStream.h \
	lib/FifoOutputStream.cc \
	lib/System.h \
	lib/Salon.h \
	lib/Salon.cc \
	lib/FileExistsException.h \
	lib/OutputStream.h

clienteSources = \
	cliente/SalonRemoto.cc \
	cliente/SalonRemoto.h \
	cliente/main.cc

salonSources = \
	salon/main.cc

bin_PROGRAMS = cliente/cliente salon/salon

cliente_cliente_SOURCES = $(clienteSources) $(libSources)
cliente_cliente_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/cliente

salon_salon_SOURCES = $(salonSources) $(libSources)
salon_salon_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/salon

