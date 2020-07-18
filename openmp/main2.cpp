#include <omp.h>
#include <stdio.h>
#include <iostream>

using namespace std;


void foo1() {
    int t = true;
    int f = false;

    #pragma omp parallel if (f)
    //{ cout << "False " << omp_get_thread_num() << endl; }
    { printf ("FALSE: I am thread %d\n", omp_get_thread_num()); }

    #pragma omp parallel if (t)
    //{ cout << "True " << omp_get_thread_num() << endl; }
    { printf ("TRUE : I am thread %d\n", omp_get_thread_num()); }
}


int main(int argc, char *argv[]) {
    foo1();

    return 0;
}