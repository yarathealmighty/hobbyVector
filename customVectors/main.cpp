#include <bits/stdc++.h>

using namespace std;

class CustomVectorException : public std::exception{
    std::string message;
public:
    CustomVectorException(std::string message="CustomVectorException happened"): message(message) {}
    virtual const char * what() const noexcept override{
        return message.c_str();
    }
};

class CustomVectorIndexOutOfBoundsException : public CustomVectorException{
public:
    CustomVectorIndexOutOfBoundsException(std::string message="CustomVectorIndexOutOfBoundsException happened"): CustomVectorException(message) {}
};

class CustomVectorNonExistentElementException : public CustomVectorException{
public:
    CustomVectorNonExistentElementException(std::string message="CustomVectorNonExistentElementException happened"): CustomVectorException(message) {}
};

class CustomVectorLengthCannotBeModifiedException : public CustomVectorException{
public:
    CustomVectorLengthCannotBeModifiedException(std::string message="CustomVectorLengthCannotBeModifiedException happened"): CustomVectorException(message) {}
};

class CustomVectorIncorrectParametersException : public CustomVectorException {
public:
    CustomVectorIncorrectParametersException(std::string message="CustomVectorIncorrectParametersException happened"): CustomVectorException(message) {}
};

class CustomVector{
    int length;
    int* contain;
public:
    CustomVector(int elements[]={},int length=0) : length(length) {
        //todo incorrect parameters exception handling
        try{
            contain = createNewContain(CustomVector::length);
            cpyContain(elements,CustomVector::contain,length, CustomVector::length);
        } catch(CustomVectorException cve){
            cerr << cve.what() << endl;
        }
    }
    CustomVector(CustomVector& cv) : length(cv.length) {
        try{
            contain=createNewContain(cv.length);
            cpyContain(cv.contain,CustomVector::contain,cv.length,CustomVector::length);
        } catch(CustomVectorException cve){
            cout << cve.what() << endl;
        }
    }

    int* createNewContain(int length){
        if(length<0){
            throw CustomVectorIncorrectParametersException("Length parameter is incorrect, it cannot be below 0, length value: " + std::to_string(length));
        }
        int* newContain = new int[length];
        return newContain;
    }

    void destroyContain(int* contain){
        delete[] contain;
    }

    void cpyContain(int* originalContain, int* newContain,const int oldLength,const int newLength){
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

    const int find(int element) const{
        for(int i=0;i<length;i++){
            if(contain[i]==element){
                return i;
            }
        }
        throw CustomVectorNonExistentElementException("Element " + std::to_string(element) + " doesn't exist in the vector, so it cannot be found");
    }

    void sort(bool reverse=false){
        if(!reverse){
            std::sort(&contain[0],&contain[length]);
        } else {
            std::sort(&contain[0],&contain[length], std::greater<int>());
        }
    }

    int sum(int startIndex=0, int steps=-1){
        //this is the most half-assed solution I could've come up
        if(steps==-1){
            steps=length-startIndex;
        }
        if(startIndex<0 || startIndex>=length){
            throw CustomVectorIncorrectParametersException("StartIndex: " + std::to_string(startIndex) + " is incorrect for length: " + std::to_string(length) + " and steps: " + std::to_string(steps));
        }
        if(steps<-1 || steps > length-startIndex){
            throw CustomVectorIncorrectParametersException("Steps: " + std::to_string(steps) + " is not a valid amount of steps for startIndex: " + std::to_string(startIndex));
        }
        int sum=0;
        for(int i=startIndex;i<startIndex+steps;i++){
            sum+=contain[i];
        }
        return sum;
    }

    void sAdd(int scalarNumber){
        for(int i=0;i<length;i++){
            contain[i]+=scalarNumber;
        }
    }

    void sSubtract(int scalarNumber){
        for(int i=0;i<length;i++){
            contain[i]-=scalarNumber;
        }
    }

    //todo test
    int* operator+(CustomVector cv){
        if(cv.length != length){
            throw CustomVectorIncorrectParametersException("The 2 lengths are not equal, cvLength: " + std::to_string(cv.length) + ", thisLength: " + std::to_string(CustomVector::length) + " are not equal so the addition cannot be performed");
        } else {
            int *tmpContain = contain;
            for (int i = 0; i < length; i++) {
                tmpContain[i]+=cv.contain[i];
            }
            return tmpContain;
        }
    }

    operator std::string() const {
        std::string str="{";
        for(int i=0;i<length;i++){
            if(i!=length-1){
                str+= std::to_string(contain[i]) + ", ";
            } else {
                str += std::to_string(contain[i]);
            }
        }
        str+="}";
        return str;
    }

    operator int() const {
        return length;
    }

    CustomVector& operator+=(int element){
        if(length==INT32_MAX){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at INT32_MAX value, cannot be extended further");
        }
        length++;
        int* tmpContain = new int[length];
        int tmpLength=length;
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length-1,tmpLength);
        tmpContain[length-1] = element;
        destroyContain(contain);
        contain = tmpContain;
        return *this;
    }

