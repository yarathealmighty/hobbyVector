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

int CustomMatrix::at(int n,int k) const {
    return mtx[n][k];
}

int CustomMatrix::find(CustomVector cv, bool findInColumns) const {
    int length=!findInColumns?rows:columns;
    CustomVector* vectors = this->split(findInColumns);

    for(int i=0;i<length;i++){
        if(cv == vectors[i]){
            return i;
        }
    }
    //todo throw exception here
    return -1;
}

int** CustomMatrix::sorted(bool sortByColumns)const {
    int length = !sortByColumns ? rows : columns;
    CustomVector* vectors = CustomMatrix::split(sortByColumns);

    //todo exception handling and optimalization
    std::sort(vectors, vectors + length);

    int** output = new int*[length];
    for (int i = 0; i < length; i++) {
        int *tmp = new int[int(vectors[i])];
        CustomVector::cpyContain(vectors[i].getContain(), tmp, int(vectors[i]), int(vectors[i]));
        output[i] = tmp;
    }

    delete[] vectors;
    return output;
}

void CustomMatrix::sort(bool sortByColumns) {
    int** tmp = sorted(sortByColumns);
    destroyMtx(mtx,rows);
    mtx = createNewMtx(rows,columns);
    cpyMtx(tmp,mtx,rows,columns,rows,columns);
    destroyMtx(tmp,rows);
    if(sortByColumns) {
        tmp = transponent();
        destroyMtx(mtx,rows);
        mtx = createNewMtx(rows,columns);
        cpyMtx(tmp,mtx,rows,columns,rows,columns);
        destroyMtx(tmp,rows);
    }
}

CustomVector* CustomMatrix::split(bool splitToColumns) const {
    CustomVector* result;
    if (!splitToColumns) {
        result = new CustomVector[rows];
        for (int i = 0; i < rows; i++) {
            result[i] = CustomVector(mtx[i], columns);
        }
    } else {
        result = new CustomVector[columns];
        for (int i = 0; i < columns; i++) {
            int* column = new int[rows];
            for (int j = 0; j < rows; j++) {
                column[j] = mtx[j][i];
            }
            result[i] = CustomVector(column, rows);
            delete[] column;
        }
    }
    return result;
}

int **CustomMatrix::transponent() const {
    int** output = new int*[rows];
    for(int i=0;i<rows;i++){
        int* row = new int[columns];
        for(int j=0;j<columns;j++){
            for(int k=0;k<rows;k++){
                row[k]=mtx[k][j];
            }
        }
        output[i]=row;
    }
    return output;
}

void CustomMatrix::sAdd(int scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mtx[i][j]+=scalarNumber;
        }
    }
}

void CustomMatrix::sSubtract(int scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mtx[i][j]-=scalarNumber;
        }
    }
}

CustomMatrix& CustomMatrix::sMultiple(int scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mtx[i][j]*=scalarNumber;
        }
    }
    return *this;
}

CustomMatrix& CustomMatrix::sDivide(int scalarNumber) {
    bool possible=true;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(mtx[i][j]%scalarNumber!=0){
                possible=false;
                break;
            }
        }
    }
    if(possible) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                mtx[i][j] /= scalarNumber;
            }
        }
    } else {
        //todo exception handling here
    }
    return *this;
}

void CustomMatrix::print(int** matrix,int row, int column) const{
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            std::cout << matrix[i][j];
            if(j!=row-1){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void CustomMatrix::coutPrint() const {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            std:: cout << mtx[i][j];
            if(j!=columns-1){
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

CustomMatrix::operator std::string() const {
    std::string s="{ ";
    for(int i=0;i<rows;i++){
        s+="{ ";
        for(int j=0;j<columns;j++){
            s+= std::to_string(mtx[i][j]) + " ";
            if(j!=columns-1){
                s+=", ";
            }
        }
        if(i==rows-1){
            s+="} }";
        } else {
            s+="} , ";
        }
    }
    return s;
}

CustomMatrix &CustomMatrix::operator+=(const CustomMatrix &other) {
    if(rows==other.rows && columns==other.columns){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                mtx[i][j]+=other.mtx[i][j];
            }
        }
    } else {
        //todo exception handling
    }
    return *this;
}

CustomMatrix &CustomMatrix::operator-=(const CustomMatrix &other) {
    if(rows==other.rows && columns==other.columns){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                mtx[i][j]-=other.mtx[i][j];
            }
        }
    } else {
        //todo exception handling
    }
    return *this;
}

bool CustomMatrix::operator==(const CustomMatrix& other) const {
    if(rows!=other.rows || columns != other.columns){
        return false;
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(mtx[i][j]!=other.mtx[i][j]){
                return false;
            }
        }
    }
    return true;
}

int* CustomMatrix::operator[](int index) const {
    if(index>-1 && index<rows){
        return mtx[index];
    } else {
        //todo exception handling
    }
}

CustomMatrix& CustomMatrix::operator=(CustomMatrix& other) {
    if(this!=&other){
        destroyMtx(mtx,rows);
        rows = other.rows;
        columns = other.columns;
        mtx = createNewMtx(rows,columns);
        cpyMtx(other.mtx,mtx,rows,columns,rows,columns);
    }
    return *this;
}



