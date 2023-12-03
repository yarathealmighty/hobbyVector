//
// Created by yarr on 2023. 12. 02..
//

#pragma once
#include "CustomVector.h"

class CustomMatrix {
    CustomVector* mtx;
    int rows;
    int coloumns;
public:
    explicit CustomMatrix(int=1,int=1);

    CustomMatrix(int*[],int,int);

    CustomMatrix(CustomMatrix&);

    static CustomVector* createNewMtx(int,int);

    static void destroyMtx(const CustomVector*);

    static void cpyMtx()
};

