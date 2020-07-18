#include <omp.h>
#include <iostream>
#include <list>
#include <unistd.h>

using namespace std;

static void processElement (unsigned n) {
    #pragma omp critical
    cout
    << "Thread : " << omp_get_thread_num()
    << "Processing : " << n
    << endl;

    usleep(n * 1000);
}

void foo1() {
    list<unsigned> lst;

    for (unsigned u = 0; u < 16; ++u){
        lst.push_back(1 + u);
    }
}


int main(int argc, char *argv[]) {
    foo1();

    return 0;
}