    CustomVector& operator-=(int element){
        if(length==0){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at 0 value, cannot be reduced further");
        }
        bool foundElement=false;
        length--;
        int* tmpContain = new int[length];
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
            throw CustomVectorNonExistentElementException("Element " + std::to_string(element) + " doesn't exist in the vector, so it cannot be taken out");
        } else {
            destroyContain(contain);
            contain = tmpContain;
            return *this;
        }
    }

    CustomVector& operator++(int){
        if(length==INT32_MAX){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at INT32_MAX value, cannot be extended further");
        }
        length++;
        int* tmpContain = new int[length];
        int tmpLength=length;
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length,tmpLength);
        destroyContain(contain);
        contain = tmpContain;
        return *this;
    }

    CustomVector& operator--(int){
        if(length==0){
            throw CustomVectorLengthCannotBeModifiedException("Length is already at 0 value, cannot be reduced further");
        }
        length--;
        int* tmpContain = new int[length];
        int tmpLength=length;
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length,tmpLength);
        destroyContain(contain);
        contain = tmpContain;
        return *this;
    }

    int& operator[](int index) const {
        if(index<0 || index>=length){
            throw CustomVectorIndexOutOfBoundsException("Index out of bounds, index: " + std::to_string(index) + ", length: " + std::to_string(length));
        } else {
            return contain[index];
        }
    }

    CustomVector& operator*=(int scalarNumber){
        //2^30-1
        if(scalarNumber>=1073741823){
            throw CustomVectorIncorrectParametersException("Warning: this number is very big and will probably yield overflowing!");
        }
        for(int i=0;i<length;i++){
            contain[i]*=scalarNumber;
        }
        return *this;
    }

    CustomVector& operator/=(int scalarNumber){
        bool correctParam=true;
        int* tmpContain = createNewContain(CustomVector::length);
        cpyContain(CustomVector::contain,tmpContain,CustomVector::length,CustomVector::length);
        for(int i=0;i<length;i++){
            if(tmpContain[i]%scalarNumber!=0){
                destroyContain(tmpContain);
                correctParam=false;
                break;
            } else {
                tmpContain[i]/=scalarNumber;
            }
        }
        if(correctParam) {
            destroyContain(contain);
            contain = tmpContain;
        } else {
            throw CustomVectorIncorrectParametersException("The number: " + std::to_string(scalarNumber) + " is not a valid number in this case");
        }
        return *this;
    }

    virtual ~CustomVector() {
        delete[] contain;
    }
};

int main(){
    int elements[] = {2,4,6,8};
    CustomVector cv(elements,4);
    cout << string(cv) << endl;
    cout << int(cv) << endl;
    cv.sSubtract(-1);
    cout << string(cv) << endl;
    cout << int(cv) << endl;
    return 0;
}
