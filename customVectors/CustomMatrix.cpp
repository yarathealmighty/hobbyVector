//
// Created by yarr on 2023. 12. 02..
//

#include "CustomMatrix.h"
#include "CustomVectorException.h"

CustomMatrix::CustomMatrix(int** elements, int rows, int columns) : rows(rows), columns(columns) {
    try{
        mtx = createNewMtx(rows,columns);
        cpyMtx(elements,mtx,rows,columns,rows,columns);
    } catch(CustomVectorException& cve){
        std::cout << cve.what() << std::endl;
    }
}

CustomMatrix::CustomMatrix(int rows, int columns) : rows(rows), columns(columns) {
    try{
        mtx = createNewMtx(rows,columns);
    } catch(CustomVectorException& cve){
        std::cout << cve.what() << std::endl;
    }
}

CustomMatrix::CustomMatrix(CustomMatrix& cm) :rows(cm.rows), columns(cm.columns) {
    try{
        mtx= createNewMtx(cm.rows,cm.columns);
        cpyMtx(cm.mtx, mtx, cm.rows, cm.columns, rows, columns);
    } catch(CustomVectorException& cve){
        std::cout << cve.what() << std::endl;
    }
}

CustomMatrix::~CustomMatrix() {
    destroyMtx(mtx,rows);
}

int** CustomMatrix::createNewMtx(int rows, int columns) {
    auto* output = new int*[rows];
    for(int i=0;i<rows;i++){
        int* tmp = CustomVector::createNewContain(columns);
        output[i]=tmp;
    }
    return output;
}

void CustomMatrix::destroyMtx(int** cv,int rows) {
    for(int i=0;i<rows;i++){
        CustomVector::destroyContain(cv[i]);
    }
    delete[] cv;
}

void CustomMatrix::cpyMtx(int** originalMtx,int** newMtx, int originalRows, int originalColumns, int newRows, int newColumns) {
    try{
        int smallerRows;
        if(originalRows<newRows){
            smallerRows=originalRows;
        } else {
            smallerRows=newRows;
        }
        for(int i=0;i<smallerRows;i++){
            CustomVector::cpyContain(originalMtx[i],newMtx[i],originalColumns,newColumns);
        }
    } catch(CustomVectorException& cve){
        std::cout << cve.what() << std::endl;
    }
}

CustomVector *CustomMatrix::split(bool splitToColumns) {
    if(!columns){
        CustomVector rows[rows];
        for(int i=0;i<CustomMatrix::rows;i++){
            CustomVector tmp(mtx[i],columns);
            rows[i] = tmp;
        }
        return rows;
    } else {
        CustomVector columns[columns];
        for(int i=0;i<CustomMatrix::columns;i++){
            int column[rows];
            for(int j=0;j<rows;j++){
                column[j] = mtx[j][i];
            }
            CustomVector tmp(column,rows);
            columns[i] = tmp;
        }
        return columns;
    }
}

