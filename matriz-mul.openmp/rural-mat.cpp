#include <iostream>
#include <cassert>
#include <cstring>
#include <ctime>
#include <random>
#include <chrono>
#include <rural-mat.hpp>
#include <cassert>
#include <fstream>
using namespace std;

/*
 * Show the last CA state to console.
 */
void print2Console(stMatrix *mat){
    cout << endl;
    cout << "Matriz: " << endl;

    for (int j = 0; j < mat->n; j++){
        cout << "\t";
        for (int i = 0; i < mat->m; i++){
            int k = j * mat->m +  i;
            cout << mat->MAT[k] << " ";
        }//end-for (int j = 0; j < mLattice->height; j++){
        cout << endl;
    }//end-void InitRandness(tpLattice *mLattice, float p){


}

void print2Binary(stMatrix *A, std::string filename){
    fstream output;
    output.open(filename, fstream::out | fstream::binary);
    assert(output.is_open());
    output.write(reinterpret_cast<char*>(&A->m), sizeof(A->m));
    output.write(reinterpret_cast<char*>(&A->n), sizeof(A->n));
    output.write(reinterpret_cast<char*>(A->MAT), sizeof(double) * A->m * A->n);

    output.close();
}

void loadBinary(stMatrix *A, std::string filename){
    fstream input;
    input.open(filename, fstream::in | fstream::binary);
    assert(input.is_open());
    double *a = NULL;
    input.read(reinterpret_cast<char*>(&A->m), sizeof(A->m));
    input.read(reinterpret_cast<char*>(&A->n), sizeof(A->n));
    posix_memalign(reinterpret_cast <void**>(&a), ALING, A->m *  A->n * sizeof(double));

    input.read(reinterpret_cast<char*>(a), sizeof(double) * A->m * A->n);

    A->MAT = a;
    input.close();
    //print2Console(A);
}


void matrix_multi(stMatrix *C, stMatrix *A, stMatrix *B){
   for (int j = 0; j < C->n; j++){
        for (int i = 0; i < C->m; i++){
            double c = 0.0f;
            for (int jA = 0; jA < A->m; jA++){
                int ak = j * A->m + jA;
                int bk = jA * B->m + i;
                c += A->MAT[ak] * B->MAT[bk];
            }//for (int jA = j; jA < A->m; jA++){

            int ck = j * C->m +  i;
            C->MAT[ck] = c;
        }//end-for (int j = 0; j < mLattice->height; j++){

    }//end-void InitRandness(tpLattice *mLattice, float p){

}

void create_mat_identity(stMatrix *A){
    for (int j = 0; j < A->n; j++){
        for (int i = 0; i < A->m; i++){
            double c = 0.0f;
            int k = j * A->m + i;
            A->MAT[k] = 0.0;
            if (j == i)
                A->MAT[k] = 1.0;
        }//for (int jA = j; jA < A->m; jA++){

    }//end-for (int j = 0; j < mLattice->height; j++){


}

void create_mat_dense(stMatrix *A){

    std::mt19937_64  generator (time(nullptr)); //64 bits
    uniform_real_distribution<double> unif(0, 1); //uniform distribuition
    for (int j = 0; j < A->n; j++){
        for (int i = 0; i < A->m; i++){
            double c = 0.0f;
            int k = j * A->m + i;
            A->MAT[k] = unif(generator) * 100.0f;

        }//for (int jA = j; jA < A->m; jA++){
    }//end-for (int j = 0; j < mLattice->height; j++){



}

/*
void matrix_multi(stMatrix *C, stMatrix *A, stMatrix *B){
   for (int j = 0; j < C->n; j++){

        for (int i = 0; i < C->m; i++){
            int ck = j * C->m +  i;
            double c = 0.0f;
            for (int jA = i; jA < A->m; jA++){
                int ak = j * A->m + jA;
                int bk = jA * B->m + i;
                c += A->MAT[ak] * B->MAT[bk];
            }//for (int jA = j; jA < A->m; jA++){
            C->MAT[ck] = c;
        }//end-for (int j = 0; j < mLattice->height; j++){

    }//end-void InitRandness(tpLattice *mLattice, float p){

}
*/
