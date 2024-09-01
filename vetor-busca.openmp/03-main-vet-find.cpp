#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <climits>
#include <omp.h>
using namespace std;
#define ALING 64

bool find_linear(unsigned long size, unsigned long value, unsigned long *vet, unsigned long *out, double *elapsedtime){
    double et = 0.0f;
    unsigned long index = 0;
    bool found = false;
    et = omp_get_wtime();
    while ((index < size) && (!found)){
        if (value > vet[index])
            index++;
        else if (value < vet[index]){
            index = size;
        }else{
            *out = index;
            found = true;
        }
    }//while ((index < size) && (!found)){
    et = omp_get_wtime() - et;
    *elapsedtime = et;
    return found;
}


bool find_binary(unsigned long low, unsigned long high, unsigned long value, unsigned long *vet, unsigned long *out){
    unsigned long l = low, h = high;
    bool found = false;
    while ((l <= h) && (!found)){
        unsigned long pm = (h + l) / 2;
        if (vet[pm] == value){
            *out = pm;
            found = true;
        }else if(value < vet[pm]){
            if (pm > 0)
                h = pm - 1;
            else{
                h = 0;
                l = 1;
            }

        }else
            l = pm + 1;
        //cout << l << "," << h << "," << pm << endl;
    }//while (l < h) && (!found){


    return found;
}
// ./find.exec 31000 7864320099

int main (int ac, char **av){
    unsigned long *vet = NULL,
                  size = strtoul(av[1], NULL, 0),
                  v = ULLONG_MAX,
                  out = 0,
                  value = strtoul(av[2], NULL, 0);

    cout << endl << "\tPesquisa no vetor" << endl;

    size *= (1024 * 1024) / sizeof(unsigned long);
    cout << "               Tamanho:" << size * sizeof(unsigned long) << " em bytes " << endl;
    posix_memalign(reinterpret_cast <void**>(&vet), ALING, size * sizeof(unsigned long));
    for (unsigned long i = 0; i < size; i++){
        vet[i] = 100 +  (2 * i + 1);
    }

    cout << "       Valores ímpares: " << vet[0] << "," << vet[size-1] << endl;
    cout << "Valor a ser pesquisado: " << value << endl;


   // bool ret = find_binary(0, size, value, vet, &out);
    double elapsedtime = 0.0f;
    bool ret = find_linear(size, value, vet, &out, &elapsedtime);

    if (ret)
        cout << "Valor encontrado na posição: " << out << " valor -> " << vet[out] << endl;
    else
        cout << "Valor não encontrado!" << endl;
    cout << "Tempo de parede: " << elapsedtime << endl;
    free(vet);
    return EXIT_SUCCESS;
}
