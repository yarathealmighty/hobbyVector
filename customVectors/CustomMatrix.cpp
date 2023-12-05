//
// Created by yarr on 2023. 12. 02..
//

#include "CustomMatrix.h"
#include "CustomMatrixIncorrectParametersException.h"
#include "CustomMatrixNonExistentElementException.h"

CustomMatrix::CustomMatrix(int** elements, int rows, int columns) : rows(rows), columns(columns) {
    try{
        mtx = createNewMtx(rows,columns);
        cpyMtx(elements,mtx,rows,columns,rows,columns);
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
    }
}

CustomMatrix::CustomMatrix(int rows, int columns) : rows(rows), columns(columns) {
    try{
        mtx = createNewMtx(rows,columns);
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
    }
}

CustomMatrix::CustomMatrix(CustomMatrix& cm) :rows(cm.rows), columns(cm.columns) {
    try{
        mtx= createNewMtx(cm.rows,cm.columns);
        cpyMtx(cm.mtx, mtx, cm.rows, cm.columns, rows, columns);
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
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
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
    }
}

int CustomMatrix::at(int n,int k) const {
    return mtx[n][k];
}

CustomVector &CustomMatrix::row(int index) const {
    if(index<0 || index >= rows){
        throw CustomMatrixIncorrectParametersException("The index-th row: " + std::to_string(index) + " does not exist");
    }
    CustomVector* vectors = split();
    return vectors[index];
}

int CustomMatrix::getRows() const {
    return rows;
}

int CustomMatrix::getColumns() const {
    return columns;
}

int **CustomMatrix::getMtx() const {
    return mtx;
}

CustomMatrix &CustomMatrix::setRow(int index, const CustomVector &cv) {
    if(index<0 || index >= rows){
        throw CustomMatrixIncorrectParametersException("The index-th row: " + std::to_string(index) + " does not exist");
    }
    if(int(cv)!=columns){
        throw CustomMatrixIncorrectParametersException("The length of the vector: " + std::to_string(int(cv)) + " and the number of columns:" + std::to_string(columns) + " are not equal");
    }
    CustomVector::destroyContain(mtx[index]);
    mtx[index]=cv.getContain();
    return *this;
}

CustomVector &CustomMatrix::column(int index) const {
    if(index<0 || index >= columns){
        throw CustomMatrixIncorrectParametersException("The index-th column: " + std::to_string(index) + " does not exist");
    }
    CustomVector* vectors = split(true);
    return vectors[index];
}

CustomMatrix &CustomMatrix::setColumn(int index, const CustomVector &cv) {
    if(index<0 || index >= columns){
        throw CustomMatrixIncorrectParametersException("The index-th column: " + std::to_string(index) + " does not exist");
    }
    if(int(cv)!=rows){
        throw CustomMatrixIncorrectParametersException("The length of the vector: " + std::to_string(int(cv)) + " and the number of rows:" + std::to_string(rows) + " are not equal");
    }
    for(int i=0;i<rows;i++){
        mtx[i][index] = cv[i];
    }
    return *this;
}

int CustomMatrix::find(const CustomVector& cv, bool findInColumns) const {
    int length=!findInColumns?rows:columns;
    CustomVector* vectors = this->split(findInColumns);

    for(int i=0;i<length;i++){
        if(cv == vectors[i]){
            return i;
        }
    }
    throw CustomMatrixNonExistentElementException("The CustomVector: " + std::string(cv) + " doesn't exist in the matrix if searched in " + (findInColumns?"columns":"rows"));
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
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(scalarNumber==0 || mtx[i][j]%scalarNumber!=0){
                throw CustomMatrixIncorrectParametersException("The matrix is not divisible by scalarNumber: " + std::to_string(scalarNumber));
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            mtx[i][j] /= scalarNumber;
        }
    }
    return *this;
}

