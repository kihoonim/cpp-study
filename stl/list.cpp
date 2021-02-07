#include <iostream>
#include <list>
#include <vector>

void test1() {
    std::list<std::string> words;
    std::list<std::string> sayings {20};
    std::list<double> values(50, 3.14);
    std::list<double> save_values {values};
    std::list<double> samples {++std::cbegin(values), --std::cend(values)};
}

void test2() {
    std::list<std::string> names {"Jane", "Jim", "Jules", "Janet"};
    //names.push_front("Ian");
    //names.push_back("Kitty");
    names.emplace_front("Ian");
    names.emplace_back("Kitty");
}

void test3() {
    std::list<int> data(10, 55);
    data.insert(++begin(data), 66);
    auto iter = std::begin(data);
    std::advance(iter, 9);
    data.insert(iter, 3, 88);
    std::vector<int> numbers(10, 5);
    data.insert(--(--std::end(data)), std::cbegin(numbers), std::cend(numbers));
}

class my_greater {
public:
    bool operator()(const std::string& s1, const std::string& s2) {
        if (s1[0] == s2[0])
            return s1.length() > s2.length();
        else
            return s1 > s2;
    }
};

void test4() {
    std::list<std::string> names {"Jane", "Jim", "Jules", "Janet"};
    names.emplace_back("Ann");
    std::string name("Alan");
    names.emplace_back(std::move(name));
    names.emplace_front("Hugo");
    names.emplace(++std::begin(names), "Hannah");

    names.sort(std::greater<std::string>());
    names.sort(std::greater<>());
    names.sort(my_greater());
    names.sort([](const std::string s1, const std::string s2){
        if (s1[0] == s2[0])
            return s1.length() > s2.length();
        else
            return s1 > s2;
    });
}

void test5() {
    std::list<int> numbers {2,5,2,3,6,7,8,2,9};
    numbers.remove(2);
    numbers.remove_if([](int n) {return n%2 == 0;});
}

void test6() {
    std::list<std::string> words {"one", "two", "two", "two", "three", "four", "four"};
    words.unique();
}

void test7() {
    std::list<int> my_values {2,4,6,14};
    std::list<int> your_values {-2,1,7,10};
    my_values.merge(your_values);
    your_values.empty();
}

void test8() {
    std::list<std::string> my_words {"three", "six", "eight"};
    std::list<std::string> your_words {"seven", "four", "nine"};
    auto comp_str = [](const std::string s1, const std::string s2) { return s1[0] < s2[0]; };
    my_words.sort(comp_str);
    my_words.sort(comp_str);
    my_words.merge(your_words, comp_str);
}

void test9() {
    std::list<std::string> my_words {"three", "six", "eight"};
    std::list<std::string> your_words {"seven", "four", "nine"};
    my_words.splice(++std::begin(my_words), your_words, ++std::begin(your_words));
    your_words.splice(++std::begin(your_words), my_words, ++std::begin(my_words), std::end(my_words));
    my_words.splice(std::begin(my_words), your_words);
    your_words.splice(std::end(your_words), my_words);
}

void test10() {
    std::list<std::string> names {"Jane", "Jim", "Jules", "Janet"};
    names.emplace_back("Ann");
    std::string name("Alan");
    names.emplace_back(std::move(name));
    names.emplace_front("Hugo");
    names.emplace(++std::begin(names), "Hannah");
    for(const auto& name : names) {
        std::cout << name << std::endl;
    }
}

int main() {

}