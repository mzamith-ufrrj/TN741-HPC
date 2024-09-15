#include <iostream>
#include <iomanip>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <cstring>
#include <random>
#include <App.h>
#include <ca-types.hpp>
#include <gol-cpu.hpp>
#include <cstdio>
#include <chrono>
using namespace std;

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
/*
 * ./GOL-Benchmarking.exec 1024 8192 100 test.csv [cpu_s/cpu_m] 1
 *                           |    |   |     |        |   |----> [0 or 1] defines output binary file to compare
 *                           |    |   |     |        |--------> cpu_s or cpu_m use cpu single or multicore.
 *                           |    |   |     |-----------------> log file used to statistic
 *                           |    |   |-----------------------> timesteps
 *                           |----|---------------------------> width and height of Cellular Automata mesh
 */
int main (int ac, char **av){

    stLattice mLattice;
    bool  flagSave = stoi(av[5]);
    //Inicializa variável
    mLattice.x   = stoi(av[1]);
    mLattice.y   = stoi(av[2]);
    mLattice.t   = stoi(av[3]);
    string filename = av[4];
    string type     = av[5];
    unsigned long  processorElapsedTime = 0;
    auto start = std::chrono::high_resolution_clock::now();


    cout << endl << "GAME OF LIFE" << endl;
    cout << "\tDomain( x = " << mLattice.x << ",y = " <<  mLattice.y << ",t = " <<  mLattice.t << ")" << endl;
    cout << "Log file: " << filename  << endl;

    unsigned long mem =  mLattice.x *  mLattice.y * sizeof(unsigned char);
    //Allocing align
    posix_memalign(reinterpret_cast <void**>(&mLattice.buff0), ALING, mem);
    posix_memalign(reinterpret_cast <void**>(&mLattice.buff1), ALING, mem);

    InitRandness(&mLattice, 0.25);
    //print2Console(&mLattice);



    processorElapsedTime = CPU_GOL(&mLattice, type);


    //print2Console(&mLattice);

    if (flagSave){
        string logBinFile = filename + ".bin";
        cout << "Saving binary output to compare [" << logBinFile << "]" << endl;
        fstream output;
        output.open(logBinFile, fstream::out | fstream::binary);
        output.write(reinterpret_cast <const char*>(mLattice.buff0), mem);
        output.close();
    }

    free(mLattice.buff0);
    free(mLattice.buff1);
    auto stop = std::chrono::high_resolution_clock::now();

    //chrono::hours, chrono::minutes, chrono::seconds, chrono::milliseconds, or chrono::microseconds.
    auto elapsed = chrono::duration_cast<chrono::microseconds>(stop - start);
    //cout << elapsed.count() << endl;
    saveLog(filename, mLattice.x, mLattice.y, mLattice.t, elapsed.count(), processorElapsedTime);
    return EXIT_SUCCESS;
}
