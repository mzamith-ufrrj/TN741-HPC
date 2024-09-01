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
/*
void saveLog(string logFile,
             int w,
             int h,
             int s,
             unsigned long total,
             unsigned long comput){

    fstream logout;
    FILE *ptr = NULL;
    struct stat buffer;
    int ret = stat(logFile.c_str(), &buffer);
    if (ret == -1){
        logout.open(logFile, fstream::trunc|fstream::out);
        //ptr = fopen(logFile.c_str(), "w+");
        assert(logout.is_open());
        logout << "width;height;steps;overhead_time_microseconds;comput_time_microseconds;total_time_microseconds" << endl;


    }else{
        logout.open(logFile, fstream::app | fstream::out);

    }
    unsigned long overhead = total - comput;

    logout << w << ";" << h << ";" << s << ";" << overhead << ";" << comput << ";" << total <<  endl;

    logout.close();
    cout << "Log file[" << logFile << "] saved" << endl;

}
*/

int main (int ac, char **av){
    unsigned long mem = 0;
    stMatrix A, B, C;
    string outfilename = av[3];
    bool show = stoi(av[4]);
    //unsigned long  processorElapsedTime = 0;
    //auto start = std::chrono::high_resolution_clock::now();


    cout << endl << "Multiplicação de matrizes" << endl;
    cout << "\t Arquivo com a matriz C: " << outfilename << endl;
    loadBinary(&A, av[1]);
    loadBinary(&B, av[2]);
    //loadBinary(&B, "B20x20-identity");

    // /p//rint2Console(&B);


    C.m = B.n;
    C.n = A.m;
    posix_memalign(reinterpret_cast <void**>(&C.MAT), ALING, C.m *  C.n * sizeof(double));
    memset(C.MAT, 0x00,  C.m *  C.n * sizeof(double));
    mem =  (A.m *  A.n + B.m *  B.n + C.m *  C.n) * sizeof(double);
    cout << "Total de memória usada: " << mem << " bytes" << endl;

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



    print2Binary(&C, outfilename);



    free(A.MAT);
    free(B.MAT);
    free(C.MAT);

    //auto stop = std::chrono::high_resolution_clock::now();

    //chrono::hours, chrono::minutes, chrono::seconds, chrono::milliseconds, or chrono::microseconds.
    //auto elapsed = chrono::duration_cast<chrono::microseconds>(stop - start);
    //cout << elapsed.count() << endl;
    //saveLog(filename, mLattice.x, mLattice.y, mLattice.t, elapsed.count(), processorElapsedTime);
    return EXIT_SUCCESS;
}
