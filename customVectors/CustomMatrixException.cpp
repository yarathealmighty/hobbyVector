//
// Created by yarr on 2023. 12. 04..
//

#include "CustomMatrixException.h"

CustomMatrixException::CustomMatrixException(std::string message) : message(message) {}

const char *CustomMatrixException::what() const noexcept {
    return message.c_str();
}