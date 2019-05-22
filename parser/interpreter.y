/*! 
  \file interpreter.y
  \brief Grammar file
*/


%{
#include <iostream>
#include <string>

/*******************************************/
/* NEW in example 5 */
/* pow */
#include <math.h>
/*******************************************/

/*******************************************/
/* NEW in example 6 */
/* Use for recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>
/*******************************************/

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"
#include "../includes/states.hpp"


/*******************************************/
/* 
  NEW in example 16
  AST class
  IMPORTANT: this file must be before init.hpp
*/
#include "../ast/ast.hpp"


/*******************************************/
/* NEW in example 7 */
/* Table of symbol */
#include "../table/table.hpp"
/*******************************************/

/*******************************************/
#include "../table/numericVariable.hpp"
/*******************************************/

/* NEW in example 15 */
#include "../table/logicalVariable.hpp"

/*******************************************/
/* NEW in example 11 */
#include "../table/numericConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 15 */
#include "../table/logicalConstant.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 13 */
#include "../table/builtinParameter1.hpp"
/*******************************************/

/*******************************************/
/* NEW in example 14 */
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
/*******************************************/


/*******************************************/
/* NEW in example 10 */
#include "../table/init.hpp"
/*******************************************/

/*! 
	\brief  Lexical or scanner function
	\return int
	\note   C++ requires that yylex returns an int value
	\sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

/* NEW in example 15 */
extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter


/***********************************************************/
/* NEW in example 2 */
extern std::string progname; //!<  Program name
/***********************************************************/

/*******************************************/
/* NEW in example 6 */
/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 
/*******************************************/


/*******************************************/
/* NEW in example 7 */
extern lp::Table table; //!< Extern Table of Symbols

/*******************************************/
/* NEW in example 16 */
extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}



/* In case of a syntactic error, more information is shown */
%error-verbose

/* Initial grammar symbol */
%start program

/*******************************************/
/* Data type YYSTYPE  */
/* NEW in example 4 */
%union {
  char * identifier; 				 /* NEW in example 7 */
  double number;  
  bool logic;						 /* NEW in example 15 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  lp::StatementList *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */
}

/* Type of the non-terminal symbols */
// New in example 17: cond
%type <expNode> exp cond 

/* New in example 14 */
%type <parameters> listOfExp  restOfListOfExp

%type <stmts> stmtlist

%type <st> stmt asgn print read if while repeatUntil for erase position

%type <prog> program

// Defined token 

/* Minimum precedence */

/*******************************************/
/* NEW in example 5 */
%token SEMICOLON
/*******************************************/

// Tokens for print sentence
%token PRINT

// Tokens for read sentence
%token READ
%token READ_STRING

// Tokens for conditional sentence
%token IF THEN ELSE ENDIF

// Tokens for while loop
%token WHILE DO ENDWHILE

// Tokens for repeat-until loop
%token REPEAT UNTIL

// Tokens for for loop
%token FOR START INC ENDFOR

// Tokens for macros
%token ERASE POSITION

// NEW in example 17
//%token LETFCURLYBRACKET RIGHTCURLYBRACKET

/* NEW in example 7 */
%right ASSIGNMENT

/* NEW in example 14 */
%token COMMA

/*******************************************/
/* MODIFIED in example 4 */
%token <number> NUMBER
/*******************************************/
%token <identifier> STRING

/*******************************************/
/* NEW in example 15 */
%token <logic> BOOL
/*******************************************/

/* MODIFIED in examples 11, 13 */
%token <identifier> VARIABLE UNDEFINED CONSTANT BUILTIN

/* Left associativity */

/*******************************************************/
/* NEW in example 15 */
%left OR

%left AND

%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN  EQUAL NOT_EQUAL

%left NOT
/*******************************************************/

/* MODIFIED in example 3 */
%left PLUS MINUS CONCATENATE

/* MODIFIED in example 5 */
%left MULTIPLICATION DIVISION MODULO DIVISION_INTEGER

%left LPAREN RPAREN

%nonassoc  UNARY

