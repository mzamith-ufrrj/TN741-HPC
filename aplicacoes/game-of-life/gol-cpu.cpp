#include <iostream>
#include <cassert>
#include <cstring>
#include <random>
#include <omp.h>
#include <ca-types.hpp>
#include <gol-cpu.hpp>
#include <chrono>
using namespace std;
/*
 * Show the last CA state to console.
 */
void print2Console(stLattice *mLattice)
{
    cout << endl;
    cout << "Last state: " << endl;
    for (int j = 0; j < mLattice->y; j++){
        for (int i = 0; i < mLattice->x; i++){
            int k = j * mLattice->x +  i;
            int v = static_cast<int> (mLattice->buff0[k]);
            cout << v;

        }//end-for (int j = 0; j < mLattice->height; j++){
        cout << endl;
    }//end-void InitRandness(tpLattice *mLattice, float p){


}

/*
 * Game of Life initial condition - random approach
 */
void InitRandness(stLattice *mLattice, double p){
    std::mt19937_64  generator (42); //64 bits
    uniform_real_distribution<double> unif(0, 1); //uniform distribuition
    memset(mLattice->buff0, 0x00,  mLattice->x * mLattice->y * sizeof(unsigned char));
    memset(mLattice->buff1, 0x00,  mLattice->x * mLattice->y * sizeof(unsigned char));

  for (int j = 0; j < mLattice->y; j++){
      for (int i = 0; i < mLattice->x; i++){
          int k = j * mLattice->x +  i;
          if (unif(generator) <= p)
                mLattice->buff0[k] = 1;
      }//end-  for (int i = 0; i < mLattice->width; i++){
  }//end-for (int j = 0; j < mLattice->height; j++){
}//end-void InitRandness(tpLattice *mLattice, float p){

unsigned long CPU1T_GOL(stLattice *mLattice){
    unsigned char nw = 0, n = 0,  ne = 0,
                  w  = 0, c = 0,  e  = 0,
                  sw = 0, s = 0, se  = 0,
                  sum;

        auto start = std::chrono::high_resolution_clock::now();

        for (int j = 0; j < mLattice->y; j++){
            int alphaJ = static_cast<int> (j-1 < 0);
            int minJ   = (alphaJ * (mLattice->y-1)) + ( (1 - alphaJ) * (j-1) );
            int maxJ   = (j+1) % mLattice->y;

            for (int i = 0; i < mLattice->x; i++){
               int alphaI = static_cast<int> (i-1 < 0);
               int minI   = (alphaI * (mLattice->x-1)) + ( (1 - alphaI) * (i-1) );
               int maxI   = (i+1) % mLattice->x;

                    c  = mLattice->buff0[j * mLattice->x  +  i];
                    nw = mLattice->buff0[minJ * mLattice->x  +  minI];
                    n  = mLattice->buff0[minJ * mLattice->x  +  i];
                    ne = mLattice->buff0[minJ * mLattice->x  +  maxI];
                    w  = mLattice->buff0[j    * mLattice->x  +  minI];
                    e  = mLattice->buff0[j    * mLattice->x  +  maxI];
                    sw = mLattice->buff0[maxJ * mLattice->x  +  minI];
                    s  = mLattice->buff0[maxJ * mLattice->x  +  i];
                    se = mLattice->buff0[maxJ * mLattice->x  +  maxI];

              sum = nw + n + ne + w + e + sw + s + se;
              //The GOL rule
              if ((sum == 3) && (c == 0))
                 mLattice->buff1[j  * mLattice->x  +  i] = 1;
              else if ((sum >= 2) && (sum <= 3) && (c == 1))
                 mLattice->buff1[j  * mLattice->x  +  i] = 1;
              else
                mLattice->buff1[j  * mLattice->x  +  i] = 0;

           }//for (int i = 0; i < mLattice->x; i+){
        }//for (int j = 0; j < mLattice->y; j++){

        unsigned char *swp = mLattice->buff0;
        mLattice->buff0 = mLattice->buff1;
        mLattice->buff1 = swp;

    auto stop = std::chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(stop - start).count();
}

//double acc  = 0.0f;
unsigned long CPUMT_GOL(stLattice *mLattice){
    double dstart;
    double dend;
    std::chrono::time_point<std::chrono::system_clock>start; // = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::system_clock>stop;
#pragma omp parallel shared(mLattice, start, stop)
{

    unsigned char nw = 0, n = 0,  ne = 0,
                  w  = 0, c = 0,  e  = 0,
                  sw = 0, s = 0, se  = 0,
                  sum;

        #pragma omp single
        {
            start = std::chrono::high_resolution_clock::now();
            dstart = omp_get_wtime();
        }
        #pragma omp barrier
        for (int j = 0; j < mLattice->y; j++){
            int alphaJ = static_cast<int> (j-1 < 0);
            int minJ   = (alphaJ * (mLattice->y-1)) + ( (1 - alphaJ) * (j-1) );
            int maxJ   = (j+1) % mLattice->y;
            #pragma omp for
            for (int i = 0; i < mLattice->x; i++){
               int alphaI = static_cast<int> (i-1 < 0);
               int minI   = (alphaI * (mLattice->x-1)) + ( (1 - alphaI) * (i-1) );
               int maxI   = (i+1) % mLattice->x;

                    c  = mLattice->buff0[j * mLattice->x  +  i];
                    nw = mLattice->buff0[minJ * mLattice->x  +  minI];
                    n  = mLattice->buff0[minJ * mLattice->x  +  i];
                    ne = mLattice->buff0[minJ * mLattice->x  +  maxI];
                    w  = mLattice->buff0[j    * mLattice->x  +  minI];
                    e  = mLattice->buff0[j    * mLattice->x  +  maxI];
                    sw = mLattice->buff0[maxJ * mLattice->x  +  minI];
                    s  = mLattice->buff0[maxJ * mLattice->x  +  i];
                    se = mLattice->buff0[maxJ * mLattice->x  +  maxI];

              sum = nw + n + ne + w + e + sw + s + se;
              //The GOL rule
              if ((sum == 3) && (c == 0))
                 mLattice->buff1[j  * mLattice->x  +  i] = 1;
              else if ((sum >= 2) && (sum <= 3) && (c == 1))
                 mLattice->buff1[j  * mLattice->x  +  i] = 1;
              else
                mLattice->buff1[j  * mLattice->x  +  i] = 0;

           }//for (int i = 0; i < mLattice->x; i+){
        }//for (int j = 0; j < mLattice->y; j++){
        #pragma omp barrier
        #pragma omp single
        {
            unsigned char *swp = mLattice->buff0;
            mLattice->buff0 = mLattice->buff1;
            mLattice->buff1 = swp;
            dend = omp_get_wtime();
            stop = std::chrono::high_resolution_clock::now();
        }

}//#pragma omp parallel shared(particles, nParticles)
    //acc += (dend - dstart);
    //cout << "OpenMP ET: " << acc << endl;
    return chrono::duration_cast<chrono::microseconds>(stop - start).count();
}

unsigned long CPU_GOL(stLattice *mLattice, string type){
    unsigned long processing = 0;
    unsigned long (*kernel)(stLattice *);
    if (type.compare("cpu_s") == 0) kernel = CPU1T_GOL;
    else kernel = CPUMT_GOL;
    for (int t = 0; t < mLattice->t; t++){
        processing += kernel(mLattice);
    }

    return processing;
}
