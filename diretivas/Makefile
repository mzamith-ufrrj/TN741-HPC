CPUCC       = g++
CPPFLAGS    = -g  -fopenmp #-O3 #-fopenmp
DEFS        = -DALING=64
INCLUDES    = -I.
LIBDIR      =  #-L/opt/gnu-gcc/lib64
LIBS        = -lm #-lgomp

LINK        = $(LIBDIR) $(LIBS)
COMPILECPU  = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS)

all: 00-main-parallel-for 01-main-parallel-section

00-main-parallel-for:
	$(COMPILECPU) 00-main-parallel-for.cpp $(LINK)  -o parallel-for-omp.exec

01-main-parallel-section:
	$(COMPILECPU) 01-main-parallel-section.cpp $(LINK)  -o parallel-section-omp.exec

02-main-parallel-reduction:
	$(COMPILECPU) 02-main-parallel-reduction.cpp $(LINK)  -o parallel-reduction-omp.exec


clean:
	rm *.exec
