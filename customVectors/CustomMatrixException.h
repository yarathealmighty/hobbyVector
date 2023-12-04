//
// Created by yarr on 2023. 12. 04..
//

#pragma once
#include <iostream>

class CustomMatrixException : public std::exception{
private:
    std::string message;
public:
    explicit CustomMatrixException(std::string message = "CustomMatrixException happened");
    [[nodiscard]] const char * what() const noexcept override;
};