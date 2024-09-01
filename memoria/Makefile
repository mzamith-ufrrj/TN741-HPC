CPUC++      = g++ #/opt/gnu-gcc/bin/g++
CPPFLAGS    = -O3
DEFS        =
INCLUDES    = -I.  -I$(PAPI)/testlib -I$(PAPI)/include -I$(PAPI)/share/papi/testlib
LIBDIR      =
LIBS        = -lm
PAPI      = /opt/papi
LINK        = $(LIBDIR) $(LIBS) -static
COMPILE++   = $(CPUC++) $(DEFS) $(INCLUDES) $(CPPFLAGS)


all:   memory


memory:
	$(COMPILE++) -c memory.cpp -o obj/memory.o
	$(COMPILE++)  obj/memory.o    $(LINK) -o memory.exec  $(PAPI)/lib/libpapi.a

clean:
	rm obj/*.o; rm *.exec