// Maximum precedence 
/* MODIFIED in example 5 */
%right POWER


%%
//! \name Grammar rules

/* MODIFIED  Grammar in example 16 */

program : stmtlist
		  { 
		    // Create a new AST
			$$ = new lp::AST($1); 

			// Assign the AST to the root
			root = $$; 

			// End of parsing
			//	return 1;
		  }
;

stmtlist:  /* empty: epsilon rule */
		  { 
			// create a empty list of statements
			$$ = new lp::StatementList(); 
		  }  

        | stmtlist stmt 
		  { 
			// copy up the list and add the stmt to it
			$$ = $1;
			$$->addStatement($2);

			// Control the interative mode of execution of the interpreter
			if (interactiveMode == true)
				if(stackedStmts.empty()) {
 			  		$2->evaluate();
				}
           }


        | stmtlist error 
           { 
			// just copy up the stmtlist when an error occurs
			$$ = $1;

			// The previous look-ahead token ought to be discarded with `yyclearin;'
			yyclearin; 
           } 
;
 

stmt: SEMICOLON  /* Empty statement: ";" */
	  {
		// Create a new empty statement node
		$$ = new lp::EmptyStmt(); 
	  }
	| asgn  SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| print SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	| read SEMICOLON
	  {
		// Default action
		// $$ = $1;
	  }
	/*  NEW in example 17 */
	| if 
	 {
		// Default action
		// $$ = $1;
	 }
	/*  NEW in example 17 */
	| while 
	 {
		// Default action
		// $$ = $1;
	 }
	| repeatUntil 
	 {
		// Default action
		// $$ = $1;
	 }
	| for 
	 {
		// Default action
		// $$ = $1;
	 }
	| erase 
	 {
		// Default action
		// $$ = $1;
	 }
	 | position 
	 {
		// Default action
		// $$ = $1;
	 }
;
 
	/*  NEW in example 17 */
if:	/* Simple conditional statement */
	IF cond THEN stmtlist ENDIF
    {
		// Create a new if statement node
		$$ = new lp::IfStmt($2, $4);
	}

	/* Compound conditional statement */
	| IF cond THEN stmtlist ELSE stmtlist ENDIF
	 {
		// Create a new if statement node
		$$ = new lp::IfStmt($2, $4, $6);
	 }

;

	/*  NEW in example 17 */
while:  WHILE cond DO stmtlist ENDWHILE
		{
			// Create a new while statement node
			$$ = new lp::WhileStmt($2, $4);
        }
;

repeatUntil: REPEAT stmtlist UNTIL cond
		{

			// Create a new do-until statement node
			$$ = new lp::RepeatUntilStmt($2, $4);
		}
		| REPEAT stmtlist UNTIL NUMBER
		{

			warning("Error sintáctico: se espera un paréntesis izquierdo ", "");
		}
;	

for: FOR VARIABLE START exp UNTIL exp INC exp DO stmtlist ENDFOR
		{

			// Create a new do-until statement node
			$$ = new lp::ForStmt($2, $4, $6, $8, $10);
		}
		/* Bucle for sin incremento */
		| FOR VARIABLE START exp UNTIL exp DO stmtlist ENDFOR
		{

			// Create a new do-until statement node
			$$ = new lp::ForStmt($2, $4, $6, $8);
		}
		| FOR STRING START exp UNTIL exp INC exp DO stmtlist ENDFOR 
		{
			execerror("Error sintáctico: se espera una variable y se proporcionó una cadena ", "");
		}
		| FOR STRING START exp UNTIL exp DO stmtlist ENDFOR 
		{
			execerror("Error sintáctico: se espera una variable y se proporcionó una cadena ", "");
		}
		| FOR NUMBER START exp UNTIL exp INC exp DO stmtlist ENDFOR 
		{
			execerror("Error sintáctico: se espera una variable y se proporcionó un número ", "");
		}
		| FOR NUMBER START exp UNTIL exp DO stmtlist ENDFOR 
		{
			execerror("Error sintáctico: se espera una variable y se proporcionó un número ", "");
		}

			/*
				Resto de reglas de exp
			*/
