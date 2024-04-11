#include "Fraction.h"
#include <iostream>
#include <string>

Fraction::Fraction() : size(0) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        integerPart[i] = 0;
        decimalPart[i] = 0;
    }
}

Fraction::Fraction(int size) : size(size) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        integerPart[i] = 0;
        decimalPart[i] = 0;
    }
}

Fraction::Fraction(const Fraction& other) : size(other.size) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        integerPart[i] = other.integerPart[i];
        decimalPart[i] = other.decimalPart[i];
    }
}

int Fraction::getSize() const {
    return size;
}

void Fraction::setSize(int size) {
    this->size = size;
}

void Fraction::setIntegerDigit(int index, unsigned char digit) {
    if (index >= 0 && index < MAX_DIGITS) {
        integerPart[index] = digit;
    }
}

unsigned char Fraction::getIntegerDigit(int index) const {
    if (index >= 0 && index < MAX_DIGITS) {
        return integerPart[index];
    }
    return 0;
}

void Fraction::setDecimalDigit(int index, unsigned char digit) {
    if (index >= 0 && index < MAX_DIGITS) {
        decimalPart[index] = digit;
    }
}

unsigned char Fraction::getDecimalDigit(int index) const {
    if (index >= 0 && index < MAX_DIGITS) {
        return decimalPart[index];
    }
    return 0;
}

Fraction Fraction::operator+(const Fraction& other) const {
    int maxSize = std::max(size, other.size);
    Fraction result(maxSize);

    int carry = 0;
    for (int i = maxSize - 1; i >= 0; --i) {
        int sum = carry + integerPart[i] + other.integerPart[i];
        result.integerPart[i] = sum % 10;
        carry = sum / 10;
    }

    for (int i = 0; i < maxSize; ++i) {
        int sum = carry + decimalPart[i] + other.decimalPart[i];
        result.decimalPart[i] = sum % 10;
        carry = sum / 10;
    }

    return result;
}

Fraction Fraction::operator-(const Fraction& other) const {
    int maxSize = std::max(size, other.size);
    Fraction result(maxSize);

    int borrow = 0;
    for (int i = maxSize - 1; i >= 0; --i) {
        int diff = integerPart[i] - other.integerPart[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.integerPart[i] = diff;
    }

    for (int i = 0; i < maxSize; ++i) {
        int diff = decimalPart[i] - other.decimalPart[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.decimalPart[i] = diff;
    }

    return result;
}

Fraction Fraction::operator*(const Fraction& other) const {
    Fraction result(size + other.size);

    int maxDecimalDigits = std::max(size, other.size);

    int* temp = new int[result.size * 2];
    std::fill(temp, temp + result.size * 2, 0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            temp[i + j] += integerPart[i] * other.integerPart[j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            temp[i + j + 1] += integerPart[i] * other.decimalPart[j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            temp[i + j + 1] += decimalPart[i] * other.integerPart[j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            temp[i + j + 2] += decimalPart[i] * other.decimalPart[j];
        }
    }

    for (int i = result.size * 2 - 1; i > 0; --i) {
        temp[i - 1] += temp[i] / 10;
        temp[i] %= 10;
    }

    for (int i = 0; i < result.size; ++i) {
        result.integerPart[i] = temp[i];
    }

    for (int i = 0; i < maxDecimalDigits; ++i) {
        result.decimalPart[i] = temp[result.size + i];
    }

    delete[] temp;

    return result;
}

bool Fraction::operator==(const Fraction& other) const {
    bool integerPartsEqual = std::equal(integerPart, integerPart + size, other.integerPart);
    bool decimalPartsEqual = std::equal(decimalPart, decimalPart + size, other.decimalPart);

    return integerPartsEqual && decimalPartsEqual;
}

void Fraction::Read() {
    std::string input;

    std::cout << "Enter the integer part of the fraction: ";
    std::cin >> input;

    size = input.length();
    for (int i = 0; i < size; ++i) {
        integerPart[i] = input[i] - '0';
    }

    std::cout << "Enter the decimal part of the fraction: ";
    std::cin >> input;

    size = std::max(size, static_cast<int>(input.length()));
    for (int i = 0; i < size; ++i) {
        decimalPart[i] = (i < input.length()) ? input[i] - '0' : 0;
    }
}

void Fraction::Display() const {
    std::cout << "Fraction: ";
    for (int i = 0; i < size; ++i) {
        std::cout << static_cast<int>(integerPart[i]);
    }

    std::cout << ".";
    for (int i = 0; i < size; ++i) {
        std::cout << static_cast<int>(decimalPart[i]);
    }
    std::cout << std::endl;
}

std::string Fraction::ToString() const {
    std::string result = "Fraction: ";
    for (int i = 0; i < size; ++i) {
        result += std::to_string(integerPart[i]);
    }

    result += ".";
    for (int i = 0; i < size; ++i) {
        result += std::to_string(decimalPart[i]);
    }
    return result;
}

unsigned char* Fraction::operator[](int index) {
    if (index == 0) {
        return integerPart;
    }
    else {
        return decimalPart;
    }
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        size = other.size;
        for (int i = 0; i < MAX_DIGITS; ++i) {
            integerPart[i] = other.integerPart[i];
            decimalPart[i] = other.decimalPart[i];
        }
    }
    return *this;
}

Fraction::operator std::string() const {
    std::string result;
    for (int i = 0; i < size; ++i) {
        result += std::to_string(integerPart[i]);
    }
    result += ".";
    for (int i = 0; i < size; ++i) {
        result += std::to_string(decimalPart[i]);
    }
    return result;
}

std::istream& operator>>(std::istream& in, Fraction& fraction) {
    std::string input;

    std::cout << "Enter the integer part of the fraction: ";
    in >> input;
    fraction.size = input.length();
    for (int i = 0; i < fraction.size; ++i) {
        fraction.integerPart[i] = input[i] - '0';
    }

    std::cout << "Enter the decimal part of the fraction: ";
    in >> input;
    fraction.size = std::max(fraction.size, static_cast<int>(input.length()));
    for (int i = 0; i < fraction.size; ++i) {
        fraction.decimalPart[i] = (i < input.length()) ? input[i] - '0' : 0;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fraction) {
    out << "Fraction: ";
    for (int i = 0; i < fraction.size; ++i) {
        out << static_cast<int>(fraction.integerPart[i]);
    }

    out << ".";
    for (int i = 0; i < fraction.size; ++i) {
        out << static_cast<int>(fraction.decimalPart[i]);
    }
    return out;
}

std::string FractionToString(const Fraction& fraction) {
    return fraction.ToString();
}