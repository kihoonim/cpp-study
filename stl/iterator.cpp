#include <iterator>
#include <iostream>

int main() {
    int data[]{1,2,3,4,5};
    
    // advance
    auto iter_advance = std::begin(data);
    std::advance(iter_advance, 3);
    std::cout << "advance : " << *iter_advance << std::endl;

    // distance
    int size = std::distance(std::begin(data), std::end(data));
    std::cout << "distance : " << size << std::endl;

    // next
    auto iter_next = std::begin(data);
    auto next = std::next(iter_next, 2);
    std::cout << "next : " << *next << std::endl;

    // prev
    auto iter_prev = std::end(data);
    auto prev = std::prev(iter_prev, 3);
    std::cout << "prev : " << *prev << std::endl;
}