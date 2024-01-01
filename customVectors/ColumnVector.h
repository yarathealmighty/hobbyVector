//
// Created by yarr on 2024. 01. 01..
//

#pragma once
#include "Fraction.h"
#include "CustomVector.h"

class ColumnVector : public CustomVector {
    ColumnVector();

    explicit ColumnVector(int);

    ColumnVector(Fraction*, int);

    ColumnVector(ColumnVector& cv);
};