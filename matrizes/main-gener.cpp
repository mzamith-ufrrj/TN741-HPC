#include <iostream>
#include <iomanip>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <cstring>
#include <random>
#include <cstdio>
#include <rural-mat.hpp>


using namespace std;
void help (void){
    cout << "Programa para gerar matrizes aleatórias e identidade" << endl;
    cout << "Exemplo: " << endl;

    cout << "\t./generate-mat-cpu.exec 10 10 1 r10x10.bin" << endl;
    cout << "\t                         |  | |  |-----> Arquivo binário com a matriz " << endl;
    cout << "\t                         |  | |--------> 1 indica matriz randomica e 0 identidade " << endl;
    cout << "\t                         |--|----------> respectivamente colunas e linhas da matriz"  << endl;
}

/*
 *  ./generate-mat-cpu.exec 10 10 1 r10x10.bin -> random
 * ./generate-mat-cpu.exec 10 10 0 i10x10.bin -> matriz identidade
 *
 */
int main (int ac, char **av){

    stMatrix A;
    if (ac != 5){
        help();
        return EXIT_SUCCESS;
    }

    string filename = av[4], smatType;
    A.m = stoi(av[1]);
    A.n = stoi(av[2]);
    int matType = stoi(av[3]);
    if (matType == 0){
        smatType = "IDENTITY";
    }else if (matType == 1){
        smatType = "RANDOM DENSE";

    }



    cout << endl << "Gerando matriz" << endl;
    cout << "\tMatriz (" << A.m << "," << A.n << ") \t Type: " << smatType <<  endl;
    cout << "\t File name: " << filename << endl;
    posix_memalign(reinterpret_cast <void**>(&A.MAT), ALING, A.m *  A.n * sizeof(double));
    memset(A.MAT, 0x00,  A.m *  A.n * sizeof(double));

    if (matType == 0){
        create_mat_identity(&A);
    }else if (matType == 1){
        create_mat_dense(&A);
    }

    print2Binary(&A, filename);
    free(A.MAT);
    return EXIT_SUCCESS;
}
