/*
 *  RPNCalc.h
 *  SAMMY KAO
 *  2/27/2023
 *
 *  CS 15 PROJ2 CALCYOULATER
 *
 *  Purpose: This file is the implementation of the RPNCalc class.
 *  In the class contains public functions such as constructor
 *  or destructor, and a run function (Calls upon private helper
 *  functions). The run function is essentially a wrapper function
 *  of another query function which then calls its own helper functions.
 */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "RPNCalc.h"

/*
 * name:      RPNCalc constructor
 * purpose:   constructs our class
 * arguments: none
 * returns:   none
 * effects:   Nothing needed because stack 
 *            initializes itself
 */
RPNCalc::RPNCalc() {

}

/*
 * name:      RPNCalc destructor
 * purpose:   destructs our class
 * arguments: none
 * returns:   none
 * effects:   Nothing needed because stack 
 *            destructs itself
 */
RPNCalc::~RPNCalc() {

}

/*
 * name:      run
 * purpose:   public query wrapper function
 * arguments: none
 * returns:   none
 * effects:   runs the program
 */
void RPNCalc::run() {
    bool over = queryloop(std::cin);
    //calls private query function
    std::cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name:      queryloop()
 * purpose:   Run query to take in input 
              until user or file quits
 * arguments: none
 * returns:   boolean value (If input had "quit")
 * effects:   Longer than 30 liness because cannot fit 
              all commands without going over
 */
bool RPNCalc::queryloop(std::istream &input) {
    //istream allows us to call this function recursively
    //from the command functions
    std::string command = " ";
    bool user_quit = true;
    while (input >> command) {
        if (command == "quit") {
            return false;
        } else if (command == "not") {
            reversetop();
        } else if (command == "print") {
            print();
        } else if (command == "clear") {
            clear();
        } else if (command == "drop") {
            drop();
        } else if (command == "dup") {
            dup();
        } else if (command == "swap") {
            swap();
        } else if (command == "+" or 
                    command == "-" or 
                    command == "*" or 
                    command == "/" or 
                    command == "mod") {
            mathoperation(command);
        } else if (command == "<" or 
                    command == ">" or 
                    command == "<=" or 
                    command == ">=" or 
                    command == "==") {
            booloperation(command);
        } else if (command == "{") {
            rstrings(input);
        } else if (command == "exec") {
            if (not exec()) {
                return false;
            }
        } else if (command == "file") {
            if (not file()) {
                return false;
            }
        } else if (command == "if") {
            if (not ifcommand()) {
                return false;
            }
        } else {
            tryaddtostack(command);
        }
    }

    return user_quit;
}


/*
 * name:      reversetop()
 * purpose:   takes top assumed bool of stack 
              and push opposite bool value onto stack
 * arguments: none
 * returns:   none
 * effects:   error if stack is empty or top is not bool
 */
void RPNCalc::reversetop() {
    try {
        if (stack.top().getBool()) {
            stack.pop();
            stack.push(Datum(false));
        } else if (not stack.top().getBool()) {
            stack.pop();
            stack.push(Datum(true));
        }
    } catch (std::runtime_error &e) {
        //Catching errors so program can still run
        //Also modular for different types of error messages
        std::cerr << "Error: " << e.what() << std::endl;
    } 
}

/*
 * name:      print()
 * purpose:   prints out top Datum value to user
 * arguments: none
 * returns:   none
 * effects:   error if stack is empty
 */
void RPNCalc::print() { 
    try {
        std::cout << stack.top().toString() << std::endl;
    }
    catch (std::runtime_error &e) {
        //Catching errors so program can still run
        std::cerr << "Error: " << e.what() << "\n";
    }
}

/*
 * name:      clear()
 * purpose:   clears our DatumStack
 * arguments: none
 * returns:   none
 * effects:   none
 */
void RPNCalc::clear() {
    stack.clear();
    //Nothing needed except this because 
    // can clear empty stack (nothing happens)
}

/*
 * name:      drop()
 * purpose:   removes top Datum our DatumStack
 * arguments: none
 * returns:   none
 * effects:   Error if stack is empty
 */
void RPNCalc::drop() {
    try {
        stack.pop();
    }
    catch (std::runtime_error &e) {
        //Catching errors so program can still run after
        std::cerr << "Error: " << e.what() << "\n";
    }
}


/*
 * name:      dup()
 * purpose:   duplicates top Datum object of our stack
 * arguments: none
 * returns:   none
 * effects:   Error if stack is empty
 */
void RPNCalc::dup() {
    try {
        stack.push(stack.top());
    }
    catch (std::runtime_error &e) {
        //Catches error so program still runs
        std::cerr << "Error: " << e.what() << "\n";
    }
}


/*
 * name:      swap()
 * purpose:   swap top two Datum objects
 * arguments: none
 * returns:   none
 * effects:   Error if stack is not size two or more
 */
void RPNCalc::swap() {
    try {
        Datum topDatum = stack.top();
        stack.pop();
        Datum newTop = stack.top();
        stack.pop();
        stack.push(topDatum);
        stack.push(newTop);
    }
    catch (std::runtime_error &e) {
        //Catches error so program still runs
        std::cerr << "Error: " << e.what() << "\n";
    }
}  


/*
 * name:      mathoperation()
 * purpose:   apply calculations to top two
              datum objects based on operation given
 * arguments: operator string
 * returns:   none
 * effects:   Error if stack not size 2 or more and top
 *            two objects are not integers
 */
void RPNCalc::mathoperation(std::string operators) {
    //Must declare these outside try and except so they're declared
    int top, second;
    try {
        Datum topDatum = stack.top();
        stack.pop();
        Datum secondDatum = stack.top();
        stack.pop();
        top = topDatum.getInt();    
        second = secondDatum.getInt();
    } catch (std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
        //Returns early so does not execute commands below
    }
    if (operators == "+") {
        stack.push(Datum(second + top));
    } else if (operators == "-") {
        stack.push(Datum(second - top));
    } else if (operators == "*") {
        stack.push(Datum(second * top));
    } else if (operators == "/") {
        if (top == 0) {
            std::cerr << "Error: division by 0." << std::endl;
            return;
        }
        stack.push(Datum(second / top));
    } else if (operators == "mod") {
        if (top == 0) {
            std::cerr << "Error: division by 0." << std::endl;
            return;
        }
        stack.push(Datum(second % top));
    }
}


/*
 * name:      booloperation()
 * purpose:   apply boolean to top two
              datum objects based on boolean given
 * arguments: operator string
 * returns:   none
 * effects:   Error if stack not size 2 or more and top
 *            two objects are not comparable
 */
void RPNCalc::booloperation(std::string operators) {
    int top, second;
    try {
        Datum topDatum = stack.top();
        stack.pop();
        Datum secondDatum = stack.top();
        stack.pop();
        if (operators == "==") {
            stack.push(Datum(topDatum.toString() == 
                            secondDatum.toString()));
            return;
        } 
        //Can have == compare two different datum types
        top = topDatum.getInt();
        second = secondDatum.getInt();
    } catch (std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;\
        return;
        //Returns so does not execute functions below
    }
    if (operators == "<") {
        stack.push(Datum(second < top));
    } else if (operators == ">") {
        stack.push(Datum(second > top));
    } else if (operators == "<=") {
        stack.push(Datum(second <= top));
    } else if (operators == ">=") {
        stack.push(Datum(second >= top));
    }
}


/*
 * name:      tryaddtostack()
 * purpose:   Try to add an object to our stack
 * arguments: command string
 * returns:   none
 * effects:   Error if cannot create a valid datum to add
 */
void RPNCalc::tryaddtostack(std::string command) {
    if (command == "#t") {
        stack.push(Datum(true));
        return;
    } else if (command == "#f") {
        stack.push(Datum(false));
        return;
    }
    //Input must either be integer or boolean (Factored in above)
    // So must be able to see if our string can convert to integer
    // Seen below using stringstream 
    std::stringstream ss(command);
    int x = 0;
    ss >> x;
    if (ss.fail()) {
        std::cerr << command << ": unimplemented" << std::endl;
        return;
    }
    stack.push(Datum(x));
}

/*
 * name:      rstrings()
 * purpose:   Parse an assumed rstring and 
              add the Datum to stack
 * arguments: input stream
 * returns:   none
 * effects:   Error if is not r strings
 */
void RPNCalc::rstrings(std::istream &input) {
    try {
        //Calls upon previously written function in different file
        stack.push(Datum(parseRString(input)));
    } catch (std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << "\n"; 
    }
}

/*
 * name:      exec()
 * purpose:   executes top rstring on stop
 * arguments: none
 * returns:   boolean value of whether the rstring 
              contained {quit}
 * effects:   Top datum on stack must be rstring type
 */
bool RPNCalc::exec() {
    try {
        Datum d = stack.top();
        if (not d.isRString()) {
            std::cerr << "Error: cannot execute non rstring\n";
            return true;
        }
        std::string rstring = d.getRString();
        if (rstring == "{ }") {
            return true;
        }
        //Use substr method to chop off brackets and whitespaces in string
        std::istringstream iss(rstring.substr(2, rstring.length() - 4));
        return queryloop(iss);
    } catch (std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << "\n"; 
    }
    return true;
}

/*
 * name:      file()
 * purpose:   opens file named in top rstring
 * arguments: none
 * returns:   boolean value of whether the "quit"
              command was contained in the file
 * effects:   Error if is not r string on top or not filename
 */
bool RPNCalc::file() {
    std::string rstring = " ";
    try {
        Datum d = stack.top();
        if (not d.isRString()) {
            std::cerr << "Error: file operand not rstring\n";
            return true;
        }
        rstring = d.getRString();
        stack.pop();
    } catch (std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << "\n"; 
        return true;
    }
    std::string filename = rstring.substr(2, (rstring.length() - 4));
    //Use substr to chop off brackets and trailing whitespace
    std::ifstream infile;
    infile.open(filename);
    if (not infile.is_open()) {
        std::cerr << "Unable to read " << filename << std::endl;
        return true;
    }
    bool user_quit = queryloop(infile);
    infile.close();
    return user_quit;
}

/*
 * name:      ifcommand()
 * purpose:   executes the boolean case of r string 
              of third bool in stack
 * arguments: none
 * returns:   boolean value if one of the rstrings
              contained "quit"
 * effects:   Error if (stack is not size 3 or above)
              or (third to top is not bool) or 
              (top two are not rstrings)
 */
bool RPNCalc::ifcommand() {
    try  {
        Datum falseCase = stack.top();
        stack.pop();
        Datum trueCase = stack.top();
        stack.pop();
        Datum testBool = stack.top();
        stack.pop();
        if (not (testBool.isBool())) {
            std::cerr << "Error: expected boolean in if test\n";
            return true;
        } else if (not (falseCase.isRString() and trueCase.isRString())) {
            std::cerr << "Error: expected rstring in if branch\n";
            return true;
        } 
        std::string rstring;
        if (testBool.toString() == "#t") {
            rstring = trueCase.toString();
        } else {
            rstring = falseCase.toString();
        }
        if (rstring == "{ }") {
            return true;
        }
        //Use substr method to chop off brackets and whitespaces in string
        std::istringstream iss(rstring.substr(2, rstring.length() - 4));
        return queryloop(iss);
    } catch (std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return true;
}
