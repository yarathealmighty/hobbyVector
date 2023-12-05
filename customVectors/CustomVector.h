//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include <bits/stdc++.h>
#include <utility>

class CustomVector{
    int length;
    int* contain;
public:
    CustomVector(int[],int);

    explicit CustomVector(int=0);

    CustomVector(const CustomVector&);

    [[nodiscard]] int *getContain() const;

    static int* createNewContain(int);

    static void destroyContain(const int*);

    static void cpyContain(const int*, int*,int,int);

    [[nodiscard]] int find(int) const;

    void sort(bool=false);

    int sum(int=0, int=-1);

    void sAdd(int);

    void sSubtract(int);

    CustomVector& sMultiple(int);

    CustomVector& sDivide(int);

    CustomVector& rowMultple(int);

    CustomVector& rowDivide(int);

    explicit operator std::string() const;

    explicit operator int() const;

    bool operator<(const CustomVector&)const;

    bool operator==(const CustomVector&)const;

    CustomVector& operator+=(const CustomVector&);

    CustomVector& operator-=(const CustomVector&);

    CustomVector& operator<<(int);

    CustomVector& operator>>(int);

    //todo these
    CustomVector& operator++(int);

    CustomVector& operator--(int);

    int& operator[](int) const;

    CustomVector& operator=(const CustomVector&);

    virtual ~CustomVector();
};

void swap(CustomVector&, CustomVector&);