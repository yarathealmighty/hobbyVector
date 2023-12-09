//
// Created by yarr on 2023. 12. 02..
//

#include "CustomMatrix.h"
#include "FractionException.h"
#include "CustomVectorException.h"

#define TESTING

using namespace std;

void CMtesting() {
    //todo write testing ui
}

void CVtesting() {
    //construct/contain/find/sort/sum/sAdd/sSubtract/sMultiple/sDivide/rowMultiple/rowDivide/</==/+=/-=/<</>>/++/--/[]/swap
    //todo write testing ui
    string s;
    bool op;
    cout << "construct/contain/find/sort/sum/sAdd/sSubtract/sMultiple/sDivide/rowMultiple/rowDivide/</==/+=/-=/<</>>/++/--/[]/swap are valid inputs for a command" << endl;
    cin >> s;
    int n,a,b;
    CustomVector v1,v2,v3;
    try{
        if(s=="construct"){
            cout << "default/param/ref" << endl;
            cin >> s;
            if(s=="default"){
                v1 = CustomVector();
                v2 = CustomVector();
                v3 = CustomVector();
            }
            if(s=="param"){
                cout << "length: ";
                cin >> n;
                cout << endl;
                Fraction elements[n];
                for(int i=0;i<n;i++){
                    cout << "a/b: ";
                    cin >> a >> b;
                    cout << endl;
                    Fraction tmp(a,b);
                    elements[i] = tmp;
                }
                v1 = CustomVector(elements,n);
                v2 = CustomVector(elements,n);
                v3 = CustomVector(elements,n);
            }
            if(s=="ref"){

            }
        }
        if(s=="contain"){

        }
        if(s=="find"){

        }
        if(s=="sort"){

        }
        if(s=="sum"){

        }
        if(s=="sAdd"){

        }
        if(s=="sSubtract"){

        }
        if(s=="sMultiple"){

        }
        if(s=="sDivide"){

        }
        if(s=="rowMultiple"){

        }
        if(s=="rowDivide"){

        }
        if(s=="<"){

        }
        if(s=="=="){

        }
        if(s=="+="){

        }
        if(s=="-="){

        }
        if(s=="<<"){

        }
        if(s==">>"){

        }
        if(s=="++"){

        }
        if(s=="--"){

        }
        if(s=="[]"){

        }
        if(s=="swap"){

        }
    } catch (CustomVectorException& cve){
        cout << cve.what() << endl;
    }
}

void Ftesting(){
    //construct/simple/+=/+/-=/-/*=/*/ /= / / /</<=/>/>=/==/!=/=
    string s;
    bool op;
    cout << "construct/simple/+=/+/-=/-/*=/*/ /= / / /</<=/>/>=/==/!=/= are valid inputs for a command" << endl;
    cin >> s;
    int a,b,c,d;
    Fraction f,g,h;
    try{
    if(s=="construct"){
        cout << "default/2/ref are valid inputs for a command" << endl;
        cin >> s;
        if(s=="default"){
            f = Fraction();
        }
        if(s=="2"){
            cout << "x y is a valid input where x,y are both integers" << endl;
            cin >> a >> b;
            f = Fraction(a,b);
        }
        if(s=="ref"){
            cout << "x y is a valid input where x,y are both integers" << endl;
            cin >> a >> b;
            Fraction tmp(a,b);
            f = tmp;
        }
    }
    if(s=="simple"){
        cout << "x y is a valid input where x,y are both integers" << endl;
        cin >> a >> b;
        f = Fraction(a,b);
        f.simplify();
    }
    if(s=="+="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f+=g;
    }
    if(s=="+"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f+g;
    }
    if(s=="-="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f-=g;
    }
    if(s=="-"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f-g;
    }
    if(s=="*="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f*=g;
    }
    if(s=="*"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f*g;
    }
    if(s=="/="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        f/=g;
    }
    if(s=="/"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        h=f/g;
    }
    if(s=="<="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f<=g;
    }
    if(s=="<"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f<g;
    }
    if(s==">="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f>=g;
    }
    if(s==">"){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f>g;
    }
    if(s=="=="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f==g;
    }
    if(s=="!="){
        cout << "x1 y1 x2 y2 is a valid input where x1,x2,y1,y2 are all integers" << endl;
        cin >> a >> b >> c >> d;
        f= Fraction(a,b);
        g= Fraction(c,d);
        op=f!=g;
    }
        cout << "numerator/denominator: " << std::string(f) << endl;
        cout << "float form: " << f.floatValue() << endl;
        cout << "int form: " << int(f) << endl;
    } catch (FractionException& fe){
        cout << fe.what() << endl;
    }
}

int main() {
#ifdef TESTING
    string s;
    cout << "cm for CustomMatrix, cv for CustomVector and f for Fraction testing" << endl;
    cin >> s;
    if(s=="cm") {
        CMtesting();
    }
    if(s=="cv") {
        CVtesting();
    }
    if(s=="f") {
        Ftesting();
    }
#endif
    return 0;
}
