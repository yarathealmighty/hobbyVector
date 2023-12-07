//
// Created by yarr on 2023. 12. 07..
//

#pragma once
#include <iostream>

class Fraction {
    //thank you dr. Kurusa Árpád
    int numerator;
    int denominator;
public:
    explicit Fraction(int=0);

    explicit Fraction(int,int);

    Fraction(Fraction&);

    Fraction& simplify();

    Fraction& operator+=(const Fraction&);

    Fraction operator+(const Fraction&);

    Fraction& operator-=(const Fraction&);

    Fraction operator-(const Fraction&);

    Fraction& operator*=(const Fraction&);

    Fraction operator*(const Fraction&);

    Fraction& operator/=(const Fraction&);

    Fraction operator/(const Fraction&);

    explicit operator std::string() const;

    explicit operator int() const;

    explicit operator float() const;

    bool operator<(const Fraction&)const;
    bool operator<=(const Fraction&)const;

    bool operator>(const Fraction&)const;
    bool operator>=(const Fraction&)const;

    bool operator==(const Fraction&)const;
    bool operator!=(const Fraction&)const;

    Fraction& operator=(const Fraction&);

    virtual ~Fraction();
};