;

	/*  NEW in example 17 */
cond: 	LPAREN exp RPAREN
		{ 
			$$ = $2;
		}
;


asgn:   VARIABLE ASSIGNMENT exp 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, $3);
		}

	|  VARIABLE ASSIGNMENT asgn 
		{ 
			// Create a new assignment node
			$$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3);
		}

	   /* NEW in example 11 */ 
	| CONSTANT ASSIGNMENT exp 
		{   
 			execerror("Error semántico en asignación: no se permite modificar una constante ", $1);
		}
	   /* NEW in example 11 */ 
	| CONSTANT ASSIGNMENT asgn 
		{   
 			execerror("Error semántico en asignación múltiple: no se permite modificar una constante ",$1);
		}
;

print:  PRINT exp 
		{
			// Create a new print node
			$$ = new lp::PrintStmt($2);
		}
;	

read:  READ LPAREN VARIABLE RPAREN  
		{
			// Create a new read node
			 $$ = new lp::ReadStmt($3);
		}

	| READ_STRING LPAREN VARIABLE RPAREN 
		{
			// Create a new read string node
			 $$ = new lp::ReadStringStmt($3);
		}

  	  /* NEW rule in example 11 */
	| READ LPAREN CONSTANT RPAREN  
		{   
			execerror("Error semántico en \"sentencia de lectura\": no se permite modificar una constante ", $3);
		}

	| READ LPAREN NUMBER RPAREN
		{
			execerror("Error semántico en \"sentencia de lectura\": no se puede leer una expresión ", "");
		}

	| READ LPAREN STRING RPAREN
		{
			execerror("Error semántico en \"sentencia de lectura\": no se puede leer una expresión ", "");
		}

			/*
				Resto de reglas de exp
			*/

	| READ_STRING LPAREN CONSTANT RPAREN  
		{   
			execerror("Error semántico en \"sentencia de lectura\": no se permite modificar una constante ", $3);
		}

	| READ_STRING LPAREN NUMBER RPAREN
		{
			execerror("Error semántico en \"sentencia de lectura\": no se puede leer una expresión ", "");
		}

	| READ_STRING LPAREN STRING RPAREN
		{
			execerror("Error semántico en \"sentencia de lectura\": no se puede leer una expresión ", "");
		}

			/*
				Resto de reglas de exp
			*/
;


erase: ERASE {

			$$ = new lp::EraseStmt();
		}
;


position: POSITION LPAREN listOfExp RPAREN {

			if($3->size() != 2) {
				execerror("Error sintáctico: número incompatible de argumentos para la función ","_lugar");
			}
			else {

				// Get the expressions from the list of expressions
				lp::ExpNode *e1 = $3->front();
				$3->pop_front();
				lp::ExpNode *e2 = $3->front();

				$$ = new lp::PositionStmt(e1, e2);
			}
		}
;


