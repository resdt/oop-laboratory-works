#include <iostream>
#include "money.h"

int main() {
    xyz::Money m("1.66");
    xyz::Money m2("02.34");
    std::cout << std::boolalpha << (m<=m2) << '\n';
    std::cout << m+m2 << '\n';
    std::cout << m2-m << '\n';
    xyz::Money m1{"100.00"};
    xyz::Money m3("0.01");
    std::cout << m1-m3 << '\n';
    xyz::Money none;
    std::cout << m-none << '\n';
    return 0;
}
