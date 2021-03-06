/*!	
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author  
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <list>

// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

// 
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/stringVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType() 
{ 
	// Get the identifier in the table of symbols as Variable
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::print() 
{
  std::cout << "VariableNode: " << this->_id << std::endl;
  std::cout << "Type: " << this->getType() << std::endl;
}


double lp::VariableNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateNumber(): la variable no es numérica", 
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateBool(): la variable no es booleana",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}


std::string lp::VariableNode::evaluateString() 
{ 
	std::string result = "";

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::StringVariable *var = (lp::StringVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución evaluateNumber(): la variable no es cadena", 
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::print() 
{
  std::cout << "ConstantNode: " << this->_id << std::endl;
  std::cout << "Type: " << this->getType() << std::endl;
}

int lp::ConstantNode::getType() 
{ 
	// Get the identifier in the table of symbols as Constant
	lp::Constant *var = (lp::Constant *) table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateNumber(): la constante no es numérica", 
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *) table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error en tiempo de ejecución en evaluateBool(): la constante no es booleana",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::print()
{
  std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber() 
{ 
    return this->_number; 
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::StringNode::getType()
{
	return STRING;
}


void lp::StringNode::print()
{
  std::cout << "StringNode: " << this->_string << std::endl;
}

std::string lp::StringNode::evaluateString() 
{ 
    return this->_string; 
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == NUMBER)
	{
		result = NUMBER;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "Operador Numérico Unario");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == BOOL)
	{
		result = BOOL;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "Operador Lógico Unario");
	}
	
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = NUMBER;
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "Operador Numérico");

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;
		
	if ( ((this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER)) or
		 ((this->_left->getType() == STRING) and (this->_right->getType() == STRING)) or
		 ((this->_left->getType() == BOOL) and (this->_right->getType() == BOOL)) )
		result = BOOL;
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "Operador Relacional");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
	{
		// 
		result = BOOL;
	}
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "Operador Lógico");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::StringOperatorNode:: getType()
{
	int result = 0;
		
	if ( ((this->_left->getType() == STRING) and (this->_right->getType() == STRING)) or 
		 ((this->_left->getType() == NUMBER) and (this->_right->getType() == STRING)) or
		 ((this->_left->getType() == STRING) and (this->_right->getType() == NUMBER)) or
		 ((this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER)) or
		 ((this->_left->getType() == BOOL) and (this->_right->getType() == STRING)) or
		 ((this->_left->getType() == STRING) and (this->_right->getType() == BOOL)) or
		 ((this->_left->getType() == BOOL) and (this->_right->getType() == BOOL)) )
	{
		// 
		result = STRING;
	}
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "Operador de Cadenas");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print() 
{
  std::cout << "UnaryMinusNode: "  << std::endl;
  std::cout << "-";
  this->_exp->print();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Menos Unario");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print() 
{
  std::cout << "UnaryPlusNode: "  << std::endl;
  this->_exp->print();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ","Más Unario");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print() 
{
  std::cout << "PlusNode: "  << std::endl;
  this->_left->print();
  std::cout << " + ";
  this->_right->print();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Más");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print() 
{
  std::cout << "MinusNode: "  << std::endl;
  this->_left->print();
  std::cout << " - ";
  this->_right->print();
}

double lp::MinusNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Menos");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print() 
{
	std::cout << "MultiplicationNode: "  << std::endl;
	this->_left->print();
	std::cout << " * ";
	this->_right->print();
}

double lp::MultiplicationNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ","Multiplicación");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
  std::cout << "DivisionNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::DivisionNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Error en tiempo de ejecución", "División por cero");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "División");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IntegerDivisionNode::print()
{
  std::cout << "IntegerDivisionNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::IntegerDivisionNode::evaluateNumber() 
{
	int result = 0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			warning("Error en tiempo de ejecución", "División por cero");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "División Entera");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
  std::cout << "ModuloNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::ModuloNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
    	if(std::abs(rightNumber) > ERROR_BOUND)
				result = (int) leftNumber % (int) rightNumber;
		else
			warning("Error en tiempo de ejecución", "División por cero");
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Módulo");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print() 
{
	std::cout << "PowerNode: "  << std::endl;
	this->_left->print();
	std::cout << " ^ ";
	this->_right->print();
}

double lp::PowerNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ", "Potencia");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenateNode::print() 
{
  std::cout << "ConcatenateNode: "  << std::endl;
  this->_left->print();
  std::cout << " || ";
  this->_right->print();
}

std::string lp::ConcatenateNode::evaluateString()
{
	std::string result = "";

	// Ckeck the types of the expressions
	if (this->getType() == STRING)
	{
		std::ostringstream aux;
  		
		if((this->_left->getType() == NUMBER) and (this->_right->getType() == STRING)){
			aux << this->_left->evaluateNumber() << this->_right->evaluateString();
			result = aux.str();
		}
		else if((this->_left->getType() == STRING) and (this->_right->getType() == NUMBER)){
			aux << this->_left->evaluateString() << this->_right->evaluateNumber();
			result = aux.str();
		}
		else if((this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER)){
			aux << this->_left->evaluateNumber() << this->_right->evaluateNumber();
			result = aux.str();
		}
		else if((this->_left->getType() == STRING) and (this->_right->getType() == BOOL)){
			aux << this->_left->evaluateString() << this->_right->evaluateBool();
			result = aux.str();
		}
		else if((this->_left->getType() == BOOL) and (this->_right->getType() == STRING)){
			aux << this->_left->evaluateBool() << this->_right->evaluateString();
			result = aux.str();
		}
		else if((this->_left->getType() == BOOL) and (this->_right->getType() == BOOL)){
			aux << this->_left->evaluateBool() << this->_right->evaluateBool();
			result = aux.str();
		}
		else if((this->_left->getType() == STRING) and (this->_right->getType() == STRING))
			result = this->_left->evaluateString() + this->_right->evaluateString();
		else
			warning("Error en tiempo de ejecución: las expresiones no son alfanuméricas para ", "Concatenar");
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son alfanuméricas para ", "Concatenar");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::print() 
{
	std::cout << "BuiltinFunctionNode_0: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( ) " ;
}

double lp::BuiltinFunctionNode_0::evaluateNumber() 
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;
		
	if (this->_exp->getType() == NUMBER)
		result = NUMBER;
	else
		warning("Error en tiempo de ejecución: tipo incompatible para ", "BuiltinFunctionNode_1");

	return	result;
}

void lp::BuiltinFunctionNode_1::print() 
{
	std::cout << "BuiltinFunctionNode_1: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_1::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo de parámetro incompatible para ", this->_id);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;
		
	if (this->_exp1->getType() == this->_exp2->getType())
		result = this->_exp1->getType();
	else
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "BuiltinFunctionNode_2");

	return	result;
}


void lp::BuiltinFunctionNode_2::print() 
{
	std::cout << "BuiltinFunctionNode_2: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp1->print();
	std::cout << " , " ;
	this->_exp2->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_2::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
	  	result = f->getFunction()(this->_exp1->evaluateNumber(),this->_exp2->evaluateNumber());
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos de parámetros incompatibles para ", this->_id);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
  std::cout << "GreaterThanNode: " << std::endl;
  this->_left->print();
  std::cout << " > ";
  this->_right->print();
}

bool lp::GreaterThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{	//getType already check if left and right parameter are string or number. This is used to know if they are string or number
		switch(this->_left->getType()){
			case NUMBER:{
				double leftNumber, rightNumber;

				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				result = (leftNumber > rightNumber);

				break;
			}
			case STRING:{
				std::string leftString, rightString;

				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				result = (leftString > rightString);

				break;
			}
			case BOOL:{
				bool leftBool, rightBool;

				leftBool = this->_left->evaluateBool();
				rightBool = this->_right->evaluateBool();

				result = (leftBool > rightBool);

				break;
			}
			default:
				warning("Error en tiempo de ejecución: tipos de parámetros incompatibles para ", "operador Mayor que");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos de parámetros incompatibles para ", "operador Mayor que");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
  std::cout << "GreaterOrEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " >= ";
  this->_right->print();
}

bool lp::GreaterOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{	//getType already check if left and right parameter are string or number. This is used to know if they are string or number
		switch(this->_left->getType()){
			case NUMBER:{
				double leftNumber, rightNumber;

				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				result = ((leftNumber > rightNumber) || (std::abs( (leftNumber - rightNumber)) < ERROR_BOUND));

				break;
			}
			case STRING:{
				std::string leftString, rightString;

				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				result = (leftString >= rightString);

				break;
			}
			case BOOL:{
				bool leftBool, rightBool;

				leftBool = this->_left->evaluateBool();
				rightBool = this->_right->evaluateBool();

				result = (leftBool >= rightBool);

				break;
			}
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "operador mayor o igual");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador mayor o igual");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
  std::cout << "LessThanNode: " << std::endl;
  this->_left->print();
  std::cout << " < ";
  this->_right->print();
}

bool lp::LessThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{	//getType already check if left and right parameter are string or number. This is used to know if they are string or number
		switch(this->_left->getType()){
			case NUMBER:{
				double leftNumber, rightNumber;

				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				result = (leftNumber < rightNumber);

				break;
			}
			case STRING:{
				std::string leftString, rightString;

				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				result = (leftString < rightString);

				break;
			}
			case BOOL:{
				bool leftBool, rightBool;

				leftBool = this->_left->evaluateBool();
				rightBool = this->_right->evaluateBool();

				result = (leftBool < rightBool);

				break;
			}
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "operador menor que");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador menor que");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
  std::cout << "LessOrEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " <= ";
  this->_right->print();
}

bool lp::LessOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{	//getType already check if left and right parameter are string or number. This is used to know if they are string or number
		switch(this->_left->getType()){
			case NUMBER:{
				double leftNumber, rightNumber;

				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				result = ((leftNumber < rightNumber) || (std::abs( (leftNumber - rightNumber)) < ERROR_BOUND));

				break;
			}
			case STRING:{
				std::string leftString, rightString;

				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				result = (leftString <= rightString);

				break;
			}
			case BOOL:{
				bool leftBool, rightBool;

				leftBool = this->_left->evaluateBool();
				rightBool = this->_right->evaluateBool();

				result = (leftBool <= rightBool);

				break;
			}
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "operador menor o igual");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador menor o igual");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
  std::cout << "EqualNode: " << std::endl;
  this->_left->print();
  std::cout << " = ";
  this->_right->print();
}

bool lp::EqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{	//getType already check if left and right parameter are string or number. This is used to know if they are string or number
		switch(this->_left->getType()){
			case NUMBER:{
				double leftNumber, rightNumber;

				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = std::abs( (leftNumber - rightNumber)) < ERROR_BOUND ;

				break;
			}
			case STRING:{
				std::string leftString, rightString;

				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				result = (leftString == rightString);

				break;
			}
			case BOOL:{
				bool leftBool, rightBool;

				leftBool = this->_left->evaluateBool();
				rightBool = this->_right->evaluateBool();

				result = (leftBool == rightBool);

				break;
			}
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "operador igualdad");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador igualdad");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
  std::cout << "NotEqualNode: " << std::endl;
  this->_left->print();
  std::cout << " != ";
  this->_right->print();
}

bool lp::NotEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{	//getType already check if left and right parameter are string or number. This is used to know if they are string or number
		switch(this->_left->getType()){
			case NUMBER:{
				double leftNumber, rightNumber;

				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = std::abs( (leftNumber - rightNumber)) >= ERROR_BOUND;

				break;
			}
			case STRING:{
				std::string leftString, rightString;

				leftString = this->_left->evaluateString();
				rightString = this->_right->evaluateString();

				result = (leftString != rightString);

				break;
			}
			case BOOL:{
				bool leftBool, rightBool;

				leftBool = this->_left->evaluateBool();
				rightBool = this->_right->evaluateBool();

				result = (leftBool != rightBool);

				break;
			}
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "operador desigualdad");
		}
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador desigualdad");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
  std::cout << "AndNode: " << std::endl;
  this->_left->print();
  std::cout << " && ";
  this->_right->print();
}

bool lp::AndNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador conjunción");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
  std::cout << "OrNode: " << std::endl;
  this->_left->print();
  std::cout << " || ";
  this->_right->print();
}

bool lp::OrNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		warning("Error en tiempo de ejecución: tipo incompatible para ", "operador disyunción");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
  std::cout << "NotNode: " << std::endl;
  std::cout << " ! ";
  this->_exp->print();
}

bool lp::NotNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "operador negación");
	}

	return result;
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print() 
{
  std::cout << "assignment_node: "  << std::endl;
  std::cout << this->_id << " := ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::AssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::NumericVariable *v = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,value);
					table.installSymbol(v);
				}
			}
			break;

			case STRING:
			{
				std::string value;
				// evaluate the expression as STRING
			 	value = this->_exp->evaluateString();

				// Check the type of the first varible
				if (firstVar->getType() == STRING)
				{
				  	// Get the identifier in the table of symbols as StringVariable
					lp::StringVariable *v = (lp::StringVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::StringVariable *v = new lp::StringVariable(this->_id,
											VARIABLE,STRING,value);
					table.installSymbol(v);
				}
			}
			break;

			case BOOL:
			{
				bool value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateBool();

				if (firstVar->getType() == BOOL)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::LogicalVariable *v = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value 
					lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,value);
					table.installSymbol(v);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else if(this->_asgn != NULL)// this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->getId());

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value of the previous variable 
					lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case STRING:
			{
				/* Get the identifier of the previous asgn in the table of symbols as StringVariable */
				lp::StringVariable *secondVar = (lp::StringVariable *) table.getSymbol(this->_asgn->getId());
				// Check the type of the first variable
				if (firstVar->getType() == STRING)
				{
					/* Get the identifier of the first variable in the table of symbols as StringVariable */
					lp::StringVariable *firstVar = (lp::StringVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not STRING
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value of the previous variable 
					lp::StringVariable *firstVar = new lp::StringVariable(this->_id,
											VARIABLE,STRING,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case BOOL:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::LogicalVariable *secondVar = (lp::LogicalVariable *) table.getSymbol(this->_asgn->getId());
				// Check the type of the first variable
				if (firstVar->getType() == BOOL)
				{
					/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
					lp::LogicalVariable *firstVar = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not BOOL
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value of the previous variable 
					lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}
	}

	else if(this->_unaryNode != NULL) { //if this->_unaryNode is not NULL
		// IMPORTANT
		// evaluate the assigment child (Will be done later if the unary operator is after the variable)
		if(_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_unaryNode->getId());

		switch(secondVar->getType()) {
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_unaryNode->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());
				}
				else {
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::NumericVariable *v = new lp::NumericVariable(this->_id, VARIABLE, NUMBER, secondVar->getValue());
					table.installSymbol(v);
				}
			}
				break;
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

		// IMPORTANT
		// evaluate the assigment child if it wasnt done
		if(!_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusAssignmentStmt::print() 
{
  std::cout << "plusAssignment_node: "  << std::endl;
  std::cout << this->_id << " +:= ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::PlusAssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(v->getValue() + value);
				}
				// The type of variable is not NUMBER
				else
				{
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else if(this->_asgn != NULL)// this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_id);

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(firstVar->getValue() + secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}
	}
	else if(this->_unaryNode != NULL) { //if this->_unaryNode is not NULL
		// IMPORTANT
		// evaluate the assigment child (Will be done later if the unary operator is after the variable)
		if(_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_unaryNode->getId());

		switch(secondVar->getType()) {
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_unaryNode->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(firstVar->getValue() + secondVar->getValue());
				}
				else {
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
				break;
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

		// IMPORTANT
		// evaluate the assigment child if it wasnt done
		if(!_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusAssignmentStmt::print() 
{
  std::cout << "minusAssignment_node: "  << std::endl;
  std::cout << this->_id << " -:= ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::MinusAssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(v->getValue() - value);
				}
				// The type of variable is not NUMBER
				else
				{
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else if(this->_asgn != NULL)// this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->getId());

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(firstVar->getValue() - secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}
	}
	else if(this->_unaryNode != NULL) { //if this->_unaryNode is not NULL
		// IMPORTANT
		// evaluate the assigment child (Will be done later if the unary operator is after the variable)
		if(_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_unaryNode->getId());

		switch(secondVar->getType()) {
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_unaryNode->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(firstVar->getValue() - secondVar->getValue());
				}
				else {
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
				break;
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

		// IMPORTANT
		// evaluate the assigment child if it wasnt done
		if(!_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ProductAssignmentStmt::print() 
{
  std::cout << "productAssignment_node: "  << std::endl;
  std::cout << this->_id << " *:= ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::ProductAssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(v->getValue() * value);
				}
				// The type of variable is not NUMBER
				else
				{
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else if(this->_asgn != NULL)// this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->getId());

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(firstVar->getValue() * secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}
	}
	else if(this->_unaryNode != NULL) { //if this->_unaryNode is not NULL
		// IMPORTANT
		// evaluate the assigment child (Will be done later if the unary operator is after the variable)
		if(_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_unaryNode->getId());

		switch(secondVar->getType()) {
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_unaryNode->getId());
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
					/* Get the identifier of the first variable in the table of symbols as NumericVariable */
					lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(firstVar->getValue() * secondVar->getValue());
				}
				else {
					warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
				}
			}
				break;
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

		// IMPORTANT
		// evaluate the assigment child if it wasnt done
		if(!_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionAssignmentStmt::print() 
{
  std::cout << "divisionAssignment_node: "  << std::endl;
  std::cout << this->_id << " /:= ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::DivisionAssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

			 	if(std::abs(value) > ERROR_BOUND) {
					// Check the type of the first varible
					if (firstVar->getType() == NUMBER)
					{
					  	// Get the identifier in the table of symbols as NumericVariable
						lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

						// Assignment the value to the identifier in the table of symbols
						v->setValue(v->getValue() / value);
					}
					// The type of variable is not NUMBER
					else
					{
						warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
					}
				}
				else {
					warning("Error en tiempo de ejecución", "División por cero");
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else if(this->_asgn != NULL)// this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->getId());

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->getId());

				if(std::abs(secondVar->getValue()) > ERROR_BOUND) {
					// Check the type of the first variable
					if (firstVar->getType() == NUMBER)
					{
						/* Get the identifier of the first variable in the table of symbols as NumericVariable */
						lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

						// Assignment the value of the second variable to the first variable
						firstVar->setValue(firstVar->getValue() / secondVar->getValue());

					}
					// The type of variable is not NUMBER
					else
					{
						warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
					}
				}
				else {
					warning("Error en tiempo de ejecución", "División por cero");
				}
			}
			break;

			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}
	}
	else if(this->_unaryNode != NULL) { //if this->_unaryNode is not NULL
		// IMPORTANT
		// evaluate the assigment child (Will be done later if the unary operator is after the variable)
		if(_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_unaryNode->getId());

		switch(secondVar->getType()) {
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_unaryNode->getId());

				if(std::abs(secondVar->getValue()) > ERROR_BOUND) {
					// Check the type of the first variable
					if (firstVar->getType() == NUMBER)
					{
						/* Get the identifier of the first variable in the table of symbols as NumericVariable */
						lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);

						// Assignment the value of the second variable to the first variable
						firstVar->setValue(firstVar->getValue() / secondVar->getValue());

					}
					// The type of variable is not NUMBER
					else
					{
						warning("Error en tiempo de ejecución: la variable no es numérica ", this->_id);
					}
				}
				else {
					warning("Error en tiempo de ejecución", "División por cero");
				}
			}
				break;
			default:
				warning("Error en tiempo de ejecución: tipo incompatible para ", "asignación");
		}

		// IMPORTANT
		// evaluate the assigment child if it wasnt done
		if(!_unaryNode->beforeVariable())
			this->_unaryNode->evaluate();
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::print() 
{
  std::cout << "PrintStmt: "  << std::endl;
  std::cout << " print ";
  this->_exp->print();
  std::cout << std::endl;
}


void lp::PrintStmt::evaluate() 
{

	switch(this->_exp->getType())
	{
		case NUMBER:
				std::cout << this->_exp->evaluateNumber();
				break;
		case STRING:
				std::cout << this->_exp->evaluateString();
				break;
		case BOOL:
			if (this->_exp->evaluateBool())
				std::cout << "verdadero";
			else
				std::cout << "falso";
		
			break;

		default:
			warning("Error en tiempo de ejecución: tipo incompatible para ", "escribir");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print() 
{
  std::cout << "ReadStmt: "  << std::endl;
  std::cout << " leer (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate() 
{   
	double value; 
	std::cin >> value;
	std::cin.ignore();

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == NUMBER)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable 
		// with the type NUMBER and the read value 
		lp::NumericVariable *n = new lp::NumericVariable(this->_id, 
									  VARIABLE,NUMBER,value);

		table.installSymbol(n);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStringStmt::print() 
{
  std::cout << "ReadStringStmt: "  << std::endl;
  std::cout << " leer_cadena (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadStringStmt::evaluate() 
{   
	std::string in_string;
	std::string value;

	std::getline(std::cin, in_string);

    //Parse in_string searching \n or \t write like 2 characters
    for(unsigned i = 0; i < in_string.size(); i++){
		if(in_string[i] == '\\'){
			switch(in_string[i+1]){
				case 'n':
					value.push_back('\n');

					break;
				case 't':
					value.push_back('\t');

					break;
				default:
					value.push_back(in_string[i+1]);

					break;
			}

			i++;
		}
		else
			value.push_back(in_string[i]);
	}

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is STRING
	if (var->getType() == STRING)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::StringVariable *n = (lp::StringVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not STRING
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as StringVariable 
		// with the type STRING and the read value 
		lp::StringVariable *n = new lp::StringVariable(this->_id, 
									  VARIABLE,STRING,value);

		table.installSymbol(n);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EraseStmt::print() 
{
  std::cout << "EraseStmt: "  << std::endl;
  std::cout << " _borrar()";
  std::cout << std::endl;
}


void lp::EraseStmt::evaluate() 
{   
	std::cout << CLEAR_SCREEN << std::endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PositionStmt::print() 
{
  std::cout << "PositionStmt: "  << std::endl;
  std::cout << " _lugar(" << (int) this->_x->evaluateNumber() << ", " << (int) this->_y->evaluateNumber() << ")";
  std::cout << std::endl;
}


void lp::PositionStmt::evaluate() 
{   

	if(this->_x->getType() == NUMBER && this->_y->getType() == NUMBER) {
		//printf("\033[%d;%dH", (int) this->_x->evaluateNumber(), (int) this->_y->evaluateNumber());
		PLACE((int) this->_x->evaluateNumber(), (int) this->_y->evaluateNumber());
	}
	else {
		warning("Error en tiempo de ejecución: tipos incompatibles para ", "_lugar");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::print() 
{
  std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate() 
{
  // Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::IfStmt::print() 
{
  std::cout << "IfStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Consequent
  this->_consequent->print();

 // The alternative is printed if exists
  if (this->_alternative != NULL)
	  this->_alternative->print();

  std::cout << std::endl;
}


void lp::IfStmt::evaluate() 
{
   // If the condition is true,
	if (this->_cond->evaluateBool() == true ) {
     // the consequent is run 
	  this->_consequent->evaluate();
	}
    // Otherwise, the alternative is run if exists
	else if (this->_alternative != NULL) {
		this->_alternative->evaluate();
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::WhileStmt::print() 
{
  std::cout << "WhileStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Body of the while loop
  this->_stmts->print();

  std::cout << std::endl;
}


void lp::WhileStmt::evaluate() 
{
  // While the condition is true. the body is run 
  while (this->_cond->evaluateBool() == true)
  {	
	  this->_stmts->evaluate();
  }

}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::RepeatUntilStmt::print() 
{
  std::cout << "RepeatUntilStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Body of the while loop
  this->_stmts->print();

  std::cout << std::endl;
}


void lp::RepeatUntilStmt::evaluate() 
{

  do {

  	this->_stmts->evaluate();

  }while(!this->_cond->evaluateBool());
}


///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

void lp::ForStmt::print() 
{
  std::cout << "ForStmt: "  << std::endl;

  // Variable
  std::cout << this->_var << std::endl;

  // Start
  this->_start->print();

  // End
  this->_end->print();

  // Increment
  this->_inc->print();

  // Body of the while loop
  this->_stmts->print();

  std::cout << std::endl;
}


void lp::ForStmt::evaluate() 
{

	double start = 0.0, end = 0.0, inc = 0.0;
	bool error = false;

	//Primero se comprueba que cada elemento del bucle for sea
	//una expresión numérica y, si lo son, se obtienen sus valores
	if(this->_inc != NULL) {
		if(this->_start->getType() != NUMBER ||
			this->_end->getType() != NUMBER ||
			this->_inc->getType() != NUMBER) {
			warning("Error en tiempo de ejecución: tipos incompatibles para ", "para");
			error = true;
		}
		else {
				start = this->_start->evaluateNumber();
				end = this->_end->evaluateNumber();
				inc = this->_inc->evaluateNumber();
		}
	}
	else {
		if(this->_start->getType() != NUMBER ||
			this->_end->getType() != NUMBER) {
			warning("Error en tiempo de ejecución: tipos incompatibles para ", "para");
			error = true;
		}
		else {
			start = this->_start->evaluateNumber();
			end = this->_end->evaluateNumber();
			inc = 1.0;
		}
	}

	if((start > end && inc > 0.0) || (start < end && inc < 0.0)) {
		if(!error) {
			warning("Error en tiempo de ejecución: el comienzo no concuerda con el fin según el paso para ", "para");
		}
		return;
	}

	if(std::abs(0.0 - inc) < ERROR_BOUND) {
		if(!error) {
			warning("Error de bucle infinito para ", "para");
		}
		return;
	}

	//Se comprueba si la tabla contiene el simbolo
	//y se borra
	if(table.lookupSymbol(this->_var)) {
		table.eraseSymbol(this->_var);
	}

	//Se crea una nueva variable numérica con el mismo
	//identificador y se instala en la tabla de símbolos
	lp::NumericVariable *v = new lp::NumericVariable(this->_var,
											VARIABLE,NUMBER,start);

	table.installSymbol(v);

	double i;
	if(inc >= 0) {
		for(i = start; i <= end; i = i + inc) {
			v->setValue(i);
			this->_stmts->evaluate();
		}
	}
	else {
		for(i = start; i >= end; i = i + inc) {
			v->setValue(i);
			this->_stmts->evaluate();
		}
	}
	v->setValue(i);
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::SwitchStmt::print() 
{
  std::cout << "SwitchStmt: "  << std::endl;

  // Variable
  this->_exp->print();

  // Start
  this->_caseList->print();

  std::cout << std::endl;
}


void lp::SwitchStmt::evaluate() {

	/*if(this->_exp->getType() == NUMBER) {

		double value = this->_exp->evaluateNumber();

		this->_caseList->evaluate((int) value);

	}*/
	if(this->_exp->getType() == NUMBER || this->_exp->getType() == STRING) {

		this->_caseList->evaluate(this->_exp);

	}
	else {
		warning("Error en tiempo de ejecución: la expresión a comprobar no es numérica ", "segun");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::StatementList::addStatement(lp::Statement * stmt) {
	this->_stmts.push_back(stmt);
}

void lp::StatementList::print() {
	std::list<Statement *>::iterator stmtIter;

	std::cout << "BlockStmt: "  << std::endl;

	for (stmtIter = this->_stmts.begin(); stmtIter != this->_stmts.end(); stmtIter++) {
	    (*stmtIter)->print();
	}
}

void lp::StatementList::evaluate() {
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts.begin(); stmtIter != this->_stmts.end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


std::string lp::UnaryNode::getId(){
	return this->_id;
}

bool lp::UnaryNode::beforeVariable(){
	return this->_before;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::Case::print() {
	std::cout << "Case: " << std::endl;
	if(this->_value != NULL) {
		std::cout << "value: " << std::endl;
		this->_value->print();
	}
	std::cout << "stmts: " << std::endl;
	this->_stmts->print();
	std::cout << "breakOpt: " << this->_breakOpt << std::endl;
	std::cout << "default case: " << this->_def << std::endl;
}

void lp::Case::evaluate() {
	this->_stmts->evaluate();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusPlusNode::print() 
{
  // Get the identifier in the table of symbols as Constant
  lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

  std::cout << "UnaryPlusPlusNode: "  << std::endl;
  std::cout << "++";
  std::cout << "VariableNode: " << this->_id << std::endl;
  std::cout << "Type: " << var->getType() << std::endl;
}

void lp::UnaryPlusPlusNode::evaluate()
{
	// Get the identifier in the table of symbols as Constant
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Ckeck the type of the expression
	if (var->getType() == NUMBER)
	{
		lp::NumericVariable *varNum = (lp::NumericVariable *) var;
		varNum->setValue(varNum->getValue() + 1);
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ","Más Más Unario");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusMinusNode::print() 
{
  // Get the identifier in the table of symbols as Constant
  lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

  std::cout << "UnaryMinusMinusNode: "  << std::endl;
  std::cout << "--";
  std::cout << "VariableNode: " << this->_id << std::endl;
  std::cout << "Type: " << var->getType() << std::endl;
}

void lp::UnaryMinusMinusNode::evaluate()
{
	// Get the identifier in the table of symbols as Constant
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Ckeck the type of the expression
	if (var->getType() == NUMBER)
	{
		lp::NumericVariable *varNum = (lp::NumericVariable *) var;
		varNum->setValue(varNum->getValue() - 1);
	}
	else
	{
		warning("Error en tiempo de ejecución: las expresiones no son numéricas para ","Menos Menos Unario");
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::CaseList::addCase(lp::Case * caseElement) {
	this->_caseList.push_back(caseElement);
}

void lp::CaseList::print() {
std::cout << "Tamaño de la lista: " << this->_caseList.size() << std::endl;
	std::list<Case *>::iterator caseIter;

	std::cout << "CaseList: "  << std::endl;

	for (caseIter = this->_caseList.begin(); caseIter != this->_caseList.end(); caseIter++) {
	    (*caseIter)->print();
	}
}

void lp::CaseList::evaluate(ExpNode * var) {
	std::list<Case *>::iterator caseIter;
	bool brk = false, switched = false;

	for (caseIter = this->_caseList.begin();
		caseIter != this->_caseList.end() && !brk;
		caseIter++) 
	{

		if(!(*caseIter)->isDefaultCase() && var->getType() != (*caseIter)->getType()) {
			warning("Error en tiempo de ejecución: la variable que se evalúa no es del mismo tipo que el valor. El comportamiento no está definido ", "segun");
		}

		if(var->getType() == NUMBER) {

			if(!((*caseIter)->isDefaultCase()) &&
				(std::abs(var->evaluateNumber() - (*caseIter)->getNumValue()) < ERROR_BOUND || switched)) {

				(*caseIter)->evaluate();
				brk = (*caseIter)->getBreakOpt();
				switched = !brk;
			}
			else if((*caseIter)->isDefaultCase()) {
				(*caseIter)->evaluate();
			}
		}
		else if(var->getType() == STRING) {

			if(!((*caseIter)->isDefaultCase()) &&
				(var->evaluateString().compare((*caseIter)->getStrValue()) == 0 || switched)) {

				(*caseIter)->evaluate();
				brk = (*caseIter)->getBreakOpt();
				switched = !brk;
			}
			else if((*caseIter)->isDefaultCase()) {
				(*caseIter)->evaluate();
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17
/*
void lp::BlockStmt::print() 
{
  std::list<Statement *>::iterator stmtIter;

  std::cout << "BlockStmt: "  << std::endl;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
     (*stmtIter)->print();
  }
}


void lp::BlockStmt::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}
*/




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print() {
  this->_stmts->print();
}



void lp::AST::evaluate() {
  this->_stmts->evaluate();
}

