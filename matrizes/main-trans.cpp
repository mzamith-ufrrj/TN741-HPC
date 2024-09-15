#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <rural-mat.hpp>
#include <chrono>

using namespace std;
void help (void){
    cout << "Programa exibir uma matriz" << endl;
    cout << "Exemplo: " << endl;

    cout << "\t./trans-mat.exec r4x5.bin saida.bin 0 1" << endl;
    cout << "\t                 |          |       | |--> Threads" << endl;
    cout << "\t                 |          |       |----> 0/1 exibe ou não a matriz de saída" << endl;
    cout << "\t                 |          |------------> Arquivo de saídas com a matriz transposta " << endl;
    cout << "\t                 |-----------------------> Arquivo com a matriz origianl " << endl;

}


int main (int ac, char **av){
    unsigned long mem = 0;
    double *elapsedtime = NULL;
    stMatrix A,
             B;
    if (ac != 5){
        help();
        return EXIT_SUCCESS;
    }
    string filename = av[1];
    string filename_transp = av[2];
    bool show = stoi(av[3]);
    unsigned int nThreads = stoi(av[4]);
    auto start_time = std::chrono::high_resolution_clock::now();
    cout << endl << "Matriz transposta" << endl;
    loadBinary(&A, filename);

    B.m = A.n;
    B.n = A.m;
    assert(posix_memalign(reinterpret_cast <void**>(&B.MAT), ALING, B.m *  B.n * sizeof(double)) == 0);
    bzero(B.MAT, B.m * B.n * sizeof(double));
    mem =  (A.m *  A.n + B.m *  B.n) * sizeof(double);
    cout << "Total de memória usada: " << (mem / 1048576) << " Mbytes" << endl;


    matrix_trans(&B, &A, nThreads, &elapsedtime);
    print2Binary(&B, filename_transp);

    cout << endl;
    if (show){
        for (int j = 0; j < B.n; j++){

            for (int i = 0; i < B.m; i++){
                int k = j * B.m + i;
                cout << setw(10) << fixed << setprecision(6) << B.MAT[k] << " ";
                //cout << setprecision(4) << A.MAT[k] << " ";
            }
            cout << endl;
        }
    }
    for (unsigned int i = 0; i < nThreads; i++){
        cout << "\tTempo gasto pela thread " << i << " foi de " << elapsedtime[i] << " em segundos" << endl;
    }


    free(B.MAT);
    free(A.MAT);
    free(elapsedtime);
    auto stop_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_time = stop_time - start_time;
    cout << "\tTempo total de execução: " << total_time.count() << endl;

    return EXIT_SUCCESS;
}
