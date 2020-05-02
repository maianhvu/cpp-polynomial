//
//  Polynomial.cpp
//  Polynomial
//
//  Created by Mai Anh Vu on 2/5/20.
//  Copyright © 2020 Mai Anh Vu. All rights reserved.
//

#include "Polynomial.hpp"
#include <climits>
#include <vector>

using namespace std;

// Copy constructor
Polynomial::Polynomial(const Polynomial &p) {
    Node *current = p.head;
    while (current) {
        append(current->power, current->coeff);
        current = current->next;
    }
}

// Copy assignment
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        Node *thisPrev = nullptr;
        Node *thisCurrent = this->head;
        Node *otherCurrent = other.head;
        
        // First copy the values from `other` to `this` up to the n-th element
        // where n = min(size(this), size(other)).
        while (thisCurrent && otherCurrent) {
            thisCurrent->power = otherCurrent->power;
            thisCurrent->coeff = otherCurrent->coeff;
            thisPrev = thisCurrent;
            thisCurrent = thisCurrent->next;
            otherCurrent = otherCurrent->next;
        }
        
        if (thisCurrent) {
            // There are still more elements for `this`, but we have reached the end
            // for the `other` one. Chop `this` off at the current point.
            this->tail = thisPrev;
            this->tail->next = nullptr;
            delete thisCurrent;
        } else if (otherCurrent) {
            // There are still more elements for the other, append to the end.
            while (otherCurrent) {
                append(otherCurrent->power, otherCurrent->coeff);
                otherCurrent = otherCurrent->next;
            }
        }
    }
    return *this;
}

// Destructor
Polynomial::~Polynomial() {
    delete head;
}

void Polynomial::append(int power, int coef) {
    Node *node = new Node(power, coef);
    if (tail) {
        tail->next = node;
    }
    tail = node;
    if (!head) {
        head = node;
    }
}

Polynomial Polynomial::readFromInput(int maxPower) {
    int coef;
    Polynomial output;
    for (int power = 0; power <= maxPower; ++power) {
        cout << "c(x^" << power << ") = ";
        cin >> coef;
        if (coef <= 0) { continue; }
        output.append(power, coef);
    }
    return output;
}

ostream & operator<< (std::ostream &out, Polynomial::Node &node) {
    switch (node.power) {
        case 0:
            out << node.coeff;
            break;
        case 1:
            if (node.coeff > 1) { out << node.coeff; }
            out << "x";
            break;
        default:
            if (node.coeff > 1) { out << node.coeff; }
            out << "x^" << node.power;
            break;
    }
    return out;
}

ostream & operator<<( ostream & out, Polynomial &poly) {
    Polynomial::Node *current = poly.getHead();
    vector<Polynomial::Node *> stack;
    while (current) {
        stack.push_back(current);
        current = current->next;
    }
    
    if (stack.empty()) { return out; }
    
    vector<Polynomial::Node *>::reverse_iterator nodeRef = stack.rbegin();

    if ((*nodeRef)->coeff) {
        out << **nodeRef;
    }
    nodeRef++;

    for (;nodeRef != stack.rend(); ++nodeRef) {
        if (!((*nodeRef)->coeff)) { continue; }
        out << " + " << **nodeRef;
    }
    
    return out;
}

Polynomial Polynomial::operator+(const Polynomial &other) {
    Polynomial result;
    Node *aNode = this->head;
    Node *bNode = other.head;
    while (aNode || bNode) {
        int aPower = aNode ? aNode->power : INT_MAX;
        int bPower = bNode ? bNode->power : INT_MAX;
        if (aPower < bPower) {
            // Use A's coefficient
            result.append(aPower, aNode->coeff);
            aNode = aNode->next;
        } else if (bPower < aPower) {
            // Use B's coefficient
            result.append(bPower, bNode->coeff);
            bNode = bNode->next;
        } else {
            int aCoeff = aNode ? aNode->coeff : 0;
            int bCoeff = bNode ? bNode->coeff : 0;
            result.append(aPower, aCoeff + bCoeff);
            aNode = aNode->next;
            bNode = bNode->next;
        }
    }
    return result;
}

Polynomial Polynomial::operator*(const Polynomial &other) {
    Polynomial result;
    Node *bNode = other.head;
    while (bNode) {
        Polynomial intermediate;
        Node *aNode = this->head;
        while (aNode) {
            intermediate.append(aNode->power + bNode->power, aNode->coeff * bNode->coeff);
            aNode = aNode->next;
        }
        result = result + intermediate;
        bNode = bNode->next;
    }
    return result;
}

// Recursive destruction
Polynomial::Node::~Node() {
    if (next) {
        delete next;
    }
}
