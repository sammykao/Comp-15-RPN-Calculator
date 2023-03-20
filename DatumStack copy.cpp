/*
 *  DatumStack.cpp
 *  SAMMY KAO
 *  2/23/2023
 *
 *  CS 15 PROJ2 CALCYOULATER
 *
 *  Purpose: This file is the implementation of 
 *  the DatumStack class to use for our RPNCalc
 *  it's essentially building a stack to use
 *
 */

#include "DatumStack.h"
#include <string>
#include <stdexcept>
#include <vector> 
#include <sstream>


/*
 * name:      DatumStack()
 * purpose:   DatumStack default constructor
 * arguments: none
 * returns:   none
 * effects:   No code really needed since Stack vector 
 *            initializes itself
 */
DatumStack::DatumStack() {

}

/*
 * name:      DatumStack()
 * purpose:   DatumStack second constructor
 * arguments: Array of Datum objects
 * returns:   none
 * effects:   initialez DatumStack using elements in array
 */
DatumStack::DatumStack(Datum arr[], int arrsize) {
    for (int i=0; i<arrsize; i++) {
        Stack.push_back(arr[i]);
    }
}

/*
 * name:      DatumStack()
 * purpose:   DatumStack copy constructor
 * arguments: other Datumstack 
 * returns:   none
 * effects:   initializes a DatumStack copy of other
 *            Datumstack, making a copy of objects
 */
DatumStack::DatumStack(const DatumStack &other) {
    for (int i=0; i<other.size(); i++) {
        Stack.push_back(other.Stack.at(i));
    }
    //at vector function returns a reference so
    // we can use to make a deep copy
}


/*
 * name:      DatumStack()
 * purpose:   DatumStack overload operator
 * arguments: other Datumstack 
 * returns:   none
 * effects:   Makes this Datumstack equal to other, 
 *            making a copy of objects
 */
DatumStack &DatumStack::operator=(const DatumStack &other) {
    if (this == &other) {
        return *this;
    }
    for (int i=0; i<other.size(); i++) {
        Stack.push_back(other.Stack.at(i));
    }
    //at vector function returns a reference so
    // we can use to make a deep copy
    return *this;
}

/*
 * name:      ~DatumStack()
 * purpose:   DatumStack destructor
 * arguments: none
 * returns:   none
 * effects:   no work neeeded to be done since
              vector class deletes itself
 */
DatumStack::~DatumStack() {

}

/*
 * name:      isEmpty()
 * purpose:   to tell if DatumStack is empty
 * arguments: none
 * returns:   boolean of empty
 * effects:   none 
 */
bool DatumStack::isEmpty() const {
    return Stack.empty();
}

/*
 * name:      clear()
 * purpose:   clear our DatumStack
 * arguments: none
 * returns:   none
 * effects:   calls upon vector method
 */
void DatumStack::clear() {
    Stack.clear();
}

/*
 * name:      size()
 * purpose:   Retrieve the size of our DatumStack
 * arguments: none
 * returns:   Size of our private stack
 * effects:   none
 */
int DatumStack::size() const {
    return Stack.size();
}

/*
 * name:      top
 * purpose:   Retrieve top Datum of our DatumStack
 * arguments: none
 * returns:   Copy of Datum at top of Datumstack
 * effects:   
 */
Datum DatumStack::top() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    return Stack.at(size() - 1);
}


/*
 * name:      pop()
 * purpose:   pops top Datum of our DatumStack()
 * arguments: none
 * returns:   none
 * effects:   Our size decreases by 1
 */
void DatumStack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("empty_stack");
    }
    Stack.pop_back();
}


/*
 * name:      push())
 * purpose:   Pushes Datum element onto our DatumStack
 * arguments: Datum element we want to push
 * returns:   none
 * effects:   none
 */
void DatumStack::push(Datum elem) {
    Stack.push_back(elem);
}