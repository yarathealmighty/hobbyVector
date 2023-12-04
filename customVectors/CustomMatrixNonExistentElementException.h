//
// Created by yarr on 2023. 12. 04..
//

#pragma once
#include "CustomMatrixException.h"

class CustomMatrixNonExistentElementException : public CustomMatrixException {
public:
    explicit CustomMatrixNonExistentElementException(std::string="CustomMatrixNonExistentElementException happened");
};
