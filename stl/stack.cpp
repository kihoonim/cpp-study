#include <iostream>
#include <stack>
#include <list>
#include <cmath>

inline size_t precedence(const char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    throw std::runtime_error {std::string{"invalid operator: "} + op};
}

double execute(std::stack<char>& ops, std::stack<double>& operands) {
    double result {};
    double rhs {operands.top()};
    operands.pop();
    double lhs {operands.top()};
    operands.pop();

    switch (ops.top()) {
    case '+':
        result = lhs + rhs;
        break;
    case '-':
        result = lhs - rhs;
        break;
    case '*':
        result = lhs * rhs;
        break;
    case '/':
        result = lhs / rhs;
        break;
    case '^':
        result = std::pow(lhs, rhs);
        break;
    default:
        throw std::runtime_error {std::string{"invalid operator:"} + ops.top()};
    }
    ops.pop();
    operands.push(result);
    return result;
}

void test1() {
    std::stack<std::string> words;
    std::stack<std::string, std::list<std::string>> fruit;

    std::list<double> values {1.4, 3.14, 2.7};
    std::stack<double, std::list<double>> my_stack(values);
    std::stack<double, std::list<double>> copy_stack {my_stack};
}

void test2() {
    std::stack<double> operands;
    std::stack<char> operators;
    std::string exp;
    
    try {
        while (true) {
            std::getline(std::cin, exp, '\n');
            if (exp.empty()) break;
        }
    }
}

int main() {
    test1();
    test2();
}