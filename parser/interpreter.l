/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/
/* tolower */
#include <ctype.h>
/*********************/

/*********************/
/* strdup */
#include <string.h>
/*********************/

/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
/*********************/

#include <stack>

/* Macros for the screen */
#include "../includes/macros.hpp"
#include "../includes/states.hpp"

/*********************/
/* 
  NEW in example 16 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

//Definition of the statement stack
std::stack <int> stackedStmts;

bool repeatState = false; //!< Used to manage control statements

%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-Z]

	/*NUMBER1 {DIGIT}+\.?*/

	/*NUMBER2 {DIGIT}*\.{DIGIT}+*/

NUMBER {DIGIT}+(\.{DIGIT}+)?(e[+\-]?{DIGIT}+)?

NUMBER_ERR \.*{NUMBER}(\.{NUMBER}+|(\.|{NUMBER})*)*

IDENTIFIER {LETTER}(({LETTER}|{DIGIT})*("_"({LETTER}|{DIGIT}))*)*

IDENTIFIER_ERR ({LETTER}|{DIGIT}|_)+

/* NEW in example 3 */
/* STATE  */
%x ERROR
%x STRING_STATE
%x COMMENT
%x LONG_COMMENT

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      { 
			/* Line counter */
           	lineNumber++; 

           	if(yyin == stdin) {
           		std::cout << BIYELLOW << ">> " << RESET;
           	}
	
			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
        	/* return NEWLINE; */
        }

";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}


","		{
			/* NEW in example 14 */
			return COMMA;
		}


	/* NÚMEROS */

{NUMBER}  {
					  /* MODIFIED in example 4 */
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext); 

                       return NUMBER; 
                      }


    /* IDENTIFICADORES */


{IDENTIFIER}   		 {
						 

						 //Transform the string to lowerCase to avoid case sensitive
						 for(int i = 0; i < strlen(yytext); i++){
						 	yytext[i] = tolower(yytext[i]);
						 }

						 /* NEW in example 7 */
						 std::string identifier(yytext);
						 /* 
                           strdup() function returns a pointer to a new string 
                           which  is a duplicate of the string yytext
                         */
						  yylval.identifier =  strdup(yytext);

						 /* If the identifier is not in the table of symbols then it is inserted */	
						 if (table.lookupSymbol(identifier) == false)
							{
								/* 
								 The identifier is inserted into the symbol table 
								 as undefined Variable with value 0.0
								*/
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

								/* A pointer to the new NumericVariable is inserted into the table of symbols */
								table.installSymbol(n);

								return VARIABLE;
							}

						/* MODIFIED in example 11 */
						/* 
							If the identifier is in the table of symbols then its token is returned 
								The identifier can be a variable or a numeric constant
						*/
						else 
							{

								if(identifier == "si" ||
								   identifier == "mientras" ||
								   identifier == "repetir" ||
								   identifier == "para" ||
								   identifier == "segun") {

									stackedStmts.push(1);

									if(identifier == "repetir") {
										repeatState = true;
									}
								}

								if((identifier == "fin_si" ||
									identifier == "fin_mientras" ||
									(repeatState && identifier == "hasta") ||
									identifier == "fin_para" ||
									identifier == "fin_segun") && 
									!stackedStmts.empty()) {

									stackedStmts.pop();

									if(repeatState && identifier == "hasta") {
										repeatState = false;
									}
								}

								lp::Symbol	*s = table.getSymbol(identifier);

								/*  If the identifier is in the table then its token is returned  */
								return s->getToken();
							}
                     }


    /* CADENAS */

"'"		{ 	/* String recognition on */
			BEGIN STRING_STATE; 
		}
<STRING_STATE>"'"  { /* String end: returned to default state */
			         BEGIN 0; 
			         yytext[yyleng-1]='\0';

			         std::string aux;

			         //Parse the string searching \n or \t write like 2 characters
			         for(unsigned i = 0; i < yyleng; i++){
						if(yytext[i] == '\\'){
							switch(yytext[i+1]){
								case 'n':
									aux.push_back('\n');

									break;
								case 't':
									aux.push_back('\t');

									break;
								default:
									aux.push_back(yytext[i+1]);

									break;
							}

							i++;
						}
						else
							aux.push_back(yytext[i]);
					}

			         //Use the same type as an identifier id (String)
			         yylval.identifier =  strdup(aux.c_str());
			         return STRING;
					}      

