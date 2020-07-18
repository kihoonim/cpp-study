#include <omp.h>
#include <iostream>
#include <list>
#include <unistd.h>
#include <thread>

using namespace std;

static void OpenMpProcessing (int n) {
    #pragma omp parallel for num_threads(n)
    for (int i = 0; i < 1000; i++) {
        cout << "Thread : " + to_string(omp_get_thread_num()) + " Processing : " + to_string(n) + "\n";
        usleep(10);   
    }
}
void Foo1() {
    thread t1(OpenMpProcessing, 10);
    thread t2(OpenMpProcessing, 20);
    thread t3(OpenMpProcessing, 30);
    thread t4(OpenMpProcessing, 40);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}


int main(int argc, char *argv[]) {
    Foo1();

    return 0;
}