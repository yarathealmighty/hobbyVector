//
// Created by yarr on 2023. 12. 02..
//

#include "CustomVectorException.h"

std::string message;

CustomVectorException::CustomVectorException(std::string message) : message(message) {}

const char *CustomVectorException::what() const noexcept {
    return CustomVectorException::message.c_str();
}