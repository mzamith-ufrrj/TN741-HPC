#ifndef GOL_CPU_HPP
#define GOL_CPU_HPP
#include <ca-types.hpp>
#include <gol-cpu.hpp>
#include <string>
/*
 * Show the last CA state to console.
 */
void print2Console(stLattice *mLattice);
void InitRandness(stLattice *mLattice, double p);
/*
 * Game of Life computation rule - single thread approach
 * IPC: initial condition is called herein
 */
unsigned long CPU1T_GOL(stLattice *mLattice);
unsigned long CPUMT_GOL(stLattice *mLattice);
unsigned long CPU_GOL(stLattice *mLattice, std::string);
#endif
