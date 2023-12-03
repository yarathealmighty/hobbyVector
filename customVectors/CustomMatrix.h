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

    [[nodiscard]] int find(CustomVector, bool=false)const;

    [[nodiscard]] int** sorted(bool=false)const;

    void sort(bool=false);

    [[nodiscard]] CustomVector* split(bool=false) const;

    [[nodiscard]] int** transponent() const;

    int determinant() const;

    void sAdd(int);

    void sSubtract(int);

    CustomMatrix& sMultiple(int);

    CustomMatrix& sDivide(int);

    void coutPrint() const;

    void print(int**,int,int) const;

    explicit operator std::string() const;

    CustomMatrix& addRow(const CustomVector&);

    CustomMatrix& addEmptyRow(const CustomVector&);

    CustomMatrix& addEmptyColumn(const CustomVector&);

    CustomMatrix& removeRow(const CustomVector&);

    CustomMatrix& removeLastRow(const CustomVector&);

    CustomMatrix& removeColumn(const CustomVector&);

    CustomMatrix& removeLastColumn(const CustomVector&);

    CustomMatrix& operator+=(const CustomMatrix&);

    CustomMatrix& operator-=(const CustomMatrix&);

    CustomMatrix& operator*=(const CustomMatrix&);

    //todo this will need inverting
    CustomMatrix& operator/=(const CustomMatrix&);

    bool operator==(const CustomMatrix&)const;

    CustomVector& operator[](int) const;

    CustomMatrix& operator=(CustomMatrix&);

    virtual ~CustomMatrix();
};

void swap(CustomMatrix&, CustomMatrix&);


