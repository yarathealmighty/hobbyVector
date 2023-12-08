//
// Created by yarr on 2023. 12. 08..
//

#include "FractionException.h"

FractionException::FractionException(std::string message) : message(message) {}

const char *FractionException::what() const noexcept {
    return message.c_str();
}
