//
// Created by yarr on 2023. 12. 04..
//

#pragma once
#include "CustomMatrixException.h"

class CustomMatrixIncorrectParametersException :public CustomMatrixException {
public:
    explicit CustomMatrixIncorrectParametersException(std::string="CustomMatrixIncorrectParametersException happened");
};
