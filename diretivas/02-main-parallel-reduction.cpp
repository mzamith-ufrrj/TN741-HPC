#include <cassert>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <chrono>
#include <climits>
#include <omp.h>
#include <unistd.h>
#include <unistd.h>
using namespace std;
#define ALING 64


int main (int ac, char **av){
    unsigned long long sum = 0;
    unsigned long *vet = NULL,
                  size = strtoul(av[1], NULL, 0);

    unsigned int nThreads = stoi(av[2]);

    cout << endl << "\tRedução" << endl;
    size *= 1048576 / sizeof(unsigned long);
    cout << "               Tamanho:" << (size * sizeof(unsigned long)) / 1048576 << " em Mbytes " << endl;
    cout << "              Posições:" << size << endl;

    posix_memalign(reinterpret_cast <void**>(&vet), ALING, size * sizeof(unsigned long));
    omp_set_num_threads(nThreads);

    //#pragma omp parallel for
    for (unsigned long i = 0; i < size; i++){
        vet[i] = i + 1;
    }

    omp_set_num_threads(nThreads);
    #pragma omp parallel for shared(size, vet) reduction(+:sum)
    for (unsigned long i = 0; i < size; i++){
        sum += static_cast<unsigned long long> (vet[i]);
    }

    cout << "Resultado da soma: " <<  sum << endl;


    free(vet);

    return EXIT_SUCCESS;
}

