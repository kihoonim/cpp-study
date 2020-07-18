#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

void read() {
	std::ifstream file("", std::ios::binary);
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	if (file.is_open()) {
		std::vector<int> vec;
		std::string s;

		while (file) {
			std::getline(file, s);
			/*if (s.find("abc")) {
				vec.push_back(1);
			}
			else {
				vec.push_back(2);
			}*/
			std::cout << s << std::endl;
		}
	}
	else {
		std::cout << "Fail" << std::endl;
	}

	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	std::cout << "<<<<< Time" << sec.count() << "s" << std::endl;
}