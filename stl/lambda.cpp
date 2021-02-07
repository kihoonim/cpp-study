#include <iostream>
#include <functional>

template <typename ForwardIter, typename F>
void change(ForwardIter first, ForwardIter last, F fun) {
    for(auto iter = first; iter != last; ++iter) {
        *iter = fun(*iter);
    } 
}

int main() {
    // functor
    //auto cube = [] (double value) -> double { return value * value * value; };
    auto cube = [] (double value) { return value * value * value; };

    double x = 2.5;
    std::cout << "cube : " << cube(x) << std::endl;
 
    // change
    int data[] {1,2,3,4,5};
    change(std::begin(data), std::end(data), [] (int value) { return value * value; });

    for (auto iter = std::begin(data); iter != std::end(data); ++iter) {
        std::cout << "change : " << *iter << std::endl;
    }

    // function
    std::function<double(double)> op { [] (double value) { return value * value * value; }};
    op = [] (double value) { return value * value; };
    std::cout << "function : " << op(2.5) << std::endl;

    // capture
    double val1 = 10;
    double val2 = 20;
    std::function<double(double)> fun;

    fun = [=] (double value) mutable -> double{ 
        std::cout << "fun = in val1 : " << val1 << std::endl;
        std::cout << "fun = in val2 : " << val2 << std::endl;
        val1 *= 10;
        val2 *= 10;
        return value; 
    };
    fun(2.0);
    std::cout << "fun = out val1 : " << val1 << std::endl;
    std::cout << "fun = out val2 : " << val2 << std::endl;

    fun = [&] (double value) mutable -> double{ 
        std::cout << "fun & in val1 : " << val1 << std::endl;
        std::cout << "fun & in val2 : " << val2 << std::endl;
        val1 *= 10;
        val2 *= 10;
        return value; 
    };
    fun(2.0);
    std::cout << "fun & out val1 : " << val1 << std::endl;
    std::cout << "fun & out val2 : " << val2 << std::endl;

    fun = [=, &val1] (double value) mutable -> double{ 
        std::cout << "fun =& in val1 : " << val1 << std::endl;
        std::cout << "fun =& in val2 : " << val2 << std::endl;
        val1 *= 10;
        val2 *= 10;
        return value; 
    };
    fun(2.0);
    std::cout << "fun =& out val1 : " << val1 << std::endl;
    std::cout << "fun =& out val2 : " << val2 << std::endl;

    fun = [&, val1] (double value) mutable -> double{ 
        std::cout << "fun &= in val1 : " << val1 << std::endl;
        std::cout << "fun &= in val2 : " << val2 << std::endl;
        val1 *= 10;
        val2 *= 10;
        return value; 
    };
    fun(2.0);
    std::cout << "fun &= out val1 : " << val1 << std::endl;
    std::cout << "fun &= out val2 : " << val2 << std::endl;
}