/*
 *  main.cpp
 *  SAMMY KAO
 *  2/27/2023
 *
 *  CS 15 PROJ2 CALCYOULATER
 *
 *  Purpose: 
    This file is the main program file of the project.
    It is essentially the user interface of the program. 
    There 
 *
 */


#include <string>
#include <iostream>
#include <fstream>
#include "RPNCalc.h"

/* main
 * Purpose: to run our calculator progra
 * Parameters: none
 * Returns: 0
 * Effects: Acts as main client using our program
 */
int main() {
    RPNCalc calculator;
    calculator.run();
    return 0;
}
