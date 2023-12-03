//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include "CustomVector.h"

class CustomMatrix {
    int** mtx;
    int rows;
    int columns;
public:
    explicit CustomMatrix(int=1,int=1);

    CustomMatrix(int*[],int,int);

    CustomMatrix(CustomMatrix&);

    static int** createNewMtx(int,int);

    static void destroyMtx(int**,int);

    static void cpyMtx(int**,int**,int,int,int,int);

    [[nodiscard]] int find(CustomVector) const;

    void sort(bool=false);

    CustomVector* split(bool=false);

    int determinant();

    void sAdd(int);

    void sSubtract(int);

    CustomMatrix& sMultiple(int);

    CustomMatrix& sDivide(int);

    CustomMatrix& operator+=(const CustomMatrix&);

    CustomMatrix& operator-=(const CustomMatrix&);

    CustomMatrix& operator<<(CustomVector);

    CustomMatrix& operator>>(CustomVector);

    CustomMatrix& operator++(int);

    CustomMatrix& operator--(int);

    CustomVector& operator[](int) const;

    CustomMatrix& operator=(CustomMatrix&);

    virtual ~CustomMatrix();
};

void swap(CustomMatrix&, CustomMatrix&);