<STRING_STATE>"\\\'"     {yymore();}

<STRING_STATE>\n         {yymore();}

<STRING_STATE>.          {yymore();}


	/* PARÉNTESIS */

"("     { return LPAREN; } 			/* NEW in example 3 */

")"	    { return RPAREN; } 			/* NEW in example 3 */


	/* DOS PUNTOS */

":"		{ return COLON; }


	/* OPERADORES ARITMÉTICOS */

"-"		{ return MINUS;  } 			/* NEW in example 3 */

"+"		{ return PLUS;   } 			/* NEW in example 3 */

"--"	{ return MINUSMINUS;  } 			

"++"	{ return PLUSPLUS;   } 			

"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */

"/"  	{ return DIVISION; } 		/* NEW in example 3 */

(?i:_div)  	{ return DIVISION_INTEGER; }

(?i:_mod)  { return MODULO; }			/* NEW in example 5 */

"**"	{ return POWER; }			/* NEW in example 5 */

":=" 	{ return ASSIGNMENT; }		/* NEW in example 7 */

"+:="	{ return PLUSASSIGNMENT; }

"-:="	{ return MINUSASSIGNMENT; }

"*:="	{ return PRODUCTASSIGNMENT; }

"/:="	{ return DIVISIONASSIGNMENT; }


	/* OPERADORES RELACIONALES */

"="	{ return EQUAL; }			/* NEW in example 15 */

"<>"	{ return NOT_EQUAL; }		/* NEW in example 15 */

">="	{ return GREATER_OR_EQUAL; }/* NEW in example 15 */

"<="	{ return LESS_OR_EQUAL; }	/* NEW in example 15 */

">"		{ return GREATER_THAN; }	/* NEW in example 15 */

"<"		{ return LESS_THAN; }		/* NEW in example 15 */

	/* OPERADOR DE CONCATENACIÓN */
"||"	{ return CONCATENATE; }


	/* OPERADORES LÓGICOS */

(?i:_no)	{ return NOT; }				/* NEW in example 15 */

(?i:_o)	{ return OR; }				/* NEW in example 15 */

(?i:_y)	{ return AND; }				/* NEW in example 15 */


	/* FUNCIONES DE MACROS */

(?i:_borrar)	{ return ERASE; }

(?i:_lugar)	{ return POSITION; }


	/* COMENTARIO DE VARIAS LÍNEAS */

"#" { BEGIN(LONG_COMMENT); }

<LONG_COMMENT>"#" { BEGIN(0); }

<LONG_COMMENT>. ;

<LONG_COMMENT>\n { lineNumber++;  }


	/* COMENTARIO DE UNA LÍNEA */

"@"		{ BEGIN(COMMENT); }

<COMMENT>"@"/(.|\n) { warning("Aviso de comentario anidado", yytext); }

<COMMENT>\n {

	BEGIN(0); 
	lineNumber++; 
}

<COMMENT>. ;

		/*^# {  The interpreter finishes when the symbol # is written at the beginning of the line 
	// std::cout << CLEAR_SCREEN; 
	//  PLACE(24,10);
  	  std::cout <<  BIYELLOW;
   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
 	  std::cout << std::endl;
   	  std::cout << RESET;
	 // PLACE(25,1);

  	  return 0;
		}*/

<<EOF>> { /* The interpreter finishes when finds the end of file character */
		  /*PLACE(24,28);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> Fin de fichero <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);*/

		  if(yyin == stdin) {
		  	std::cout << std::endl;
		  }
	  	  return 0;
	}


{IDENTIFIER_ERR}			{ warning("Identificador incorrecto", yytext);
								  /* Restore the initial state */
   								  BEGIN(INITIAL);
								}


{NUMBER_ERR}				{ warning("Número incorrecto", yytext);
								  /* Restore the initial state */
   								  BEGIN(INITIAL);
								}

.								{ 	
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										The current value of yytext 
										will be concatenated with the next character
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&@#|:]	{ /* MODIFIED in examples 5, 7, 15 */
								  /* NEW in example 3 */
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 

								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1); 
								/* Display the error message */
								warning("Símbolo no permitido", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%

