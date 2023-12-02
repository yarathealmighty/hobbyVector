//
// Created by yarr on 2023. 12. 02..
//

#include <iostream>
#include "CustomVectorException.h"

class CustomVectorLengthCannotBeModifiedException : public CustomVectorException{
public:
    explicit CustomVectorLengthCannotBeModifiedException(std::string message="CustomVectorLengthCannotBeModifiedException happened");
};