#include <iostream>
#include <memory>

int main() {
    // expire
    auto shared_expire = std::make_shared<std::string>("khlim");
    std::weak_ptr<std::string> weak_expire1 {shared_expire};
    std::weak_ptr<std::string> weak_expire2 {weak_expire1};

    std::cout << "weak1 : " << weak_expire1.expired() << std::endl;
    std::cout << "weak2 : " << weak_expire2.expired() << std::endl;

    shared_expire = nullptr;
    std::cout << "weak1 : " << weak_expire1.expired() << std::endl;
    std::cout << "weak2 : " << weak_expire2.expired() << std::endl;

    // lock
    auto shared_lock = std::make_shared<std::string>("khlim");
    std::weak_ptr<std::string> weak_lock {shared_lock};
    std::shared_ptr<std::string> shared_lock_new {weak_lock.lock()};

    std::cout << "lock : " << *shared_lock_new << std::endl;
    shared_lock = nullptr;
    std::cout << "lock : " << *shared_lock_new << std::endl;
}
