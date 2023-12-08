//
// Created by yarr on 2023. 12. 08..
//

#pragma once
#include <iostream>

class FractionException : std::exception {
    std::string message;
public:
    FractionException(std::string="FractionException happened");
    const char * what() const noexcept override;
};
