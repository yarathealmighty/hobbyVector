//
// Created by yarr on 2023. 12. 04..
//

#pragma once
#include "CustomMatrixException.h"

class CustomMatrixElementNotFoundException : public CustomMatrixException {
public:
    explicit CustomMatrixElementNotFoundException(std::string="CustomMatrixElementNotFoundException happened");
};
