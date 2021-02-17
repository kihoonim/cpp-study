#pragma once
#include <iostream>
#include <thread>

void foo() {
	printf("Hello from foo \n");
}

class callable_class {
public:
	void operator()() {
		printf("Hello from callable class \n");
	}
};

void run() {
	std::thread thread1(foo);
	callable_class obj;
	std::thread thread2(obj);

	thread1.join();
	thread2.join();

	printf("Hello from main \n");
}

void _1_4() {
	run();
}