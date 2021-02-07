#include <iostream>
#include <memory>

int main() {

    // create
    //std::unique_ptr<std::string> pname {new std::string{"khlim"}};
    auto unique_create1 = std::make_unique<std::string>("khlim");
    auto unique_create2 = std::make_unique<std::string>(6, '*');

    std::cout << "create 1 : " << *unique_create1 << std::endl;
    std::cout << "create 2 : " << *unique_create2 << std::endl;

    // assign
    size_t len{10};
    //std::unique_ptr<int[]> pnumbers {new int[len]};
    auto unique_assign = std::make_unique<int[]>(len);
    
    for (size_t i = 0; i < len; i++) {
        unique_assign[i] = i * i;
    }
    
    for (size_t i = 0; i < len; i++) {
        std::cout << "assign : " << unique_assign[i] << std::endl;
    }

    // get
    auto unique_get1 = std::make_unique<std::string>(6, '*');
    auto unique_get2 = unique_get1.get();
    std::cout << "get : " << *unique_get2 << std::endl;

    // reset
    auto unique_reset = std::make_unique<std::string>("khlim");
    unique_reset.reset();
    std::cout << "reset 1 : " << (unique_reset == nullptr) << std::endl;
    unique_reset.reset(new std::string("khlim2"));
    std::cout << "reset 2 : " << *unique_reset << std::endl;

    // release
    auto unique_release1 = std::make_unique<std::string>("khlim");
    std::unique_ptr<std::string> unique_release2{unique_release1.release()};
    std::cout << "release 2 : " << *unique_release2 << std::endl;

    // swap
    auto unique_swap1 = std::make_unique<std::string>("khlim1");
    auto unique_swap2 = std::make_unique<std::string>("khlim2");
    unique_swap1.swap(unique_swap2);

    std::cout << "swap 1 : " << *unique_swap1 << std::endl;
    std::cout << "swap 2 : " << *unique_swap2 << std::endl;

    // null check
    auto unique_null = std::make_unique<std::string>("khlim");
    std::cout << "ckeck not null : " << (unique_null == nullptr) << std::endl;
    unique_null.reset();
    std::cout << "check null : " << (unique_null == nullptr) << std::endl;
}