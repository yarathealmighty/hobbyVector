//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include <bits/stdc++.h>
#include <utility>
#include "Fraction.h"

class CustomVector{
    int length;
    Fraction* contain;
public:
    CustomVector(Fraction[],int);

    explicit CustomVector(int=0);

    CustomVector(const CustomVector&);

    [[nodiscard]] Fraction* getContain() const;

    static Fraction* createNewContain(int);

    static void destroyContain(const Fraction*);

    static void cpyContain(const Fraction*, Fraction*,int,int);

    [[nodiscard]] int find(const Fraction&) const;

    void sort(bool=false);

    Fraction sum(int=0, int=-1);

    CustomVector& sAdd(const Fraction&);

    CustomVector& sSubtract(const Fraction&);

    CustomVector& sMultiple(const Fraction&);

    CustomVector& sDivide(const Fraction&);

    CustomVector& rowMultple(const Fraction&);

    CustomVector& rowDivide(const Fraction&);

    explicit operator std::string() const;

    explicit operator int() const;

    bool operator<(const CustomVector&)const;

    bool operator==(const CustomVector&)const;

    CustomVector& operator+=(const CustomVector&);

    CustomVector& operator-=(const CustomVector&);

    CustomVector& operator<<(const Fraction&);

    CustomVector& operator>>(const Fraction&);

    //todo these
    CustomVector& operator++(int);

    CustomVector& operator--(int);

    Fraction& operator[](int) const;

    CustomVector& operator=(const CustomVector&);

    virtual ~CustomVector();
};

void swap(CustomVector&, CustomVector&);