//
// Created by yarr on 2023. 12. 02..
//

#include "CustomVector.h"
#include "CustomVectorException.h"
#include "CustomVectorIncorrectParametersException.h"
#include "CustomVectorNonExistentElementException.h"
#include "CustomVectorLengthCannotBeModifiedException.h"
#include "CustomVectorIndexOutOfBoundsException.h"
#include <bits/stdc++.h>

    CustomVector::CustomVector(Fraction* elements,int length) : length(length) {
        //todo incorrect parameters exception handling
        try{
            contain = createNewContain(CustomVector::length);
            cpyContain(elements,CustomVector::contain,length, CustomVector::length);
        } catch(CustomVectorException& cve){
            std::cerr << cve.what() << std::endl;
        }
    }
    CustomVector::CustomVector(int length) : length(length) {
        try{
            Fraction elements[length];
            for(int i=0;i<length;i++){
                Fraction f(0);
                elements[i]= f;
            }
            contain = createNewContain(CustomVector::length);
            cpyContain(elements,CustomVector::contain,length, CustomVector::length);
        } catch(CustomVectorException& cve){
            std::cerr << cve.what() << std::endl;
        }
    }

    CustomVector::CustomVector(const CustomVector& cv) : length(cv.length) {
        try{
            contain=createNewContain(cv.length);
            cpyContain(cv.contain,contain,cv.length,length);
        } catch(CustomVectorException& cve){
            std::cout << cve.what() << std::endl;
        }
    }

    CustomVector::~CustomVector() {
        destroyContain(contain);
    }

    Fraction *CustomVector::getContain() const {
        return contain;
    }

    Fraction* CustomVector::createNewContain(int length){
        if(length<0){
            throw CustomVectorIncorrectParametersException("Length parameter is incorrect, it cannot be below 0, length value: " + std::to_string(length));
        }
        auto* newContain = new Fraction[length];
        return newContain;
    }

    void CustomVector::destroyContain(const Fraction* contain){
        delete[] contain;
    }

    void CustomVector::cpyContain(const Fraction* originalContain, Fraction* newContain,const int oldLength,const int newLength){
        if(oldLength > newLength){
            throw CustomVectorIncorrectParametersException("Old length: " + std::to_string(oldLength) + " and new length: " + std::to_string(newLength) + " are incorrect lengths");
        } else {
            if(oldLength<0 || newLength<0){
                throw CustomVectorIncorrectParametersException("Length parameters are incorrect, it cannot be below 0, length values: " + std::to_string(oldLength) + ", " + std::to_string(newLength));
            } else {
                for (int i = 0; i < newLength; i++) {
                    newContain[i] = originalContain[i];
                }
            }
        }
    }

    [[nodiscard]] int CustomVector::find(const Fraction& element) const{
        for(int i=0;i<length;i++){
            if(contain[i]==element){
                return i;
            }
        }
        throw CustomVectorNonExistentElementException("Element " + std::string(element) + " doesn't exist in the vector, so it cannot be found");
    }

    //todo this
    /*
    void CustomVector::sort(bool reverse){
        if(!reverse){
            std::sort(&contain[0],&contain[length]);
        } else {
            std::sort(&contain[0],&contain[length], std::greater<>());
        }
    }
    */

    Fraction CustomVector::sum(int startIndex, int steps){
        //this is the most half-assed solution I could've come up with
        if(steps==-1){
            steps=length-startIndex;
        }
        if(startIndex<0 || startIndex>=length){
            throw CustomVectorIncorrectParametersException("StartIndex: " + std::to_string(startIndex) + " is incorrect for length: " + std::to_string(length) + " and steps: " + std::to_string(steps));
        }
        if(steps<-1 || steps > length-startIndex){
            throw CustomVectorIncorrectParametersException("Steps: " + std::to_string(steps) + " is not a valid amount of steps for startIndex: " + std::to_string(startIndex));
        }
        Fraction sum(0);
        for(int i=startIndex;i<startIndex+steps;i++){
            sum+=contain[i];
        }
        return sum;
    }

    CustomVector& CustomVector::sAdd(const Fraction& scalarNumber){
        for(int i=0;i<length;i++){
            contain[i]+=scalarNumber;
        }
        return *this;
    }

    CustomVector& CustomVector::sSubtract(const Fraction& scalarNumber){
        for(int i=0;i<length;i++){
            contain[i]-=scalarNumber;
        }
        return *this;
    }

    CustomVector& CustomVector::sMultiple(const Fraction& scalarNumber){
        //2^30-1
        if(scalarNumber>=Fraction(1073741823)){
            throw CustomVectorIncorrectParametersException("Warning: this number is very big and will probably yield overflowing!");
        }
        for(int i=0;i<length;i++){
            contain[i]*=scalarNumber;
        }
        return *this;
    }

    CustomVector& CustomVector::sDivide(const Fraction& scalarNumber){
        for(int i=0;i<length;i++){
            if(scalarNumber==Fraction(0)){
                throw CustomVectorIncorrectParametersException("The vector is not divisible by this scalarNumber: " + std::string(scalarNumber));
            }
        }
        for(int i=0;i<length;i++){
            contain[i]/=scalarNumber;
        }
        return *this;
    }

    CustomVector& CustomVector::rowMultple(const Fraction& scalarNumber) {
        CustomVector& output(*this);
        output.sMultiple(scalarNumber);
        return output;
    }

    CustomVector& CustomVector::rowDivide(const Fraction& scalarNumber){
        CustomVector& output(*this);
        output.sDivide(scalarNumber);
        return output;
    }

    CustomVector::operator std::string() const {
        std::string str="{";
        for(int i=0;i<length;i++){
            if(i!=length-1){
                str+= std::string(contain[i]) + ", ";
            } else {
                str += std::string(contain[i]);
            }
        }
        str+="}";
        return str;
    }

    CustomVector::operator int() const {
        return length;
    }

    bool CustomVector::operator<(const CustomVector& other)const {
        for (int i = 0; i < std::min(length, other.length); ++i) {
            if (contain[i] < other.contain[i]) return true;
            if (contain[i] > other.contain[i]) return false;
        }
        return length < other.length;
    }

    bool CustomVector::operator==(const CustomVector& cv) const {
        if(length!=cv.length){
            return false;
        }
        for(int i=0;i<length;i++){
            if(contain[i]!=cv.contain[i]){
                return false;
            }
        }
        return true;
    }

    CustomVector& CustomVector::operator+=(const CustomVector& cv){
        if(cv.length!=length){
            throw CustomVectorIncorrectParametersException("The dimensions of the 2 vectors are different, this:" + std::to_string(length) + ", other:" + std::to_string(cv.length));
        }
        for(int i=0;i<length;i++){
            contain[i]+=cv.contain[i];
        }
        return *this;
    }

    CustomVector& CustomVector::operator-=(const CustomVector& cv){
        if(cv.length!=length){
            throw CustomVectorIncorrectParametersException("The dimensions of the 2 vectors are different, this:" + std::to_string(length) + ", other:" + std::to_string(cv.length));
        }
        for(int i=0;i<length;i++){
            contain[i]-=cv.contain[i];
        }
        return *this;
    }

    CustomVector& CustomVector::operator<<(const Fraction& element){
        if(length==INT32_MAX){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at INT32_MAX value, cannot be extended further");
        }
        length++;
        auto* tmpContain = new Fraction[length];
        int tmpLength=length;
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length-1,tmpLength);
        tmpContain[length-1] = element;
        destroyContain(contain);
        contain = tmpContain;
        return *this;
    }

    CustomVector& CustomVector::operator>>(const Fraction& element){
        if(length==0){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at 0 value, cannot be reduced further");
        }
        bool foundElement=false;
        length--;
        auto* tmpContain = new Fraction[length];
        int j=0;
        for(int i=0;i<length+1;i++){
            if(contain[i]!=element) {
                tmpContain[j++] = contain[i];
            } else {
                foundElement=true;
            }
        }
        if(!foundElement){
            length++;
            throw CustomVectorNonExistentElementException("Element " + std::string(element) + " doesn't exist in the vector, so it cannot be taken out");
        } else {
            destroyContain(contain);
            contain = tmpContain;
            return *this;
        }
    }

    CustomVector& CustomVector::operator++(int){
        CustomVector& output(*this);
        if(length==INT32_MAX){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at INT32_MAX value, cannot be extended further");
        }
        length++;
        auto* tmpContain = new Fraction[length];
        int tmpLength=length;
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length,tmpLength);
        destroyContain(contain);
        contain = tmpContain;
        return output;
    }

    CustomVector& CustomVector::operator--(int){
        if(length==0){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at 0 value, cannot be reduced further");
        }
        length--;
        auto* tmpContain = new Fraction[length];
        int tmpLength=length;
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length,tmpLength);
        destroyContain(contain);
        contain = tmpContain;
        return *this;
    }

    Fraction& CustomVector::operator[](int index) const {
        if(index<0 || index>=length){
            throw CustomVectorIndexOutOfBoundsException("Index out of bounds, index: " + std::to_string(index) + ", length: " + std::to_string(length));
        } else {
            return contain[index];
        }
    }

    CustomVector& CustomVector::operator=(const CustomVector& cv) {
        if(this!=&cv) {
            length = cv.length;
            destroyContain(contain);
            contain = createNewContain(cv.length);
            cpyContain(cv.contain, contain, cv.length, length);
        }
        return *this;
    }

void swap(CustomVector& cv1, CustomVector& cv2){
    CustomVector tmp(cv2);
    cv2 = cv1;
    cv1 = tmp;
}