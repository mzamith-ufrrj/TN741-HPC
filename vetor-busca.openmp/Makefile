CPUCC       = g++
CPPFLAGS    = -g #-O3 #-fopenmp
DEFS        = -DALING=64
INCLUDES    = -I.
LIBDIR      =  #-L/opt/gnu-gcc/lib64
LIBS        = -lm
MKDIR_P     = mkdir -p
OUT_DIR     = obj

LINK        = $(LIBDIR) $(LIBS)  -static #-static-libstdc++ -static-libgcc
COMPILECPU  = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS)

all: multi-mat-cpu generate-mat show-mat

show-mat: rural-mat main-show
	$(COMPILECPU) ${OUT_DIR}/rural-mat.o ${OUT_DIR}/main-show.o $(LINK)  -o show-mat.exec

generate-mat:  rural-mat main-gener
	$(COMPILECPU)  ${OUT_DIR}/rural-mat.o ${OUT_DIR}/main-gener.o $(LINK)  -o generate-mat.exec

multi-mat-cpu:  rural-mat main-multi
	$(COMPILECPU)  ${OUT_DIR}/rural-mat.o  ${OUT_DIR}/main-multi.o $(LINK) -o multi-mat-cpu.exec

main-show:
	$(COMPILECPU) -c main-show.cpp -o  ${OUT_DIR}/main-show.o

main-gener:
	$(COMPILECPU) -c main-gener.cpp -o  ${OUT_DIR}/main-gener.o

main-multi:
	$(COMPILECPU) -c main-multi.cpp -o  ${OUT_DIR}/main-multi.o

rural-mat:
	$(COMPILECPU) -c rural-mat.cpp -o  ${OUT_DIR}/rural-mat.o

directories:
	${MKDIR_P} ${OUT_DIR}

clean:
	rm  ${OUT_DIR}/*.o; rm *.exec
