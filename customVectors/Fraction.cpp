//
// Created by stali on 2023. 12. 07..
//

#include "Fraction.h"
#include "FractionException.h"

Fraction::Fraction(int numerator) : numerator(numerator), denominator(1) {}

Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}

Fraction::Fraction(const Fraction &f) : numerator(f.numerator), denominator(f.denominator) {}

void Fraction::print() {
    cleanup();
    try{
        std::cout << int(*this) << std::endl;
    } catch(FractionException& fe){
        std::cout << std::string(*this) << std::endl;
    }
}

void Fraction::cleanup() {
    if(denominator==0){
        throw FractionException("Not a valid fraction (denominator is 0).");
    }
    if(numerator==0){
        denominator=1;
    }
    if(denominator<0){
        denominator*=-1;
        numerator*=-1;
    }
    simplify();
}

Fraction &Fraction::simplify() {
    int a=numerator,b=denominator,ans;
    if(a==0 || b==1){
        return *this;
    }
    if(b==-1){
        expand(-1);
        return *this;
    }
    if(a<0){
        a*=-1;
    }
    if(b<0){
        b*=-1;
    }
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

Fraction &Fraction::expand(int scalarNumber) {
    numerator*=scalarNumber;
    denominator*=scalarNumber;
    return *this;
}

float Fraction::floatValue() const {
    float out = float(numerator)/float(denominator);
    return out;
}

Fraction &Fraction::operator+=(const Fraction &f) {
    Fraction tmpFraction(f);
    if(denominator!=f.denominator){
        int tmp = denominator;
        this->expand(f.denominator);
        tmpFraction.expand(tmp);
    }
    numerator+=tmpFraction.numerator;
    cleanup();
    return *this;
}

Fraction Fraction::operator+(const Fraction &f) const {
    Fraction tmpFraction(f);
    Fraction output(*this);
    if(denominator!=f.denominator){
        int tmp = denominator;
        output.expand(tmpFraction.denominator);
        tmpFraction.expand(tmp);
    }
    output.numerator+=tmpFraction.numerator;
    return output;
}

Fraction &Fraction::operator-=(const Fraction &f) {
    Fraction tmpFraction(f);
    if(denominator!=f.denominator){
        int tmp = denominator;
        expand(f.denominator);
        tmpFraction.expand(tmp);
    }
    numerator-=tmpFraction.numerator;
    cleanup();
    return *this;
}

Fraction Fraction::operator-(const Fraction &f) const {
    Fraction tmpFraction(f);
    Fraction output(*this);
    if(denominator!=f.denominator){
        int tmp = denominator;
        output.expand(tmpFraction.denominator);
        tmpFraction.expand(tmp);
    }
    output.numerator-=tmpFraction.numerator;
    output.cleanup();
    return output;
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
        if(denominator==numerator){
            return 1;
        }
        if(numerator==0){
            return 0;
        }
        if(denominator==-1){
            return numerator*-1;
        }
        throw FractionException("The fraction: " + std::string(*this) + " is not castable to int");
    }
}

bool Fraction::operator<(const Fraction &other) const {
    //todo more elegantly
    if(floatValue()<other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator<=(const Fraction &other) const {
    if(floatValue()<=other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>(const Fraction &other) const {
    if(floatValue()>other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator>=(const Fraction &other) const {
    if(floatValue()>=other.floatValue()){
        return true;
    } else {
        return false;
    }
}

bool Fraction::operator==(const Fraction &other) const {
    //todo more elegantly
    if(floatValue()==other.floatValue()){
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
