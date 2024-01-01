//
// Created by yarr on 2024. 01. 01..
//

#pragma once
#include "ColumnVector.h"

ColumnVector::ColumnVector() : CustomVector() {}

ColumnVector::ColumnVector(const int length) : CustomVector(length) {}

ColumnVector::ColumnVector(Fraction* elements, int length) : CustomVector(elements,length) {}

ColumnVector::ColumnVector(ColumnVector &cv) : CustomVector(cv) {}