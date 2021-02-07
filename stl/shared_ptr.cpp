#include <iostream>
#include <memory>

int main() {
    // create
    //std::shared_ptr<double> shared {new double{999.0}};
    auto shared = std::make_shared<double>(999.0);

    *shared = 8888.0;
    std::cout << "shared : " << *shared << std::endl;
    *shared = 8889.0;
    std::cout << "shared : " << *shared << std::endl;

    //std::shared_ptr<double> shared2 {shared};
    auto shared2 = shared;
    std::cout << "shared2 : " << *shared2 << std::endl;

    // get
    std::shared_ptr<double> shared_get {new double{999.0}};
    std::cout << "get : " << *(shared_get.get()) << std::endl;

    // initialize
    auto shared_init = std::make_shared<std::string>("khlim");
    std::cout << "init : " << *shared_init << std::endl;
    shared_init = nullptr;
    //shared_init.reset();
    std::cout << "init : " << (shared_init == nullptr) << std::endl;

    // reset
    auto shared_reset = std::make_shared<std::string>("khlim");
    shared_reset.reset(new std::string{"khlim2"});
    std::cout << "reset : " << *shared_reset << std::endl;

    // check equal
    auto shared_equal1 = std::make_shared<std::string>("khlim");
    auto shared_equal2 = shared_equal1;
    std::cout << "check equal : " << (shared_equal1 && (shared_equal1 == shared_equal2)) << std::endl;

    // check unique
    std::cout << "check unique : " << shared_equal1.unique() << std::endl;
    shared_equal2 = nullptr;
    std::cout << "check unique : " << shared_equal1.unique() << std::endl;

    // check count
    auto shared_equal3 = shared_equal1;
    auto shared_equal4 = shared_equal1;
    std::cout << "check count : " << shared_equal1.use_count() << std::endl;
}