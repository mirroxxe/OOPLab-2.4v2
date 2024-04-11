#include <iostream>
#include "Fraction.h"

int main() {
    Fraction fraction1;
    Fraction fraction2(5);

    std::cout << "Enter fraction 1:" << std::endl;
    std::cin >> fraction1;
    std::cout << "Enter fraction 2:" << std::endl;
    std::cin >> fraction2;

    std::cout << "Fraction 1:" << std::endl;
    std::cout << fraction1 << std::endl;
    std::cout << "Fraction 2:" << std::endl;
    std::cout << fraction2 << std::endl;

    Fraction sum = fraction1 + fraction2;
    std::cout << "Sum of fractions:" << std::endl;
    std::cout << sum << std::endl;

    Fraction difference = fraction1 - fraction2;
    std::cout << "Difference of fractions:" << std::endl;
    std::cout << difference << std::endl;

    Fraction product = fraction1 * fraction2;
    std::cout << "Product of fractions:" << std::endl;
    std::cout << product << std::endl;

    std::cout << "Are fractions equal? " << (fraction1 == fraction2 ? "Yes" : "No") << std::endl;

    std::string fractionStr = static_cast<std::string>(fraction1);
    std::cout << "Fraction 1 as string: " << fractionStr << std::endl;

    return 0;
}
