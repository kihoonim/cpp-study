#include <iostream>
#include <forward_list>
#include <utility>
using namespace std::rel_ops;

void test1() {
    std::forward_list<std::string> my_words {"three", "six", "eight"};
    auto count = std::distance(std::begin(my_words), std::end(my_words));
}

void test2() {
    std::forward_list<int> data {10, 21, 43, 87, 175, 351};
    auto iter = std::begin(data);
    size_t n {3};
    std::advance(iter, n);
    std::cout << n << " : " << *iter << std::endl;
}

void test3() {
    std::forward_list<std::string> my_words {"three", "six", "eight"};
    std::forward_list<std::string> your_words {"seven", "four", "nine"};
    my_words.splice_after(my_words.before_begin(), your_words, ++std::begin(your_words));
    my_words.splice_after(my_words.before_begin(), your_words, ++std::begin(your_words), std::end(your_words));
}

class Box {
private:
    size_t length {};
    size_t width {};
    size_t height {};

public:
    explicit Box(size_t l = 1, size_t w = 1, size_t h = 1) : length {l}, width {w}, height {h} {}
    double volume() const { return length * width * height; }
    bool operator < (const Box& box) { return volume() < box.volume(); }
    bool operator == (const Box& box) { return length == box.length && width == box.width && height == box.height; }

    friend std::istream& operator >> (std::istream& in, Box& box);
    friend std::ostream& operator << ()
};

int main() {

}