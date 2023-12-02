//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include <iostream>
#include "CustomVectorException.h"

class CustomVectorIncorrectParametersException : public CustomVectorException {
public:
    explicit CustomVectorIncorrectParametersException(std::string message="CustomVectorIncorrectParametersException happened");
};