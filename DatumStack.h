/*
 *  DatumStack.h
 *  SAMMY KAO
 *  2/23/2023
 *
 *  CS 15 PROJ2 CALCYOULATER
 *
 *  Purpose: This file is the implementation of 
 *  the DatumStack class to use for our RPNCalc
 *  it's essentially building a stack to use 
 *  with some public wrapper functions on the private vector
 */


#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Datum.h"


class DatumStack {
public:
    //Constructors and the Big Three
    DatumStack();
    DatumStack(Datum arr[], int arrsize);
    DatumStack(const DatumStack &other);
    DatumStack &operator=(const DatumStack &other);
    ~DatumStack();

    //Retrieval functions
    bool isEmpty() const;
    void clear();
    int size() const;
    Datum top();

    //Insert and delete functions
    void pop();
    void push(Datum elem);



private:
    std::vector<Datum> Stack;
    //Datum vector that acts as our DatumStack
};

#endif
