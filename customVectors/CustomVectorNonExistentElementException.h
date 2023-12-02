//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include <iostream>
#include "CustomVectorException.h"

class CustomVectorNonExistentElementException : public CustomVectorException{
public:
    explicit CustomVectorNonExistentElementException(std::string message="CustomVectorNonExistentElementException happened");
};