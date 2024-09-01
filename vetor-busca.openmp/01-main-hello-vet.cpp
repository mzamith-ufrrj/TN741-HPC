#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <random>
#include <omp.h>
#include <unistd.h>
#define ALING 64
using namespace std;

void wVet(unsigned int *vetA, unsigned int size){

    #pragma omp parallel for
    for (unsigned int i = 0; i < size; i++){
        vetA[i] = omp_get_thread_num();
    }
}

void wVet2(unsigned int *vetA, unsigned int size){
    unsigned int a = 0,
                 b = 0;

    cout << "Como indexar diretamente o vetor com as threads" << endl;


#pragma omp parallel private (a, b) shared (size)
{
    unsigned int subsize = size / omp_get_num_threads(),
                 residual = 0;



    if (omp_get_thread_num() == omp_get_num_threads() - 1){
        residual = size % omp_get_num_threads();
    }

    a = subsize * omp_get_thread_num();
    b = subsize * (omp_get_thread_num() + 1) + residual;

    usleep(1000 * omp_get_thread_num());

    for (unsigned int i = a; i < b; i++){
        vetA[i] = omp_get_thread_num();
    }

}//Fim do bloco em paralelo

}


int main (int ac, char **av){
    unsigned int *vetA  = NULL,
                 size = stoi(av[2]),
                 nthread = stoi(av[1]);

    assert(nthread <= size);
    cout << endl << "Exemplo de manipulação de vetor" << endl;
    posix_memalign(reinterpret_cast <void**>(&vetA), ALING, size * sizeof(unsigned int));

    omp_set_num_threads(nthread);
    //wVet(vetA, size);
    wVet2(vetA, size);

    for (unsigned int i = 0; i < size; i++){
        cout << i << " -> " << vetA[i] << endl;
    }
    free(vetA);
    return EXIT_SUCCESS;
}
