#include <iostream>
#include <string>
#include <algorithm> 

class Fraction {
private:
    static const int MAX_DIGITS = 100;
    unsigned char integerPart[MAX_DIGITS];
    unsigned char decimalPart[MAX_DIGITS];
    int size;

public:
    Fraction();
    Fraction(int size);
    Fraction(const Fraction& other);

    int getSize() const;
    void setSize(int size);

    void setIntegerDigit(int index, unsigned char digit);
    unsigned char getIntegerDigit(int index) const;

    void setDecimalDigit(int index, unsigned char digit);
    unsigned char getDecimalDigit(int index) const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;

    bool operator==(const Fraction& other) const;

    void Read();
    void Display() const;
    std::string ToString() const;

    unsigned char* operator[](int index);

    Fraction& operator=(const Fraction& other);

    operator std::string() const;

    friend std::istream& operator>>(std::istream& in, Fraction& fraction);
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
};
