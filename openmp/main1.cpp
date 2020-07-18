#include <omp.h>
#include <stdio.h>
#include <iostream>

using namespace std;


void foo1() {
    #pragma omp parellel 
    {
        cout << "Hello World" 
        << "\nThread Index" << omp_get_thread_num()
        << "\nThread Count" << omp_get_num_threads()
        << endl;
    }
}

void foo2() {
    const int MAX = 100;
    double res[MAX];

    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < MAX; i++) {
            cout << i 
            << " " << omp_get_thread_num()
            << endl;

            res[i] = i;
        }
    }
}

void foo3() {
    double ZZ, res=0.0;

    #pragma omp parallel for reduction(+:res) private (ZZ)
    for (int i = 0; i < 100; i++) {
        ZZ = i;
        res = res + ZZ;
    }

    cout << res << endl;
}

int main(int argc, char *argv[]) {
    //foo1();
    foo2();
    foo3();
    return 0;
}