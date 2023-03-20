/*
 *  RPNCalc.h
 *  SAMMY KAO
 *  2/27/2023
 *
 *  CS 15 PROJ2 CALCYOULATER
 *
 *  Purpose: This file is the interface of the RPNCalc class
 *          Listed below is the class with its functions and
 *           data structures. Only constructor, destructor, and 
 *           wrapper query function are public while the other 
 *           command functions are private so 'client' has no outside
 *           acess except running the program.
 *
 */


#ifndef __RPNCALC_H_
#define __RPNCALC_H_

#include <string>
#include <iostream>
#include <fstream>
#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
class RPNCalc {
public:
    RPNCalc();
    ~RPNCalc();
    //Only public function
    void run();
    //Subset functions will be private

private:
    DatumStack stack;
    bool queryloop(std::istream &input);
    //Query functions

    void reversetop();
    void print();
    void clear();
    void drop();
    void dup();
    void swap();
    //Simple commands

    void mathoperation(std::string operators);
    void booloperation(std::string operators);
    //Math operations

    void rstrings(std::istream &input);
    bool exec();
    bool file();
    bool ifcommand();
    //Complex commands

    void tryaddtostack(std::string command);
    //Final function and can also 
    //tell if input not valid
};

#endif
