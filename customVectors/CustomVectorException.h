//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include <iostream>

class CustomVectorException : public std::exception{
private:
    std::string message;
public:
    explicit CustomVectorException(std::string message = "CustomVectorException happened");
    [[nodiscard]] const char * what() const noexcept override;
};