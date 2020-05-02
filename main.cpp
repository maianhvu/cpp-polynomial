//
//  main.cpp
//  Polynomial
//
//  Created by Mai Anh Vu on 2/5/20.
//  Copyright © 2020 Mai Anh Vu. All rights reserved.
//

#include <iostream>
#include "Polynomial.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    int aMaxPower, bMaxPower;
    
    cout << "maxPower(a) = ";
    cin >> aMaxPower;
    Polynomial a = Polynomial::readFromInput(aMaxPower);
    
    cout << "maxPower(b) = ";
    cin >> bMaxPower;
    Polynomial b = Polynomial::readFromInput(bMaxPower);
    
    cout << "------------------" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "------------------" << endl;
    
    Polynomial sum = a + b;
    cout << "a + b = " << sum << endl;
    Polynomial product = a * b;
    cout << "a * b = " << product << endl;
    return 0;
}

