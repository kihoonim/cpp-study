#include <iostream>
#include <csignal>
#include <csetjmp>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

jmp_buf gbuf1;
jmp_buf gbuf2;

class TestClass1 {
private: 
	mutex* m_ = nullptr;

public:
	TestClass1(mutex* m) {
		m_ = m;
		RegisterSignalHandler();
	}

	static void SignalHandler(int signum) {
		cout << "TestClass1 Signal : " << signum << endl;

		signal(signum, SignalHandler);

		longjmp(gbuf1, signum);
	}

	void RegisterSignalHandler() {
		signal(SIGABRT, SignalHandler);
		signal(SIGINT, SignalHandler);
	}

	void Run() {
		lock_guard<mutex> guard(*m_);

		try {
			int sig;
			if ((sig = setjmp(gbuf1)) == 0) {
				cout << "TestClass1 before raise\n";
				Sleep(2000);
				raise(SIGABRT);
				cout << "TestClass1 after raise\n";
			}
			else {
				throw(sig);
			}
		}
		catch (int& signum) {
			cerr << "TestClass1 Caught exception: " << signum << endl;
		}
	}
};

class TestClass2 {
private:
	mutex* m_ = nullptr;

public:
	TestClass2(mutex* m) {
		m_ = m;
		RegisterSignalHandler();
	}

	static void SignalHandler(int signum) {
		cout << "TestClass2 Signal : " << signum << endl;

		signal(signum, SignalHandler);

		longjmp(gbuf2, signum);
	}

	void RegisterSignalHandler() {
		signal(SIGABRT, SignalHandler);
		signal(SIGINT, SignalHandler);
	}

	void Run() {
		lock_guard<mutex> guard(*m_);

		try {
			int sig;
			if ((sig = setjmp(gbuf2)) == 0) {
				cout << "TestClass2 before raise\n";
				Sleep(2000);
				raise(SIGINT);
				cout << "TestClass2 after raise\n";
			}
			else {
				throw(sig);
			}
		}
		catch (int& signum) {
			cerr << "TestClass2 Caught exception: " << signum << endl;
		}
	}
};

void RunClass1(mutex* m) {
	TestClass1 class1(m);

	for (int i = 0; i < 10; i++) {
		thread t(&TestClass1::Run, &class1);
		//t.join();
	}
}

void RunClass2(mutex* m) {
	TestClass2 class2(m);

	for (int i = 0; i < 10; i++) {
		thread t(&TestClass2::Run, &class2);
		//t.join();
	}
}

int main() {
	mutex* m = new mutex();

	//thread t1(RunClass1, m);
	//thread t2(RunClass2, m);

	RunClass1(m);
	RunClass2(m);

	Sleep(60*60*1000);
}
