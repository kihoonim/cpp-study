#include <iostream>

struct Box {
    double len;
    double width;
    double height;
};


class Volume {
public:
    double operator()(double x, double y, double z) {
        return x * y * x;
    }

    double operator()(const Box& box) {
        return box.len * box.width * box.height;
    }
};

int main() {
    Volume volume;
    Box box {1.0, 2.0, 3.0};
    std::cout << "box volume : "<<  volume(box) << std::endl;
}