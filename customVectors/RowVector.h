//
// Created by yarr on 2024. 01. 01..
//

#pragma once
#include "CustomVector.h"

class RowVector : public CustomVector {
    RowVector();

    explicit RowVector(int);

    RowVector(Fraction*,int);

    RowVector(RowVector& rv);
};