//
// Created by yarr on 2024. 01. 01..
//

#include "RowVector.h"

RowVector::RowVector() : CustomVector() {}

RowVector::RowVector(const int length) : CustomVector(length) {}

RowVector::RowVector(Fraction* elements, const int length) : CustomVector(elements,length) {}

RowVector::RowVector(RowVector &rv) : CustomVector(rv) {}