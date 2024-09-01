################################################################################
#
#  Universidade Federal Rural do Rio de Janeiro - UFRRJ
#  por: Marcelo Zamith - mzamith@ufrrj.br
#
################################################################################
EXEFILE   = exemplo.exec
CPUCC     = g++
CPPFLAGS  =
DEFS      = $(APPLICATION)  $(VERSION)
INCLUDES  = -I.
LIBDIR    = -L/usr/lib 
PAPILIBS  =
LIBS     =  -lm 
LINK     =  $(LIBDIR) $(LIBS) -static


ifeq ($(TARGET), release)
  DEFS      += 
  CPPFLAGS  +=  -O3 
else
  DEFS     += -D_DEBUG
  CPPFLAGS += -g -Wall -O0
endif

CPU_COMPILE = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS)


all:	loop-explicitly-optimization loop-implicitly-optimization loop-no-optimization main

	$(CPU_COMPILE)	 obj/loop-explicitly-optimization.o obj/loop-implicitly-optimization.o obj/loop-no-optimization.o obj/main.o $(LINK) -o $(EXEFILE)

main:
	$(CPU_COMPILE) -c main.cpp -o obj/main.o

loop-no-optimization:
	$(CPU_COMPILE)   -c loop-no-optimization.cpp -o obj/loop-no-optimization.o

loop-implicitly-optimization:
	$(CPU_COMPILE)   -c loop-implicitly-optimization.cpp -o obj/loop-implicitly-optimization.o

loop-explicitly-optimization:
	$(CPU_COMPILE)  -mavx -c loop-explicitly-optimization.cpp -o obj/loop-explicitly-optimization.o
 

clean:
	rm *.exec; rm obj/*.o

