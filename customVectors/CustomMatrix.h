//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include "CustomVector.h"

class CustomMatrix {
    Fraction** mtx;
    int rows;
    int columns;
public:
    explicit CustomMatrix(int=1,int=1);

    CustomMatrix(Fraction*[],int,int);

    CustomMatrix(CustomMatrix&);

    static Fraction** createNewMtx(int,int);

    static void destroyMtx(Fraction**,int);

    static void cpyMtx(Fraction**,Fraction**,int,int,int,int);

    [[nodiscard]] bool reduceable()const;

    [[nodiscard]] bool upperTriangle() const;

    [[nodiscard]] bool lowerTriangle() const;

    [[nodiscard]] bool strictReduceable() const;

    [[nodiscard]] bool strictUpperTriangle() const;

    [[nodiscard]] bool strictLowerTriangle() const;

    [[nodiscard]] int getRows()const;

    [[nodiscard]] int getColumns()const;

    [[nodiscard]] Fraction** getMtx()const;

    [[nodiscard]] Fraction at(int,int)const;

    [[nodiscard]] CustomVector& row(int) const;

    CustomMatrix& setRow(int, const CustomVector&);

    [[nodiscard]] CustomVector& column(int) const;

    CustomMatrix& setColumn(int, const CustomVector&);

    [[nodiscard]] int find(const CustomVector&, bool=false)const;

    [[nodiscard]] Fraction** sorted(bool=false)const;

    void sort(bool=false);

    [[nodiscard]] CustomVector* split(bool=false) const;

    [[nodiscard]] Fraction** transponent() const;

    [[nodiscard]] Fraction selfDeterminant();

    CustomMatrix& sAdd(const Fraction&);

    CustomMatrix& sSubtract(const Fraction&);

    CustomMatrix& sMultiple(const Fraction&);

    CustomMatrix& sDivide(const Fraction&);

    void coutPrint() const;

    static void print(Fraction**,int,int) ;

    explicit operator std::string() const;

    CustomMatrix& addRow(const CustomVector&);

    CustomMatrix& addEmptyRow();

    CustomMatrix& addColumn(const CustomVector&);

    CustomMatrix& addEmptyColumn();

    CustomMatrix& removeRow(const CustomVector&);

    CustomMatrix& removeLastRow();

    CustomMatrix& removeColumn(const CustomVector&);

    CustomMatrix& removeLastColumn();

    CustomVector getDiagonal() const;

    CustomMatrix& operator+=(const CustomMatrix&);

    CustomMatrix& operator-=(const CustomMatrix&);

    CustomMatrix operator*(const CustomMatrix&) const;

    //todo this will need inverting
    CustomMatrix operator/(const CustomMatrix&);

    bool operator==(const CustomMatrix&)const;

    Fraction* operator[](int) const;

    CustomMatrix& operator=(CustomMatrix&);

    virtual ~CustomMatrix();
};

void swap(CustomMatrix&, CustomMatrix&);

Fraction determinant(CustomMatrix);

CustomMatrix eye(int);