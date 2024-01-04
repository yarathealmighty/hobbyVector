//
// Created by yarr on 2023. 12. 02..
//

#include "CustomMatrix.h"
#include "CustomMatrixIncorrectParametersException.h"
#include "CustomMatrixNonExistentElementException.h"
#include "FractionException.h"

CustomMatrix::CustomMatrix(Fraction** elements, int rows, int columns) : rows(rows), columns(columns) {
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

Fraction** CustomMatrix::createNewMtx(int rows, int columns) {
    auto* output = new Fraction*[rows];
    for(int i=0;i<rows;i++){
        Fraction* tmp = CustomVector::createNewContain(columns);
        output[i]=tmp;
    }
    return output;
}

void CustomMatrix::destroyMtx(Fraction** cv,int rows) {
    for(int i=0;i<rows;i++){
        CustomVector::destroyContain(cv[i]);
    }
    delete[] cv;
}

void CustomMatrix::cpyMtx(Fraction** originalMtx,Fraction** newMtx, int originalRows, int originalColumns, int newRows, int newColumns) {
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

//todo testing and all that
bool CustomMatrix::reduceable() const {
    CustomVector* columnVectors = this->split(true);
    for(int i=0;i<columns;i++){
        for(int j=i+1;j<int(columnVectors[i]);j++){
            try {
                if(int(columnVectors[i][j]) != 0){
                    return true;
                }
            } catch (FractionException& fe){
                return true;
            }
        }
    }
    return false;
}

bool CustomMatrix::upperTriangle() const {
    return !reduceable();
}

bool CustomMatrix::strictReduceable() const {
    try {
        CustomVector diagonal = getDiagonal();
        std::cout << "lefut2" << std::endl;
        std::cout << std::string(diagonal) << std::endl;
        Fraction tmp = diagonal.sum();
        std::cout << "lefut3" << std::endl;
        if(int(tmp)==0 && reduceable()){
            return true;
        } else {
            return false;
        }
    } catch(FractionException& fe){
        std::cout << fe.what() << std::endl;
        return false;
    }
}

bool CustomMatrix::strictUpperTriangle() const {
    return !strictReduceable();
}

Fraction CustomMatrix::at(int n,int k) const {
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

Fraction **CustomMatrix::getMtx() const {
    return mtx;
}

CustomMatrix &CustomMatrix::setRow(int index, const CustomVector &cv) {
    if(index<0 || index >= rows){
        throw CustomMatrixIncorrectParametersException("The index-th row: " + std::to_string(index) + " does not exist");
    }
    if(int(cv)!=columns){
        throw CustomMatrixIncorrectParametersException("The length of the vector: " + std::to_string(int(cv)) + " and the number of columns:" + std::to_string(columns) + " are not equal");
    }
    for(int i=0;i<columns;i++){
        mtx[index][i]=cv[i];
    }
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
}

Fraction** CustomMatrix::sorted(bool sortByColumns)const {
    int length = !sortByColumns ? rows : columns;
    CustomVector* vectors = CustomMatrix::split(sortByColumns);

    //todo exception handling and optimalization
    std::sort(vectors, vectors + length);

    auto** output = new Fraction*[length];
    for (int i = 0; i < length; i++) {
        auto *tmp = new Fraction[int(vectors[i])];
        CustomVector::cpyContain(vectors[i].getContain(), tmp, int(vectors[i]), int(vectors[i]));
        output[i] = tmp;
    }

    delete[] vectors;
    return output;
}

void CustomMatrix::sort(bool sortByColumns) {
    Fraction** tmp = sorted(sortByColumns);
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
            auto* column = new Fraction[rows];
            for (int j = 0; j < rows; j++) {
                column[j] = mtx[j][i];
            }
            result[i] = CustomVector(column, rows);
            delete[] column;
        }
    }
    return result;
}

Fraction **CustomMatrix::transponent() const {
    auto** output = new Fraction*[rows];
    for(int i=0;i<rows;i++){
        auto* row = new Fraction[columns];
        for(int j=0;j<columns;j++){
            for(int k=0;k<rows;k++){
                row[k]=mtx[k][j];
            }
        }
        output[i]=row;
    }
    return output;
}

Fraction determinant(CustomMatrix cm) {
    Fraction sum(0);
    if (cm.getRows() < 2 || cm.getColumns() < 2 || cm.getRows() != cm.getColumns()) {
        throw CustomMatrixIncorrectParametersException("The dimensions of the matrix: " + std::to_string(cm.getRows()) + ", " + std::to_string(cm.getColumns()) + " are incorrect for determinant calculation");
    }
    if (cm.getRows() == 2 && cm.getColumns() == 2) {
        return (cm.getMtx()[0][0] * cm.getMtx()[1][1]) - (cm.getMtx()[0][1] * cm.getMtx()[1][0]);
    }
    for (int i = 0; i < cm.getColumns(); i++) {
        CustomMatrix tmp = cm;
        tmp.removeRow(tmp.row(0));
        tmp.removeColumn(tmp.column(i));
        Fraction cofactor = cm.getMtx()[0][i] * determinant(tmp);
        if(i%2==1) {
            cofactor*=Fraction(-1);
        }
        sum+=cofactor;
    }
    return sum;
}

Fraction CustomMatrix::selfDeterminant() {
    Fraction tmp;
    try {
        tmp = determinant(*this);
        if (tmp == Fraction(0)) {
            throw CustomMatrixException("The matrix is degenerate");
        }
    } catch(CustomMatrixException& cme){
        std::cout << cme.what() << std::endl;
    }
    return tmp;
}

CustomMatrix& CustomMatrix::sAdd(const Fraction& scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mtx[i][j]+=scalarNumber;
        }
    }
    return *this;
}

