#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cmath>
#include <vector>

class Root {
public:
    double operator()(double x) { return std::sqrt(x); };
};

int main() {
    double data[] {1.5, 2.5, 3.5, 4.5, 5.5};
    double result[5];
    auto print = std::ostream_iterator<double>(std::cout, " ");

    // functor
    Root root;
    std::cout << "functor : " << std::endl;
    std::transform(std::begin(data), std::end(data), result, root);
    std::copy(std::begin(result), std::end(result), print);
    std::cout << std::endl << std::endl;

    // lambda
    std::cout << "lambda : " << std::endl;
    std::transform(std::begin(data), std::end(data), result, [](double x) { return std::sqrt(x); });
    std::copy(std::begin(result), std::end(result), print);
    std::cout << std::endl << std::endl;

    // function
    std::function<double(double)> op = [](double x) { return x * x; };
    std::cout << "function : " << std::endl;
    std::transform(std::begin(data), std::end(data), result, op);
    std::copy(std::begin(result), std::end(result), print);
    std::cout << std::endl << std::endl;

    // lambdas
    std::cout << "lambdas : " << std::endl;
    std::transform(std::begin(data), std::end(data), result, [&op](double x) { return op(x) * op(x); });
    std::copy(std::begin(result), std::end(result), print);
    std::cout << std::endl << std::endl;
}