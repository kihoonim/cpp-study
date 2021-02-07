#include <numeric>
#include <iostream>
#include <iterator>

int main() {
    std:: cout 
    << std::accumulate(
        std::istream_iterator<double>(std::cin), 
        std::istream_iterator<double>(), 
        0.0) 
    << std::endl;
}