CustomMatrix& CustomMatrix::sSubtract(const Fraction& scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mtx[i][j]-=scalarNumber;
        }
    }
    return *this;
}

CustomMatrix& CustomMatrix::sMultiple(const Fraction& scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            mtx[i][j]*=scalarNumber;
        }
    }
    return *this;
}

CustomMatrix& CustomMatrix::sDivide(const Fraction& scalarNumber) {
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(scalarNumber==Fraction(0)){
                throw CustomMatrixIncorrectParametersException("The matrix is not divisible by scalarNumber: " + std::string(scalarNumber));
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

void CustomMatrix::print(Fraction** matrix,int row, int column) {
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            std::cout << std::string(matrix[i][j]);
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
            try {
                std::cout << int(mtx[i][j]);
            } catch(FractionException& fe){
                std::cout << std::string(mtx[i][j]);
            }
            if(j!=columns-1){
                std::cout << "\t";
            }
        }
        std::cout << std::endl;
    }
}

CustomMatrix &CustomMatrix::addRow(const CustomVector& cv) {
    auto** newMtx = new Fraction*[rows + 1];
    for (int i = 0; i < rows; i++) {
        auto* newRow = new Fraction[columns];
        for (int j = 0; j < columns; j++) {
            newRow[j] = mtx[i][j];
        }
        newMtx[i] = newRow;
    }
    newMtx[rows] = new Fraction[columns];
    for (int j = 0; j < columns; j++) {
        newMtx[rows][j] = cv.getContain()[j];
    }
    destroyMtx(mtx, rows);
    rows++;
    mtx = newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::addEmptyRow() {
    auto** newMtx = new Fraction*[rows+1];
    for(int i=0;i<rows;i++){
        auto* newRow = new Fraction[columns];
        for(int j=0;j<columns;j++){
            newRow[j] = mtx[i][j];
        }
        newMtx[i]=newRow;
    }
    auto* cv = new Fraction[columns];
    for(int i=0;i<columns;i++){
        cv[i] = Fraction(0);
    }
    newMtx[rows]=cv;
    destroyMtx(mtx,rows);
    rows++;
    mtx= newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::addColumn(const CustomVector& cv) {
    auto* column = new Fraction[rows];
    for(int i=0;i<rows;i++){
        column[i] = cv.getContain()[i];
    }
    auto** newMtx = new Fraction*[rows];
    for(int i=0;i<rows;i++){
        auto* row = new Fraction[columns+1];
        for(int j=0;j<columns;j++){
            row[j] = mtx[i][j];
        }
        row[columns] = column[i];
        newMtx[i] = row;
    }
    delete[] column;
    destroyMtx(mtx,rows);
    columns++;
    mtx = newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::addEmptyColumn() {
    Fraction column[rows];
    for(int i=0;i<rows;i++){
        column[i]=Fraction(0);
    }
    auto** newMtx = new Fraction*[rows];
    for(int i=0;i<rows;i++){
        auto* row = new Fraction[columns+1];
        for(int j=0;j<columns;j++){
            row[j] = mtx[i][j];
        }
        row[columns] = column[i];
        newMtx[i] = row;
    }
    destroyMtx(mtx,rows);
    columns++;
    mtx = newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::removeRow(const CustomVector &cv) {
    try{
        int index = find(cv);
        auto** newMtx = new Fraction*[rows-1];
        int j=0;
        for(int i=0;i<rows;i++){
            if(i==index){
                continue;
            } else {
                auto* row = new Fraction[columns];
                for(int k=0;k<columns;k++){
                    row[k] = mtx[i][k];
                }
                newMtx[j++]=row;
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
    auto** newMtx = new Fraction*[rows];
    for(int i=0;i<rows;i++){
        auto* row = new Fraction[columns];
        for(int j=0;j<columns;j++){
            row[j]=mtx[i][j];
        }
        newMtx[i] = row;
    }
    destroyMtx(mtx,rows+1);
    mtx = newMtx;
    return *this;
}

CustomMatrix &CustomMatrix::removeColumn(const CustomVector &cv) {
    try{
        int index = find(cv,true);
        auto** newMtx = new Fraction*[rows];
        for(int i=0;i<rows;i++){
            int j=0;
            auto* row = new Fraction[columns-1];
            for(int k=0;k<columns;k++){
                if(k==index){
                    continue;
                } else {
                    row[j++] = mtx[i][k];
                }
            }
            newMtx[i] = row;
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
    auto** newMtx = new Fraction*[rows];
    for(int i=0;i<rows;i++){
        auto* row = new Fraction[columns];
        for(int j=0;j<columns;j++){
            row[j] = mtx[i][j];
        }
        newMtx[i] = row;
    }
    destroyMtx(mtx,rows);
    mtx = newMtx;
    return *this;
}

CustomVector CustomMatrix::getDiagonal() const {
    CustomVector output = CustomVector();
    for(int i=0;i<rows;i++){
        output << mtx[i][i];
    }
    return output;
}

CustomMatrix::operator std::string() const {
    std::string s="{ ";
    for(int i=0;i<rows;i++){
        s+="{ ";
        for(int j=0;j<columns;j++){
            s+= std::string(mtx[i][j]) + " ";
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
            Fraction sum(0);
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

Fraction* CustomMatrix::operator[](int index) const {
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

CustomMatrix eye(const int n){
    CustomMatrix output(n,n);
    for(int i=0;i<n;i++){
        CustomVector cv;
        for(int j=0;j<n;j++){
            if(i==j){
                Fraction one(1,1);
                cv << one;
            } else {
                Fraction zero(0,1);
                cv << zero;
            }
        }
        output.setRow(i,cv);
    }
    return output;
}

