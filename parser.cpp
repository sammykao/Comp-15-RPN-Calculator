/*
 *  parser.h
 *  SAMMY KAO
 *  2/23/2023
 *
 *  CS 15 PROJ2 CALCYOULATER
 *
 *  This file is the definition of the parseRString function, 
    only function definiton in this file
 *
 */

#include <iostream>
#include <sstream>
#include <string>

/*
 * name:      parseRString())
 * purpose:   Parse an input stream to be a full rstring
 * arguments: rest of input stream
 * returns:   Rstring 
 * effects:   Errors thrown if bracket syntax fails
 */
std::string parseRString(std::istream & input) {
    std::stringstream ss;
    std::string command;
    ss << "{";
    int openingbracket = 1;
    //Chopping off starting bracket then inputting 
    //Into function so must add it back to string
    int closingbracket = 0;
    while(not input.eof()) {
        input >> command;
        ss << " " << command;
        if (command == "{") {
            openingbracket++;
        }
        if (command == "}") {
            closingbracket++;
        }
        if (closingbracket == openingbracket) {
            return ss.str();
            //returns once brackets match
        }
    }
    if (not (closingbracket == openingbracket)) {
        throw std::runtime_error("reached end of program when "
                                "searching for }");
    }
    //Only error if file stream ends before brackets close
    return ss.str();
}
