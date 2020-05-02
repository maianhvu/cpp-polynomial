//
//  Polynomial.hpp
//  Polynomial
//
//  Created by Mai Anh Vu on 2/5/20.
//  Copyright © 2020 Mai Anh Vu. All rights reserved.
//

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <iostream>

class Polynomial
{
public:
    class Node {
    public:
        inline Node(int p, int c): power(p), coeff(c), next(nullptr) {};
        ~Node();
        int power;
        int coeff;
        Node *next;
        friend std::ostream & operator<< ( std::ostream & , Node &);
    };
    
    Polynomial(const Polynomial &p);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& other);
        
    friend std::ostream & operator<< ( std::ostream & , Polynomial &);
    
    Polynomial operator+(const Polynomial &);
    Polynomial operator*(const Polynomial &);
    
    static Polynomial readFromInput(int maxPower);
    inline Node *getHead() { return head; }
private:
    inline Polynomial(): head(nullptr), tail(nullptr) {};
    Node *head;
    Node *tail;
    void append(int power, int coef);
};

#endif /* Polynomial_hpp */
