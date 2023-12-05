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

    [[nodiscard]] int getRows()const;

    [[nodiscard]] int getColumns()const;

    [[nodiscard]] int** getMtx()const;

    [[nodiscard]] int at(int,int)const;

    [[nodiscard]] CustomVector& row(int) const;

    CustomMatrix& setRow(int, const CustomVector&);

    [[nodiscard]] CustomVector& column(int) const;

    CustomMatrix& setColumn(int, const CustomVector&);

    [[nodiscard]] int find(const CustomVector&, bool=false)const;

    [[nodiscard]] int** sorted(bool=false)const;

    void sort(bool=false);

    [[nodiscard]] CustomVector* split(bool=false) const;

    [[nodiscard]] int** transponent() const;

    [[nodiscard]] int selfDeterminant();

    void sAdd(int);

    void sSubtract(int);

    CustomMatrix& sMultiple(int);

    CustomMatrix& sDivide(int);

    void coutPrint() const;

    static void print(int**,int,int) ;

    explicit operator std::string() const;

    CustomMatrix& addRow(const CustomVector&);

    CustomMatrix& addEmptyRow();

    CustomMatrix& addColumn(const CustomVector&);

    CustomMatrix& addEmptyColumn();

    CustomMatrix& removeRow(const CustomVector&);

    CustomMatrix& removeLastRow();

    CustomMatrix& removeColumn(const CustomVector&);

    CustomMatrix& removeLastColumn();

    CustomMatrix& operator+=(const CustomMatrix&);

    CustomMatrix& operator-=(const CustomMatrix&);

    CustomMatrix operator*(const CustomMatrix&) const;

    //todo this will need inverting
    CustomMatrix operator/(const CustomMatrix&);

    bool operator==(const CustomMatrix&)const;

    int* operator[](int) const;

    CustomMatrix& operator=(CustomMatrix&);

    virtual ~CustomMatrix();
};

void swap(CustomMatrix&, CustomMatrix&);

int determinant(CustomMatrix);