void CustomMatrix::print(int** matrix,int row, int column) {
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

CustomMatrix &CustomMatrix::addRow(const CustomVector& cv) {
    int** newMtx = new int*[rows+1];
    for(int i=0;i<rows;i++){
        int* newRow = new int[columns];
        for(int j=0;j<columns;j++){
            newRow[j] = mtx[i][j];
        }
        newMtx[i]=newRow;
        delete[] newRow;
    }
    newMtx[rows]=cv.getContain();
    destroyMtx(mtx,rows);
    rows++;
    mtx= newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::addEmptyRow() {
    int** newMtx = new int*[rows+1];
    for(int i=0;i<rows;i++){
        int* newRow = new int[columns];
        for(int j=0;j<columns;j++){
            newRow[j] = mtx[i][j];
        }
        newMtx[i]=newRow;
        delete[] newRow;
    }
    int* cv = new int[columns];
    for(int i=0;i<columns;i++){
        cv[i] = 0;
    }
    newMtx[rows]=cv;
    destroyMtx(mtx,rows);
    delete[] cv;
    rows++;
    mtx= newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::addColumn(const CustomVector& cv) {
    int* column = cv.getContain();
    int** newMtx = new int*[rows];
    for(int i=0;i<rows;i++){
        int* row = new int[columns+1];
        for(int j=0;j<columns;j++){
            row[j] = mtx[i][j];
        }
        row[columns] = column[i];
        newMtx[i] = row;
        delete[] row;
    }
    delete[] column;
    destroyMtx(mtx,rows);
    mtx = newMtx;
    columns++;
    return *this;
}

CustomMatrix &CustomMatrix::addEmptyColumn() {
    int column[rows];
    for(int i=0;i<rows;i++){
        column[i]=0;
    }
    int** newMtx = new int*[rows];
    for(int i=0;i<rows;i++){
        int* row = new int[columns+1];
        for(int j=0;j<columns;j++){
            row[j] = mtx[i][j];
        }
        row[columns] = column[i];
        newMtx[i] = row;
        delete[] row;
    }
    destroyMtx(mtx,rows);
    mtx = newMtx;
    columns++;
    return *this;
}

CustomMatrix &CustomMatrix::removeRow(const CustomVector &cv) {
    try{
        int index = find(cv);
        int** newMtx = new int*[rows-1];
        int j=0;
        for(int i=0;i<rows;i++){
            if(i==index){
                continue;
            } else {
                newMtx[j++]=mtx[i];
            }
        }
        destroyMtx(mtx,rows);
        rows--;
        mtx = newMtx;
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
    }
    return *this;
}

CustomMatrix &CustomMatrix::removeLastRow() {
    rows--;
    int** newMtx = new int*[rows];
    for(int i=0;i<rows;i++){
        newMtx[i] = mtx[i];
    }
    destroyMtx(mtx,rows+1);
    mtx = newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::removeColumn(const CustomVector &cv) {
    try{
        int index = find(cv,true);
        int** newMtx = new int*[rows];
        for(int i=0;i<rows;i++){
            int j=0;
            int* row = new int[columns-1];
            for(int k=0;k<columns;k++){
                if(k==index){
                    continue;
                } else {
                    row[j++] = mtx[i][k];
                }
            }
            newMtx[i] = row;
            delete[] row;
        }
        columns--;
        destroyMtx(mtx,rows);
        mtx=newMtx;
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
    }
    return *this;
}

CustomMatrix &CustomMatrix::removeLastColumn() {
    columns--;
    int** newMtx = new int*[rows];
    for(int i=0;i<rows;i++){
        int* row = new int[columns];
        for(int j=0;j<columns;j++){
            row[j] = mtx[i][j];
        }
        newMtx[i] = row;
        delete[] row;
    }
    destroyMtx(mtx,rows);
    mtx = newMtx;
    return *this;
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
        throw CustomMatrixIncorrectParametersException("The dimensions of this matrix: " + std::to_string(rows) + ", " + std::to_string(columns) + " are not equal to the dimensions of the other matrix: " + std::to_string(other.rows) + ", " + std::to_string(other.columns));
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
        throw CustomMatrixIncorrectParametersException("The dimensions of this matrix: " + std::to_string(rows) + ", " + std::to_string(columns) + " are not equal to the dimensions of the other matrix: " + std::to_string(other.rows) + ", " + std::to_string(other.columns));
    }
    return *this;
}

CustomMatrix CustomMatrix::operator*(const CustomMatrix &other) const {
    if(columns!=other.rows){
        throw CustomMatrixIncorrectParametersException("The k dimension of the left matrix is: " +std::to_string(columns)+ " and the n dimension of the second matrix is: " + std::to_string(other.rows) + ", which are not equal");
    }
    CustomVector* first = split();
    CustomVector* second = other.split(true);
    CustomMatrix newCM(rows,other.columns);
    for(int i=0;i<rows;i++){
        CustomVector tmp(0);
        for(int j=0;j<other.columns;j++){
            int sum=0;
            for(int k=0;k<columns;k++){
                sum+=first[i][k]*second[j][k];
            }
            tmp<<sum;
        }
        newCM.setRow(i,tmp);
    }
    delete[] first;
    delete[] second;
    return newCM;
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
        throw CustomMatrixIncorrectParametersException("The index: " + std::to_string(index) + " is not a valid index for " + std::to_string(rows) + " rows");
    }
}

//todo this
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

void swap(CustomMatrix &cm1, CustomMatrix &cm2) {
    CustomMatrix CM(cm2);
    cm2=cm1;
    cm1=CM;
}

int determinant(CustomMatrix cm) {
    int sum=0;
    //todo chessboard
    if(cm.getRows()<2 || cm.getColumns()<2 || cm.getRows()!=cm.getColumns()){
        throw CustomMatrixIncorrectParametersException("The dimensions of the matrix: " + std::to_string(cm.getRows()) + ", " + std::to_string(cm.getColumns()) + " are incorrect for determinant calculation");
    }
    if(cm.getRows()==2 && cm.getColumns()==2){
        return (cm.getMtx()[0][0]*cm.getMtx()[1][1])-(cm.getMtx()[0][1]*cm.getMtx()[1][0]);
    }
    CustomMatrix* matrices = new CustomMatrix[cm.getColumns()];
    for(int i=0;i<cm.getColumns();i++){
        //todo smaller matrices
        matrices[i] = cm;
    }
    //todo recursive call for sum+=
    return sum;
}
