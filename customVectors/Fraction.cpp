//
// Created by stali on 2023. 12. 07..
//

#include "Fraction.h"

Fraction::Fraction(int numerator) : numerator(numerator), denominator(1) {}

Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

Fraction::Fraction(Fraction &f) : numerator(f.numerator), denominator(f.denominator) {}

Fraction &Fraction::simplify() {
    int a=numerator,b=denominator,ans;
    while(a!=b){
        if(a>b){
            a-=b;
        } else {
            b-=a;
        }
    }
    ans=a;
    numerator/=ans;
    denominator/=ans;
    return *this;
}

Fraction &Fraction::operator+=(const Fraction &f) {
    numerator*=f.numerator;
    denominator*=f.denominator;
    return *this;
}

Fraction Fraction::operator+(const Fraction &f) {
    int a=numerator+f.numerator,b=denominator+f.denominator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction &Fraction::operator-=(const Fraction &f) {
    numerator-=f.numerator;
    denominator-=f.denominator;
    return *this;
}

Fraction Fraction::operator-(const Fraction &f) {
    int a=numerator-f.numerator,b=denominator-f.denominator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction &Fraction::operator*=(const Fraction &f) {
    numerator*=f.numerator;
    denominator*=f.denominator;
    return *this;
}

Fraction Fraction::operator*(const Fraction &f) {
    int a=numerator*f.numerator,b=denominator*f.denominator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction &Fraction::operator/=(const Fraction &f) {
    numerator*=f.denominator;
    denominator*=f.numerator;
    return *this;
}

Fraction Fraction::operator/(const Fraction &f) {
    int a=numerator*f.denominator, b=denominator*f.numerator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction::operator std::string() const {
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

Fraction::operator int() const {
    if(denominator==1){
        return numerator;
    } else {
        //todo exception here
    }
}

Fraction::operator float() const {
    return numerator/denominator;
}

bool Fraction::operator<(const Fraction &other) const {
    //todo more elegantly
    if(float(*this)<float(other)){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator<=(const Fraction &other) const {
    if(float(*this)<=float(other)){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>(const Fraction &other) const {
    if(float(*this)>float(other)){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>=(const Fraction &other) const {
    if(float(*this)>=float(other)){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator==(const Fraction &other) const {
    //todo more elegantly
    if(float(*this)==float(other)){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator!=(const Fraction &other) const {
    return !(*this==other);
}

Fraction &Fraction::operator=(const Fraction &other) {
    if(this!=&other){
        numerator=other.numerator;
        denominator=other.denominator;
    }
    return *this;
}

Fraction::~Fraction() {

}
