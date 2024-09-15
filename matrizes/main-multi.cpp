#include <iostream>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>
#include <rural-mat.hpp>
using namespace std;

void saveLog(string logFile,
             unsigned int mem,
             double totalTime,
             double *threadsTime,
             unsigned int nThreads){

    fstream logout;
    FILE *ptr = NULL;
    struct stat buffer;
    int ret = stat(logFile.c_str(), &buffer);
    if (ret == -1){
        logout.open(logFile, fstream::trunc|fstream::out);
        //ptr = fopen(logFile.c_str(), "w+");
        assert(logout.is_open());
        logout << "memoria;";
        /*
        for (unsigned int i = 1; i <= nThreads; i++){
            logout << "thread_" << i << ";";
        }
        logout << "media;variancia;tempo_total" << endl;
        */
        logout << "threads;";
        logout << "tempo_total" << endl;
    }else{
        logout.open(logFile, fstream::app | fstream::out);
    }
    logout << mem << ";";
    /*
    double ave = 0.0f,
          vari = 0.0f;

    for (unsigned int i = 0; i < nThreads; i++){
        ave += threadsTime[i];
        logout << threadsTime[i] << ";";
    }

    logout << ave / static_cast<double>(nThreads) << ";";
    for (unsigned int i = 0; i < nThreads; i++){
        vari += ((threadsTime[i] - ave) * (threadsTime[i] - ave));
    }
    logout << vari / static_cast<double>(nThreads) << ";";
    */
    logout << nThreads << ";";
    logout << totalTime << endl;

    logout.close();
    cout << "\tLog file[" << logFile << "] saved" << endl;

}


int main (int ac, char **av){
    unsigned long mem = 0;
    stMatrix      A,
                  B,
                  C;

    string filename_matrix_A = av[1],
           filename_matrix_B = av[2],
           filename_matrix_C = av[3],
           filename_log      = av[4];
    bool show             = stoi(av[6]);
    unsigned int nThreads = stoi(av[5]);


    auto start_time = std::chrono::high_resolution_clock::now();
    cout << endl << "Multiplicação de matrizes" << endl;
    cout << "Matrizes:" << endl;
    cout << "\t A - arquivo: " << filename_matrix_A << endl;
    cout << "\t B - arquivo: " << filename_matrix_B << endl;
    cout << "\t C - arquivo: " << filename_matrix_C << endl;
    cout << "Threads: " << nThreads << endl;

    loadBinary(&A, filename_matrix_A);
    loadBinary(&B, filename_matrix_B);

    C.m = B.n;
    C.n = A.m;

    assert(posix_memalign(reinterpret_cast <void**>(&C.MAT), ALING, C.m *  C.n * sizeof(double)) == 0);


    memset(C.MAT, 0x00,  C.m *  C.n * sizeof(double));
    mem =  (A.m *  A.n + B.m *  B.n + C.m *  C.n) * sizeof(double);
    cout << "Total de memória usada: " << (mem / 1048576) << " Mbytes" << endl;

    matrix_multi(&C, &A, &B);
    if (show){
        cout << "Matrizes" << endl;
        cout << "A:" << endl;
        print2Console(&A);
        cout << "B:" << endl;
        print2Console(&B);
        cout << "C:" << endl;
        print2Console(&C);

    }

    /*
    for (unsigned int i = 0; i < nThreads; i++){
        cout << "\tTempo gasto pela thread " << i << " foi de " << elapsedtime[i] << " em segundos" << endl;
    }
    */
    print2Binary(&C, filename_matrix_C);
    free(A.MAT);
    free(B.MAT);
    free(C.MAT);

    auto stop_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_time = stop_time - start_time;
    cout << "\tTempo total de execução: " << total_time.count() << endl;

    //saveLog(filename_log, mem, total_time.count(), elapsedtime, nThreads);

    //chrono::hours, chrono::minutes, chrono::seconds, chrono::milliseconds, or chrono::microseconds.
    //auto elapsed = chrono::duration_cast<chrono::microseconds>(stop - start);
    //cout << elapsed.count() << endl;
    //saveLog(filename, mLattice.x, mLattice.y, mLattice.t, elapsed.count(), processorElapsedTime);
    return EXIT_SUCCESS;
}
