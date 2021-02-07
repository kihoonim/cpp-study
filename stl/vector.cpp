#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <utility>

using std::vector;
using std::string;

void test1() {
    vector<string> words;
    words.reserve(10);

    std::cout << "IN : " << std::endl;
    std::copy(
        std::istream_iterator<string> {std::cin}, 
        std::istream_iterator<string> {}, 
        std::back_inserter(words));

    std::cout << "Start Sorting" << std::endl;
    bool out_of_order {false};
    auto last = std::end(words);
    while (true) {
        for (auto first = std::begin(words) + 1; first != last; ++first) {
            if (*(first - 1) > *first) {
                std::swap(*first, *(first - 1));
                out_of_order = true;
            }
        }
        if (!out_of_order) {
            break;
        }
        out_of_order = false;
    }

    std::cout << "Increm." << std::endl;
    std::copy(
        std::begin(words), 
        std::end(words), 
        std::ostream_iterator<string> {std::cout, ""});
    std::cout << std::endl;

    vector<string> words_copy {
        std::make_move_iterator(std::begin(words)), 
        std::make_move_iterator(std::end(words))};

    std::cout << "After Moved" << std::endl;
    std::copy(
        std::begin(words_copy), 
        std::end(words_copy),
        std::ostream_iterator<string> {std::cout, " "});
    std::cout << std::endl;

    std::cout << "words size : " << words.size() << std::endl;
    if (words.front().empty()) {
        std::cout << "First Is Empty" << std::endl;
    }
    std::cout << "First : " << words.front() << std::endl;
}

void test2() {
    std::vector<double> values;
    values.push_back(3.14);
    
    std::vector<std::string> words;
    words.push_back(string("adiabatic"));
    words.push_back("adiabatic");
    words.emplace_back("abstemious");

    std::string str {"alleged"};
    words.emplace_back(str, 2, 3);
}

void test3() {
    std::vector<std::string> words {"first", "second"};
    auto iter = words.emplace(++std::begin(words), 5, 'A');
    words.emplace(++iter, "$$$$");
}

void test4() {
    std::vector<std::string> words {"one", "three", "eight"};
    auto iter = words.insert(++std::begin(words), "two");
    std::string more[] {"five", "six", "seven"};
    iter = words.insert(--std::end(words), std::begin(more), std::end(more));
    iter = words.insert(std::end(words), "ten");
    iter = words.insert(std::cend(words) - 1, 2, "nine");
    iter = words.insert(std::end(words), {std::string{"twelve"}, std::string{"thirteen"}});
}

void test5() {
    std::vector<std::string> str {"one", "two", "one", "three"};
    auto riter = std::find(std::rbegin(str), std::rend(str), "one");
    str.insert(riter.base(), "five");
}

void test6() {
    std::vector<int> data(100, 99);
    //std::swap(std::begin(data) + 1, std::end(data) - 1);
    data.pop_back();
    data.clear();
}

void test7() {
    std::vector<int> data(100, 99);
    data.shrink_to_fit();
    //auto iter = data.erase(std::begin(data) + 1);
    auto iter = data.erase(std::begin(data) + 1, std::begin(data) + 3);
}

void test8() {
    std::vector<std::string> words {"one", "none", "some", "all", "none", "most", "many"};
    auto iter = std::remove(std::begin(words), std::end(words), "none");
    auto iter2 = words.erase(iter, std::end(words));
}

int main() {
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    //test6();
    //test7();
    test8();
}