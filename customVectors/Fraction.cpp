//
// Created by stali on 2023. 12. 07..
//

#include "Fraction.h"
#include "FractionException.h"

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

float Fraction::floatValue() const {
    float out = float(numerator)/float(denominator);
    return out;
}

Fraction &Fraction::operator+=(const Fraction &f) {
    numerator*=f.numerator;
    denominator*=f.denominator;
    return *this;
}

Fraction Fraction::operator+(const Fraction &f) const {
    int a=numerator+f.numerator,b=denominator+f.denominator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction &Fraction::operator-=(const Fraction &f) {
    numerator-=f.numerator;
    denominator-=f.denominator;
    return *this;
}

Fraction Fraction::operator-(const Fraction &f) const {
    int a=numerator-f.numerator,b=denominator-f.denominator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction &Fraction::operator*=(const Fraction &f) {
    numerator*=f.numerator;
    denominator*=f.denominator;
    return *this;
}

Fraction Fraction::operator*(const Fraction &f) const {
    int a=numerator*f.numerator,b=denominator*f.denominator;
    Fraction tmp(a,b);
    return tmp;
}

Fraction &Fraction::operator/=(const Fraction &f) {
    if(f.numerator==0){
        throw FractionException("Cannot divide by 0");
    }
    numerator*=f.denominator;
    denominator*=f.numerator;
    return *this;
}

Fraction Fraction::operator/(const Fraction &f) const {
    if(f.numerator==0){
        throw FractionException("Cannot divide by 0");
    }
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
        throw FractionException("The fraction: " + std::string(*this) + " is not castable to int");
    }
}

bool Fraction::operator<(const Fraction &other) const {
    //todo more elegantly
    if(this->floatValue()<other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator<=(const Fraction &other) const {
    if(this->floatValue()<=other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>(const Fraction &other) const {
    if(this->floatValue()>other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>=(const Fraction &other) const {
    if(this->floatValue()>=other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator==(const Fraction &other) const {
    //todo more elegantly
    if(this->floatValue()==other.floatValue()){
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
