#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <rural-mat.hpp>


using namespace std;
//apt install libfmt-dev
/*
 *  ./generate-mat-cpu.exec 10 10 1 r10x10.bin -> random
 * ./generate-mat-cpu.exec 10 10 0 i10x10.bin -> matriz identidade
 *
 */
int main (int ac, char **av){
    stMatrix A;
    string filename = av[1];
    cout << endl << "Matriz" << endl;
    loadBinary(&A, filename);
    cout << endl;
    for (int j = 0; j < A.n; j++){

        for (int i = 0; i < A.m; i++){
            int k = j * A.m + i;
            cout << setw(10) << fixed << setprecision(6) << A.MAT[k] << " ";
            //cout << setprecision(4) << A.MAT[k] << " ";
        }
        cout << endl;
    }


    free(A.MAT);
    return EXIT_SUCCESS;
}