exp:	NUMBER 
		{ 
			// Create a new number node
			$$ = new lp::NumberNode($1);
		}

	| 	exp PLUS exp 
		{ 
			// Create a new plus node
			 $$ = new lp::PlusNode($1, $3);
		 }

	| 	exp MINUS exp
      	{
			// Create a new minus node
			$$ = new lp::MinusNode($1, $3);
		}

	| 	exp MULTIPLICATION exp 
		{ 
			// Create a new multiplication node
			$$ = new lp::MultiplicationNode($1, $3);
		}

	| 	exp DIVISION exp
		{
		  // Create a new division node	
		  $$ = new lp::DivisionNode($1, $3);
	   }

	 | 	exp DIVISION_INTEGER exp
		{
		  // Create a new division node	
		  $$ = new lp::IntegerDivisionNode($1, $3);
	   }

	| 	LPAREN exp RPAREN
       	{ 
		    // just copy up the expression node 
			$$ = $2;
		 }

  	| 	PLUS exp %prec UNARY
		{ 
		  // Create a new unary plus node	
  		  $$ = new lp::UnaryPlusNode($2);
		}

	| 	MINUS exp %prec UNARY
		{ 
		  // Create a new unary minus node	
  		  $$ = new lp::UnaryMinusNode($2);
		}

	|	exp MODULO exp 
		{
		  // Create a new modulo node	

		  $$ = new lp::ModuloNode($1, $3);
       }

	|	exp POWER exp 
     	{ 
		  // Create a new power node	
  		  $$ = new lp::PowerNode($1, $3);
		}
	|	STRING 
		{ 
			// Create a new string node
			$$ = new lp::StringNode($1);
		}
	|
		exp CONCATENATE exp 
		{ 
			// Create a new plus node
			 $$ = new lp::ConcatenateNode($1, $3);
		}

	 | VARIABLE
		{
		  // Create a new variable node	
		  $$ = new lp::VariableNode($1);
		}

	 | CONSTANT
		{
		  // Create a new constant node	
		  $$ = new lp::ConstantNode($1);

		}

	| BUILTIN LPAREN listOfExp RPAREN
		{
			// Get the identifier in the table of symbols as Builtin
			lp::Builtin *f= (lp::Builtin *) table.getSymbol($1);

			// Check the number of parameters 
			if (f->getNParameters() ==  (int) $3->size())
			{
				switch(f->getNParameters())
				{
					case 0:
						{
							// Create a new Builtin Function with 0 parameters node	
							$$ = new lp::BuiltinFunctionNode_0($1);
						}
						break;

					case 1:
						{
							// Get the expression from the list of expressions
							lp::ExpNode *e = $3->front();

							// Create a new Builtin Function with 1 parameter node	
							$$ = new lp::BuiltinFunctionNode_1($1,e);
						}
						break;

					case 2:
						{
							// Get the expressions from the list of expressions
							lp::ExpNode *e1 = $3->front();
							$3->pop_front();
							lp::ExpNode *e2 = $3->front();

							// Create a new Builtin Function with 2 parameters node	
							$$ = new lp::BuiltinFunctionNode_2($1,e1,e2);
						}
						break;

					default:
							execerror("Error sintáctico: demasiados parámetros para la función ", $1);
				} 
			}
			else
				execerror("Error sintáctico: número de parámetros incompatible para la función ", $1);
		}

	| exp GREATER_THAN exp
	 	{
		  // Create a new "greater than" node	
 			$$ = new lp::GreaterThanNode($1,$3);
		}

	| exp GREATER_OR_EQUAL exp 
	 	{
		  // Create a new "greater or equal" node	
 			$$ = new lp::GreaterOrEqualNode($1,$3);
		}

	| exp LESS_THAN exp 	
	 	{
		  // Create a new "less than" node	
 			$$ = new lp::LessThanNode($1,$3);
		}

	| exp LESS_OR_EQUAL exp 
	 	{
		  // Create a new "less or equal" node	
 			$$ = new lp::LessOrEqualNode($1,$3);
		}

	| exp EQUAL exp 	
	 	{
		  // Create a new "equal" node	
 			$$ = new lp::EqualNode($1,$3);
		}

    | exp NOT_EQUAL exp 	
	 	{
		  // Create a new "not equal" node	
 			$$ = new lp::NotEqualNode($1,$3);
		}

    | exp AND exp 
	 	{
		  // Create a new "logic and" node	
 			$$ = new lp::AndNode($1,$3);
		}

    | exp OR exp 
	 	{
		  // Create a new "logic or" node	
 			$$ = new lp::OrNode($1,$3);
		}

    | NOT exp 
	 	{
		  // Create a new "logic negation" node	
 			$$ = new lp::NotNode($2);
		}
;


listOfExp: 
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

	|  exp restOfListOfExp
			{
				$$ = $2;

				// Insert the expression in the list of expressions
				$$->push_front($1);
			}
;

restOfListOfExp:
			/* Empty list of numeric expressions */
			{
			    // Create a new list STL
				$$ = new std::list<lp::ExpNode *>(); 
			}

		|	COMMA exp restOfListOfExp
			{
				// Get the list of expressions
				$$ = $3;

				// Insert the expression in the list of expressions
				$$->push_front($2);
			}
;



%%



