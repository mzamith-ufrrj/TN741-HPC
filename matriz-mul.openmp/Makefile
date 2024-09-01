CPUCC       = g++
CPPFLAGS    = -g #-O3 #-fopenmp
DEFS        = -DALING=64
INCLUDES    = -I.
LIBDIR      =  #-L/opt/gnu-gcc/lib64
LIBS        = -lm

LINK        = $(LIBDIR) $(LIBS)  -static #-static-libstdc++ -static-libgcc
COMPILECPU  = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS)

all: multi-mat-cpu generate-mat show-mat

show-mat: rural-mat main-show
	$(COMPILECPU) obj/rural-mat.o obj/main-show.o $(LINK)  -o show-mat.exec

generate-mat:  rural-mat main-gener
	$(COMPILECPU) obj/rural-mat.o obj/main-gener.o $(LINK)  -o generate-mat.exec

multi-mat-cpu:  rural-mat main-multi
	$(COMPILECPU) obj/rural-mat.o obj/main-multi.o $(LINK) -o multi-mat-cpu.exec

main-show:
	$(COMPILECPU) -c main-show.cpp -o obj/main-show.o

main-gener:
	$(COMPILECPU) -c main-gener.cpp -o obj/main-gener.o

main-multi:
	$(COMPILECPU) -c main-multi.cpp -o obj/main-multi.o

rural-mat:
	$(COMPILECPU) -c rural-mat.cpp -o obj/rural-mat.o


clean:
	rm obj/*.o; rm *.exec
