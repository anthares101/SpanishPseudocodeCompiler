/*! 
  \file ipe.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: example 17
 \author   Sergio Gomez Moreales and Ángel Heredia Pérez
 \date     2018 - 4 - 26
 \version  1.0
 \note Novelties
	+ AST: intermidiate code
	+ New statements: if, while, block
*/

#include "./includes/macros.hpp"

// New in example 2
#include <stdio.h>
#include <string>
//

/////////////////////////////
/* 
  NEW in example 16 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "ast/ast.hpp"
////////////////////////////////////////

#include "./parser/interpreter.tab.h"

int lineNumber = 1; //!< Line counter

/* NEW in example 15 */
bool interactiveMode; //!< Control the interactive mode of execution of the interpreter


// New in example 2
extern FILE * yyin; //!< Standard input device for yylex() 
std::string progname; //!<  Program name
//


//////////////////////////////////////////////
// NEW in example 6 

// Use for recovery of runtime errors 
#include <setjmp.h>
#include <signal.h>

// Error recovery functions 
#include "error/error.hpp"


lp::AST *root; //!< Root of the abstract syntax tree AST
///////////////////////////////////////////// 

//////////////////////////////////////////////
// NEW in example 10 

#include "table/init.hpp"


/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors 

//////////////////////////////////////////////
// NEW in example 7 

#include "table/table.hpp"

lp::Table table; //!< Table of Symbols



// cout.precision
#include <iostream>

#include <fstream>

// rand, RAND_MAX
#include <stdlib.h>

std::ofstream errorLog; //!< file pointer to error log

//Date and time
#include <ctime>

//////////////////////////////////////////////////

//! \name Main program

/*! 
	\brief  Main function
	\param  argc: number of command line parameters
	\param  argv: values of command line parameters
	\return int
	\note   C++ requires that main returns an int value
	\sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
 srand (time(NULL)); //Random seed

 // Option -t needed
 // yydebug = 1;
 
 /* 
   If the input file exists 
      then 
           it is set as input device for yylex();
      otherwise
            the input device is the keyboard (stdin)
 */
 if (argc == 2) 
 {

 	std::string filename = argv[1];

	if(filename.find_last_of(".") != std::string::npos &&
	   filename.substr(filename.find_last_of(".")+1) != "e") {

		std::cout << BIRED << 
		"Error: la extensión del fichero no es la correcta\nSaliendo del programa..."
		<< RESET << std::endl;
		exit(EXIT_FAILURE);
	}

	yyin = fopen(argv[1],"r");

	if(yyin != NULL) {
		interactiveMode = false;
	}
	else {
		std::cout << BIRED << "Error: el fichero no existe\nSaliendo del programa..." << RESET << std::endl;
		exit(EXIT_FAILURE);
	}
	 
 }
else
 {
	interactiveMode = true;
	std::cout << CLEAR_SCREEN;
	PLACE(2, 2);
	std::cout << std::endl << BIPURPLE <<
	"Bienvenido al modo interactivo de IPE (Intérprete de Pseudocódigo Español)" << std::endl <<
	"--------------------------------------------------------------------------"
	<< RESET << std::endl;
	std::cout << std::endl << BIYELLOW << ">> " << RESET;
 }

 // Copy the name of the interpreter 
	progname = argv[0];

 /* Number of decimal places */ 
 std::cout.precision(7);

 errorLog.open("error_log.txt");

 time_t current_time;
 struct tm * time_info;
 char timeString[9];
 char dateString[9];

 current_time = time(NULL);
 time(&current_time);
 time_info = localtime(&current_time);

 strftime(dateString, sizeof(dateString), "%D", time_info);

 errorLog << ">>> Entry at: " << dateString << " current time: ";

 strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
 errorLog << timeString << "\n\n";

 /* 
   Table of symbols initialization 
   Must be written before the recovery sentence: setjmp
 */
   init(table);

/* Sets a viable state to continue after a runtime error */
 setjmp(begin);

 /* The name of the function to handle floating-point errors is set */
 signal(SIGFPE,fpecatch);

 // Parser function
  yyparse();

 if (interactiveMode == false)
 {
  /* NEW in example 15 */
  /*  root->print(); */
 	if(root != NULL) {
 		root->evaluate();
 	}
 }

 errorLog.close();

 /* End of program */
 return 0;
}



