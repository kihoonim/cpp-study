#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <iterator>

void test1() {
    std::deque<int> a_deque;
    std::deque<int> my_deque(10);
    std::deque<std::string> words {"one", "none", "some", "all", "none", "most", "many"};
    std::deque<std::string> words_copy { words };
    std::deque<std::string> words_part { std::begin(words), std::begin(words) + 5 };
    std::cout << words.at(2) << std::endl;
}

void test2() {
    std::deque<int> numbers {2,3,4};
    numbers.push_front(11);
    numbers.push_back(12);
    numbers.pop_front();
}

void test3() {
    std::deque<std::string> words {"one", "two", "three", "four"};
    auto init_list = {std::string{"seven"}, std::string{"eignt"}, std::string{"nine"}};
    words.assign(init_list);
    std::deque<std::string> other_words;
    other_words = words;
    words = {"ten", "eleven"};
}

void test4() {
    std::deque<std::string> names;
    std::cout << "Enter : " << std::endl;
    std::copy(
        std::istream_iterator<std::string> {std::cin}, 
        std::istream_iterator<std::string> {}, 
        std::front_inserter(names));

    std::cout << "Out : " << std::endl;
    std::copy(
        std::begin(names), 
        std::end(names), 
        std::ostream_iterator<std::string> {std::cout, " "});
}

int main() {
    //test1();
    //test2();
    //test3();
    test4();
}