//
// Created by yarr on 2023. 12. 02..
//

#include <iostream>
#include "CustomVectorException.h"

class CustomVectorIndexOutOfBoundsException : public CustomVectorException{
public:
    explicit CustomVectorIndexOutOfBoundsException(std::string message="CustomVectorIndexOutOfBoundsException happened");
};