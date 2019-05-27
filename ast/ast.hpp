/*!	
	\file    ast.hpp
	\brief   Declaration of AST class
	\author  
	\date    2018-12-13
	\version 1.0
*/

#ifndef _AST_HPP_
#define _AST_HPP_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <string>
#include <list>


#define ERROR_BOUND 1.0e-6  //! Error bound for the comparison of real numbers.
/*
#define NUMBER 1
#define BOOL 2
*/



namespace lp
{
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*!	
  \class   ExpNode
  \brief   Definition of atributes and methods of ExpNode class
  \warning Abstract class
*/
 class ExpNode 
{
  public:
	/*!	
		\brief   Type of  the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  int
		\sa		 print
	*/
    virtual int getType() = 0;


	/*!	
		\brief   Print the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		 evaluate()
	*/
    virtual void print() = 0;

	/*!	
		\brief   Evaluate the expression as NUMBER
		\warning Virtual function: could be redefined in the heir classes
		\return  double
		\sa		 print
	*/
    virtual double evaluateNumber()
	{
		return 0.0;
	}		


	/*!	
		\brief   Evaluate the expression as BOOL
		\warning Virtual function: could be redefined in the heir classes
		\return  bool
		\sa		 print
	*/
    virtual bool evaluateBool()
	{
		return false;
	}

	/*!	
		\brief   Evaluate the expression as STRING
		\warning Virtual function: could be redefined in the heir classes
		\return  bool
		\sa		 print
	*/
    virtual std::string evaluateString()
	{
		return "";
	}

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class VariableNode
  \brief Definition of atributes and methods of VariableNode class
  \note  VariableNode Class publicly inherits from ExpNode class
*/
class VariableNode : public ExpNode 
{
	private:
	  std::string _id; //!< Name of the VariableNode

	public:

	/*!		
		\brief Constructor of VariableNode
		\param value: double
		\post  A new NumericVariableNode is created with the name of the parameter
		\note  Inline function
	*/
	  VariableNode(std::string const & value)
		{
			this->_id = value; 
		}

	/*!	
		\brief   Type of the Variable
		\return  int
		\sa		 print
	*/
	 int getType();

	/*!
		\brief   Print the Variable
		\return  void
		\sa		 evaluate()
	*/
	  void print();

	/*!	
		\brief   Evaluate the Variable as NUMBER
		\return  double
		\sa		 print
	*/
	  double evaluateNumber();

	/*!	
		\brief   Evaluate the Variable as BOOL
		\return  bool
		\sa		 print
	*/
	  bool evaluateBool();

	  /*!	
		\brief   Evaluate the Variable as STRING
		\return  bool
		\sa		 print
	*/
	  std::string evaluateString();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class ConstantNode
  \brief Definition of atributes and methods of ConstantNode class
  \note  ConstantNode Class publicly inherits from ExpNode class
*/
class ConstantNode : public ExpNode 
{
	private:
	  std::string _id; //!< Name of the ConstantNode

	public:

	/*!		
		\brief Constructor of ConstantNode
		\param value: double
		\post  A new ConstantNode is created with the name of the parameter
	*/
	  ConstantNode(std::string value)
		{
			this->_id = value; 
		}

	/*!	
		\brief   Type of the Constant
		\return  int
		\sa		 print
	*/
	 int getType();

	/*!
		\brief   Print the Constant
		\return  void
		\sa		 evaluate()
	*/
	  void print();

	/*!	
		\brief   Evaluate the Constant as NUMBER
		\return  double
		\sa		 print
	*/
	  double evaluateNumber();

	/*!	
		\brief   Evaluate the Constant as BOOL
		\return  bool
		\sa		 print
	*/
	  bool evaluateBool();
};





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumberNode
  \brief Definition of atributes and methods of NumberNode class
  \note  NumberNode Class publicly inherits from ExpNode class
*/
class NumberNode : public ExpNode 
{
 private: 	
   double _number; //!< \brief number of the NumberNode
 
 public:

/*!		
	\brief Constructor of NumberNode
	\param value: double
	\post  A new NumberNode is created with the value of the parameter
	\note  Inline function
*/
  NumberNode(double value)
	{
	    this->_number = value;
	}

	/*!	
	\brief   Get the type of the expression: NUMBER
	\return  int
	\sa		 print
	*/
	int getType();

	/*!
		\brief   Print the expression
		\return  void
		\sa		 evaluate()
	*/
	void print();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		 print
	*/
	double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class StringNode
  \brief Definition of atributes and methods of StringNode class
  \note  StringNode Class publicly inherits from ExpNode class
*/
class StringNode : public ExpNode 
{
 private: 	
   std::string _string; //!< \brief string of the StringNode
 
 public:

	/*!		
		\brief Constructor of NumberNode
		\param value: double
		\post  A new NumberNode is created with the value of the parameter
		\note  Inline function
	*/
  	StringNode(const std::string & value)
	{
	    this->_string = value;
	};

	/*!	
	\brief   Get the type of the expression: STRING
	\return  int
	\sa		 print
	*/
	int getType();

	/*!
		\brief   Print the expression
		\return  void
		\sa		 evaluate()
	*/
	void print();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		 print
	*/
	std::string evaluateString();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from ExpNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class UnaryOperatorNode : public ExpNode 
{
 protected:
  ExpNode *_exp;  //!< Child expression

 public:

/*!		
	\brief Constructor of UnaryOperatorNode links the node to it child,
           and stores the character representation of the operator.
	\param expression: pointer to ExpNode
	\post  A new OperatorNode is created with the parameters
	\note  Inline function
*/
  UnaryOperatorNode(ExpNode *expression)
	{
		this->_exp = expression;
	}

	/*!	
	\brief   Get the type of the child expression
	\return  int
	\sa		 print
	*/
	inline int getType()
	{
		return this->_exp->getType();
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericUnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from UnaryOperatorNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class NumericUnaryOperatorNode : public UnaryOperatorNode 
{
 public:

/*!		
	\brief Constructor of NumericUnaryOperatorNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new NumericUnaryOperatorNode is created with the parameters
	\note  Inline function
*/
  NumericUnaryOperatorNode(ExpNode *expression): UnaryOperatorNode(expression)
	{
		// Empty
	}

	/*!	
	\brief   Get the type of the child expression
	\return  int
	\sa		 print
	*/
	int getType();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicalUnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from UnaryOperatorNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class LogicalUnaryOperatorNode : public UnaryOperatorNode 
{
 public:

/*!		
	\brief Constructor of LogicalUnaryOperatorNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new NumericUnaryOperatorNode is created with the parameters
	\note  Inline function
*/
  LogicalUnaryOperatorNode(ExpNode *expression): UnaryOperatorNode(expression)
	{
		// Empty
	}

	/*!	
	\brief   Get the type of the child expression
	\return  int
	\sa		 print
	*/
	int getType();

};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryMinusNode
  \brief   Definition of atributes and methods of UnaryMinusNode class
  \note    UnaryMinusNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryMinusNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryMinusNode uses NumericUnaryOperatorNode's constructor as member initializer.
	\param expression: pointer to ExpNode
	\post  A new UnaryMinusNode is created with the parameter
	\note  Inline function: the NumericUnaryOperatorNode's constructor is used ad member initializer
*/
  UnaryMinusNode(ExpNode *expression): NumericUnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryPlusNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    UnaryPlusNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryPlusNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryPlusNode uses NumericUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryPlusNode is created with the parameter
*/
  UnaryPlusNode(ExpNode *expression): NumericUnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   OperatorNode
  \brief   Definition of atributes and methods of OperatorNode class
  \note    OperatorNode Class publicly inherits from ExpNode class
  \warning Abstract class, because it does not redefine the print and getType methods of ExpNode
*/
class OperatorNode : public ExpNode 
{
	protected:
		ExpNode *_left;    //!< Left expression
		ExpNode *_right;   //!< Right expression

	public:
	/*!		
		\brief Constructor of OperatorNode links the node to its children,
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new OperatorNode is created with the parameters
	*/
    OperatorNode(ExpNode *L, ExpNode *R)
	{
	    this->_left  = L;
    	this->_right = R;
	}

};



//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericOperatorNode
  \brief   Definition of atributes and methods of NumericOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class NumericOperatorNode : public OperatorNode 
{
	public:

	/*!		
		\brief Constructor of NumericOperatorNode uses OperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NumericOperatorNode is created with the parameters
	*/
    NumericOperatorNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
	{
		//	Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	\sa		 print()
	*/
	int getType();
};



//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   RelationalOperatorNode
  \brief   Definition of atributes and methods of RelationalOperatorNode class
  \note    RelationalOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class RelationalOperatorNode : public OperatorNode 
{
public:
/*!		
	\brief Constructor of RelationalOperatorNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new RelationalOperatorNode is created with the parameters
*/
    RelationalOperatorNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
	{
		//	Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	\sa		 print()
	*/
	int getType();

};


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicalOperatorNode
  \brief   Definition of atributes and methods of LogicalOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class LogicalOperatorNode : public OperatorNode 
{
	public:

	/*!		
		\brief Constructor of LogicalOperatorNode uses OperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NumericOperatorNode is created with the parameters
	*/
    LogicalOperatorNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
	{
		//	Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	\sa		 print()
	*/
	int getType();
};


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   StringOperatorNode
  \brief   Definition of atributes and methods of StringOperatorNode class
  \note    StringOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the print method of ExpNode
*/
class StringOperatorNode : public OperatorNode 
{
	public:

	/*!		
		\brief Constructor of StringOperatorNode uses OperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new StringOperatorNode is created with the parameters
	*/
    StringOperatorNode(ExpNode *L, ExpNode *R): OperatorNode(L,R) 
	{
		//	Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	\sa		 print()
	*/
	int getType();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusNode
  \brief   Definition of atributes and methods of PlusNode class
  \note    PlusNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class PlusNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of PlusNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new PlusNode is created with the parameter
*/
  PlusNode(ExpNode *L, ExpNode *R) : NumericOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the PlusNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the PlusNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   MinusNode
  \brief   Definition of atributes and methods of MinusNode class
  \note    MinusNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class MinusNode : public NumericOperatorNode 
{
  public:

/*!		
	\brief Constructor of MinusNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new MinusNode is created with the parameter
*/
  MinusNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the MinusNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the MinusNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MultiplicationNode
  \brief   Definition of atributes and methods of MultiplicationNode class
  \note    MultiplicationNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class MultiplicationNode : public NumericOperatorNode 
{
  public:

/*!		
	\brief Constructor of MultiplicationNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new MultiplicationNode is created with the parameter
*/
  MultiplicationNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the MultiplicationNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the MultiplicationNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DivisionNode
  \brief   Definition of atributes and methods of DivisionNode class
  \note    DivisionNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class DivisionNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of DivisionNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new DivisionNode is created with the parameter
*/
  DivisionNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the DivisionNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the DivisionNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};

/*!	
  \class   IntegerDivisionNode
  \brief   Definition of atributes and methods of IntegerDivisionNode class
  \note    IntegerDivisionNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class IntegerDivisionNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of DivisionNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new DivisionNode is created with the parameter
*/
  IntegerDivisionNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the DivisionNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the DivisionNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ModuloNode
  \brief   Definition of atributes and methods of ModuloNode class
  \note    ModuloNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class ModuloNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of ModuloNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new ModuloNode is created with the parameter
*/
  ModuloNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the ModuloNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the ModuloNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PowerNode
  \brief   Definition of atributes and methods of PowerNode class
  \note    PowerNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own print and evaluate functions
*/
class PowerNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of PowerNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new PowerNode is created with the parameter
*/
  PowerNode(ExpNode *L, ExpNode *R): NumericOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the PowerNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the PowerNode
	\return  double
	\sa		 print
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ConcatenateNode
  \brief   Definition of atributes and methods of ConcatenateNode class
  \note    ConcatenateNode Class publicly inherits from StringOperatorNode class 
		   and adds its own print and evaluate functions
*/
class ConcatenateNode : public StringOperatorNode
{
  public:
/*!		
	\brief Constructor of ConcatenateNode uses StringOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new ConcatenateNode is created with the parameter
*/
  ConcatenateNode(ExpNode *L, ExpNode *R) : StringOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the ConcatenateNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the ConcatenateNode
	\return  string
	\sa		 print
*/
  std::string evaluateString();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode
  \brief   Definition of atributes and methods of BuiltinFunctionNode class
  \note    BuiltinFunctionNode Class publicly inherits from ExpNode class 
*/
class BuiltinFunctionNode : public ExpNode 
{
  protected: 
	std::string _id; //!< Name of the BuiltinFunctionNode
	
  public:
/*!		
	\brief Constructor of BuiltinFunctionNode
	\param id: string, name of the BuiltinFunction
	\post  A new BuiltinFunctionNode is created with the parameter
*/
  BuiltinFunctionNode(std::string id)
	{
		this->_id = id;
	}

};




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_0
  \brief   Definition of atributes and methods of BuiltinFunctionNode_0 class
  \note    BuiltinFunctionNode_0 Class publicly inherits from BuiltinFunctionNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_0 : public BuiltinFunctionNode 
{
  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_0 uses BuiltinFunctionNode's constructor as member initializer
	\param id: string, name of the BuiltinFunction
	\post  A new BuiltinFunctionNode_2 is created with the parameter
*/
  BuiltinFunctionNode_0(std::string id): BuiltinFunctionNode(id)
	{
		// 
	}

	/*!	
		\brief   Get the type of the child expression:
		\return  int
		\sa		 print
	*/
	int getType();



	/*!
		\brief   Print the BuiltinFunctionNode_0
		\return  void
		\sa		 evaluate()
	*/
	  void print();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_0
		\return  double
		\sa		 print
	*/
	  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_1
  \brief   Definition of atributes and methods of BuiltinFunctionNode_1 class
  \note    BuiltinFunctionNode_1 Class publicly inherits from BuiltinFunctionNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_1: public BuiltinFunctionNode 
{
  private:
	ExpNode *_exp;  //!< Argument of the BuiltinFunctionNode_1

  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_1 uses BuiltinFunctionNode's constructor as member initializer
	\param id: string, name of the BuiltinFunction
	\param expression: pointer to ExpNode, argument of the BuiltinFunctionNode_1
	\post  A new BuiltinFunctionNode_1 is created with the parameters
*/
  BuiltinFunctionNode_1(std::string id, ExpNode *expression): BuiltinFunctionNode(id)
	{
		this->_exp = expression;
	}

	/*!	
		\brief   Get the type of the child expression:
		\return  int
		\sa		 print
	*/
	int getType();

	/*!
		\brief   Print the BuiltinFunctionNode_1
		\return  void
		\sa		 evaluate()
	*/
	  void print();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_1
		\return  double
		\sa		 print
	*/
	  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_2
  \brief   Definition of atributes and methods of BuiltinFunctionNode_2 class 
  \note    BuiltinFunctionNode_2 Class publicly inherits from BuiltinFunctionNode class 
		   and adds its own print and evaluate functions
*/
class BuiltinFunctionNode_2 : public BuiltinFunctionNode 
{
	private:
		ExpNode *_exp1; //!< First argument of the BuiltinFunction_2
		ExpNode *_exp2; //!< Second argument of the BuiltinFunction_2

	public:
	/*!		
		\brief Constructor of BuiltinFunctionNode_2 uses BuiltinFunctionNode's constructor as member initializer
		\param id: string, name of the BuiltinFunction_2
		\param expression1: pointer to ExpNode, first argument of the BuiltinFunctionNode
		\param expression2: pointer to ExpNode, second argument of the BuiltinFunctionNode
		\post  A new BuiltinFunctionNode_2 is created with the parameters
	*/
	  BuiltinFunctionNode_2(std::string id,ExpNode *expression1,ExpNode *expression2): BuiltinFunctionNode(id)
	{
		this->_exp1 = expression1;
		this->_exp2 = expression2;
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	\sa		 print
	*/
	int getType();



	/*!
		\brief   Print the BuiltinFunctionNode_2
		\return  void
		\sa		 evaluate()
	*/
	  void print();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_2
		\return  double
		\sa		 print
	*/
	  double evaluateNumber();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterThanNode
  \brief   Definition of atributes and methods of GreaterThanNode class
  \note    GreaterThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class GreaterThanNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of GreaterThanNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new GreaterThanNode is created with the parameter
*/
  GreaterThanNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) 
  {
		// Empty
  }


/*!
	\brief   Print the GreaterThanNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the GreaterThanNode
	\return  bool
	\sa		 print
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterOrEqualNode
  \brief   Definition of atributes and methods of GreaterOrEqualNode class
  \note    GreaterOrEqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class GreaterOrEqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of GreaterOrEqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new GreaterOrEqualNode is created with the parameter
*/
  GreaterOrEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the GreaterOrEqualNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the GreaterOrEqualNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessThanNode
  \brief   Definition of atributes and methods of LessThanNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class LessThanNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of LessThanNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new LessThanNode is created with the parameter
*/
  LessThanNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the LessThanNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the LessThanNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessOrEqualNode
  \brief   Definition of atributes and methods of LessOrEqualNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class LessOrEqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of LessOrEqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new LessOrEqualNode is created with the parameter
*/
  LessOrEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the LessOrEqualNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the LessOrEqualNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EqualNode
  \brief   Definition of atributes and methods of EqualNode class
  \note    EqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class EqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of EqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new EqualNode is created with the parameter
*/
  EqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) 
  {
		// Empty
  }
/*!
	\brief   Print the EqualNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the EqualNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   NotEqualNode
  \brief   Definition of atributes and methods of NotEqualNode class
  \note    NotEqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class NotEqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of NotEqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new NotEqualNode is created with the parameter
*/
  NotEqualNode(ExpNode *L, ExpNode *R): RelationalOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the NotEqualNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the NotEqualNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AndNode
  \brief   Definition of atributes and methods of AndNode class
  \note    AndNode Class publicly inherits from LogicalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class AndNode : public LogicalOperatorNode 
{
  public:

/*!		
	\brief Constructor of AndNode uses LogicalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new AndNode is created with the parameter
*/
  AndNode(ExpNode *L, ExpNode *R): LogicalOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the AndNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the AndNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   OrNode
  \brief   Definition of atributes and methods of OrNode class
  \note    OrNode Class publicly inherits from LogicalOperatorNode class 
		   and adds its own print and evaluate functions
*/
class OrNode : public LogicalOperatorNode 
{
  public:

/*!		
	\brief Constructor of AndNode uses LogicalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new AndNode is created with the parameter
*/
  OrNode(ExpNode *L, ExpNode *R): LogicalOperatorNode(L,R) 
  {
		// Empty
  }

/*!
	\brief   Print the OrNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the OrNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NotNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    NotNode Class publicly inherits from LogicalUnaryOperatorNode class
*/
class NotNode : public LogicalUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of NotNode uses LogicalUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new NotNode is created with the parameter
*/
  NotNode(ExpNode *expression): LogicalUnaryOperatorNode(expression) 
	{
		// empty
	} 

/*!
	\brief   Print the NotNode
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the NotNode
	\return  bool
	\sa		 print()
*/
  bool evaluateBool();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   Statement
  \brief   Definition of atributes and methods of Statement class
  \warning Abstract class
*/

class Statement {
 public:

/*!	
	\brief   Print the Statement
	\note    Virtual function: can be redefined in the heir classes
	\return  double
	\sa		 print
*/

  virtual void print() {}

/*!	
	\brief   Evaluate the Statement
	\warning Pure virtual function: must be redefined in the heir classes
	\return  double
	\sa		 print
*/
  virtual void evaluate() = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   StatementList
  \brief   Definition of atributes and methods of StatementList class
*/
class StatementList {

private:
	//! List with all the statements
 	std::list<lp::Statement *> _stmts;

public:

/*!
	\brief Class constructor
*/
StatementList() {
	//Empty 
}

/*!
	\brief Adds a statement to the list
	\return void
*/
void addStatement(lp::Statement * stmt);

/*!	
	\brief   Print the StatementList
	\return  void
	\sa		 evaluate
*/

void print();

/*!	
	\brief   Evaluate the StatementList
	\return  void
	\sa		 print
*/
void evaluate();
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryNode
  \brief   Definition of atributes and methods of UnaryNode class
  \note    UnaryNode Class publicly inherits from Statement class
  \warning Abstract class, because it does not redefine the print method of Statement
*/
class UnaryNode : public Statement
{
 protected:
  	  std::string _id; //!< VariableNode
  	  bool _before; //!< Unary is before the variable

 public:

/*!		
	\brief Constructor of UnaryNode
	\param id: string, variable name
	\param before: bool, unary operator position
	\note  Inline function
*/
  UnaryNode(std::string id, bool before)
	{
		this->_id = id;
		this->_before = before;
	}

/*!
	\brief   Return the variable id
	\return  string
*/
 std::string getId();

 /*!
	\brief   Determine if the unary operator is before the variable or not
	\return  bool
*/
 bool beforeVariable();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryPlusPlusNode
  \brief   Definition of atributes and methods of UnaryPlusPlusNode class
  \note    UnaryPlusPlusNode Class publicly inherits from UnaryNode class
*/
class UnaryPlusPlusNode : public UnaryNode
{

 public:

/*!		
	\brief Constructor of UnaryPlusPlusNode uses UnaryNode's constructor as member initializer
	\param id: string, variable name
	\param before: bool, unary operator position
	\post  A new UnaryPlusPlusNode is created with the parameters
*/
  UnaryPlusPlusNode(std::string id, bool before) : UnaryNode(id, before)
	{
		//empty
	}

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate()
*/
  void print();
  

/*!	
	\brief   Evaluate the expression
	\sa		 print
*/
  void evaluate();
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryMinusMinusNode
  \brief   Definition of atributes and methods of UnaryMinusMinusNode class
  \note    UnaryMinusMinusNode Class publicly inherits from UnaryNode class
*/
class UnaryMinusMinusNode : public UnaryNode
{

 public:

/*!		
	\brief Constructor of UnaryMinusMinusNode uses UnaryNode's constructor as member initializer
	\param id: string, variable name
	\param before: bool, unary operator position
	\post  A new UnaryMinusMinusNode is created with the parameters
*/
  UnaryMinusMinusNode(std::string id, bool before) : UnaryNode(id, before)
	{
		//empty
	}

/*!
	\brief   Print the expression
	\return  void
	\sa		 evaluate()
*/
  void print();
  

/*!	
	\brief   Evaluate the expression
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   Case
  \brief   Definition of atributes and methods of Case class
*/
class Case : public Statement {

private:
	ExpNode * _value; //!< Case value
	StatementList * _stmts; //!< Statements of the body of the case
	bool _breakOpt; //!< Wether the case has a break option or not
	bool _def; //!< Wether it is the default case or not

public:

	/*!		
	\brief Constructor of Case 
	\param value: int *, value of the Case
	\param stmts: body of the Case
	\param breakOpt: Wether the case has a break option or not
	\param def: Wether the case is default or not
	\post  A new Case is created with the parameters
*/
	Case(StatementList * stmts, ExpNode * value = NULL, bool breakOpt = false, bool def = NULL) {
		this->_value = value;
		this->_stmts = stmts;
		this->_breakOpt = breakOpt;
		this->_def = def;
	}

	/*!	
		\brief   Gets the type of the Case
		\return  int
		\note 	 inline function
	*/
	inline int getType() const {
		return this->_value->getType();
	}

	/*!	
		\brief   Gets the value of the Case
		\return  double
		\note 	 inline function
	*/
	inline double getNumValue() const {
		return this->_value->evaluateNumber();
	}

	/*!	
		\brief   Gets the value of the Case
		\return  string
		\note 	 inline function
	*/
	inline std::string getStrValue() const {
		return this->_value->evaluateString();
	}

	/*!	
		\brief   Gets the break option of the Case
		\return  bool
		\note 	 inline function
	*/
	inline bool getBreakOpt() const {
		return this->_breakOpt;
	}

	/*!	
		\brief   Tells if it is de default case or not
		\return  bool
		\note 	 inline function
	*/
	inline bool isDefaultCase() const {
		return this->_def;
	}

	/*!	
		\brief   Print the Case
		\return  void
		\sa		 evaluate
	*/

	void print();

	/*!	
		\brief   Evaluate the Case
		\return  void
		\sa		 print
	*/
	void evaluate();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   CaseList
  \brief   Definition of atributes and methods of CaseList class
*/
class CaseList {

private:
	std::list<lp::Case *> _caseList; //!< List of cases

public:

	/*!
		\brief Class constructor
	*/
	CaseList() {
		//Empty 
	}

	/*!
		\brief Adds a case to the list
		\return void
	*/
	void addCase(lp::Case * caseElement);

	/*!	
		\brief   Print the CaseList
		\return  void
		\sa		 evaluate
	*/

	void print();

	/*!	
		\brief   Evaluate the CaseList
		\param 	 var: ExpNode, value of the variable to be evaluated
		\return  void
		\sa		 print
	*/
	void evaluate(ExpNode * var);
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class Assignment
  \brief Definition of atributes and methods of Assignment class
  \note  Assignment Class publicly inherits from Statement class
  \note Abstract class
*/
class Assignment : public Statement {

protected:
	std::string _id;    //!< Name of the variable of the assignment statement
	ExpNode *_exp; 	 //!< Expresssion the assignment statement
	Assignment *_asgn;  //!< Allow multiple assigment -> a = b = 2
  	UnaryNode *_unaryNode; //!< Allow unary operators assigments -> a = ++b; a = b++; a = --b; a = b--;

public:

	/*!		
	\brief Constructor of Assignment 
	\param id: string, variable of the Assignment
	\param expression: pointer to ExpNode
	\post  A new Assignment is created with the parameters
*/
	Assignment(std::string id, ExpNode *expression): _id(id), _exp(expression)
	{
		this->_asgn = NULL;
		this->_unaryNode = NULL;
	}

	/*!		
	\brief Constructor of Assignment 
	\param id: string, variable of the Assignment
	\param asgn: pointer to Assignment
	\post  A new Assignment is created with the parameters
*/
	Assignment(std::string id, Assignment *asgn): _id(id), _asgn(asgn)
	{
		this->_exp = NULL;
		this->_unaryNode = NULL;
	}

/*!		
	\brief Constructor of Assignment 
	\param id: string, variable of the Assignment
	\param unaryNode: pointer to UnaryNode
	\post  A new Assignment is created with the parameters
*/
  Assignment(std::string id, UnaryNode *unaryNode): _id(id), _unaryNode(unaryNode)
	{
		this->_exp = NULL;
		this->_asgn = NULL;
	}


	/*!
	\brief Getter for the ID
	\note inline function
	*/
	inline std::string getId() const {
		return this->_id;
	} 

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class PlusAssignmentStmt;
class MinusAssignmentStmt;

/*!	
  \class   AssignmentStmt
  \brief   Definition of atributes and methods of AssignmentStmt class
  \note    AssignmentStmt Class publicly inherits from Assignment class 
		   and adds its own print and evaluate functions
*/
class AssignmentStmt : public Assignment
{

 public:

/*!		
	\brief Constructor of AssignmentStmt 
	\param id: string, variable of the AssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new AssignmentStmt is created with the parameters
*/
  AssignmentStmt(std::string id, ExpNode *expression) : Assignment(id, expression)
	{
		//Empty
	}

/*!		
	\brief Constructor of AssignmentStmt 
	\param id: string, variable of the AssignmentStmt
	\param asgn: pointer to Assignment
	\post  A new AssignmentStmt is created with the parameters
	\note  Allow multiple assigment -> a = b = 2 
*/

  AssignmentStmt(std::string id, Assignment *asgn) : Assignment(id, asgn)
	{
		//Empty
	}

/*!		
	\brief Constructor of AssignmentStmt 
	\param id: string, variable of the AssignmentStmt
	\param unaryNode: pointer to UnaryNode
	\post  A new AssignmentStmt is created with the parameters
*/
  AssignmentStmt(std::string id, UnaryNode *unaryNode): Assignment(id, unaryNode)
	{
		//Empty
	}


/*!
	\brief   Print the AssignmentStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the AssignmentStmt
	\return  void
	\sa		 print
*/
    void evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusAssignmentStmt
  \brief   Definition of atributes and methods of PlusAssignmentStmt class
  \note    PlusAssignmentStmt Class publicly inherits from Assignment class 
		   and adds its own print and evaluate functions
*/
class PlusAssignmentStmt : public Assignment
{

 public:

/*!		
	\brief Constructor of PlusAssignmentStmt 
	\param id: string, variable of the PlusAssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new PlusAssignmentStmt is created with the parameters
*/
  PlusAssignmentStmt(std::string id, ExpNode *expression) : Assignment(id, expression)
	{
		//Empty
	}

/*!		
	\brief Constructor of PlusAssignmentStmt 
	\param id: string, variable of the PlusAssignmentStmt
	\param asgn: pointer to AssignmentStmt
	\post  A new PlusAssignmentStmt is created with the parameters 
*/

  PlusAssignmentStmt(std::string id, Assignment *asgn) : Assignment(id, asgn)
	{
		//Empty
	}

/*!		
	\brief Constructor of PlusAssignmentStmt 
	\param id: string, variable of the PlusAssignmentStmt
	\param unaryNode: pointer to UnaryNode
	\post  A new PlusAssignmentStmt is created with the parameters
*/
  PlusAssignmentStmt(std::string id, UnaryNode *unaryNode): Assignment(id, unaryNode)
	{
		//Empty
	}

/*!
	\brief   Print the PlusAssignmentStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the PlusAssignmentStmt
	\return  void
	\sa		 print
*/
    void evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MinusAssignmentStmt
  \brief   Definition of atributes and methods of MinusAssignmentStmt class
  \note    MinusAssignmentStmt Class publicly inherits from Assignment class 
		   and adds its own print and evaluate functions
*/
class MinusAssignmentStmt : public Assignment
{

 public:

/*!		
	\brief Constructor of MinusAssignmentStmt 
	\param id: string, variable of the MinusAssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new MinusAssignmentStmt is created with the parameters
*/
  MinusAssignmentStmt(std::string id, ExpNode *expression) : Assignment(id, expression)
	{
		//Empty
	}

/*!		
	\brief Constructor of MinusAssignmentStmt 
	\param id: string, variable of the MinusAssignmentStmt
	\param asgn: pointer to Assignment
	\post  A new MinusAssignmentStmt is created with the parameters 
*/

  MinusAssignmentStmt(std::string id, Assignment *asgn) : Assignment(id, asgn)
	{
		//Empty
	}

	/*!		
	\brief Constructor of MinusAssignmentStmt 
	\param id: string, variable of the MinusAssignmentStmt
	\param unaryNode: pointer to UnaryNode
	\post  A new MinusAssignmentStmt is created with the parameters
*/
  MinusAssignmentStmt(std::string id, UnaryNode *unaryNode): Assignment(id, unaryNode)
	{
		//Empty
	}

/*!
	\brief   Print the MinusAssignmentStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the MinusAssignmentStmt
	\return  void
	\sa		 print
*/
    void evaluate();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ProductAssignmentStmt
  \brief   Definition of atributes and methods of ProductAssignmentStmt class
  \note    ProductAssignmentStmt Class publicly inherits from Assignment class 
		   and adds its own print and evaluate functions
*/
class ProductAssignmentStmt : public Assignment
{

 public:

/*!		
	\brief Constructor of ProductAssignmentStmt 
	\param id: string, variable of the ProductAssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new ProductAssignmentStmt is created with the parameters
*/
  ProductAssignmentStmt(std::string id, ExpNode *expression) : Assignment(id, expression)
	{
		//Empty
	}

/*!		
	\brief Constructor of ProductAssignmentStmt 
	\param id: string, variable of the ProductAssignmentStmt
	\param asgn: pointer to Assignment
	\post  A new ProductAssignmentStmt is created with the parameters 
*/

  ProductAssignmentStmt(std::string id, Assignment *asgn) : Assignment(id, asgn)
	{
		//Empty
	}

	/*!		
	\brief Constructor of ProductAssignmentStmt 
	\param id: string, variable of the ProductAssignmentStmt
	\param unaryNode: pointer to UnaryNode
	\post  A new ProductAssignmentStmt is created with the parameters
*/
  ProductAssignmentStmt(std::string id, UnaryNode *unaryNode): Assignment(id, unaryNode)
	{
		//Empty
	}

/*!
	\brief   Print the ProductAssignmentStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the ProductAssignmentStmt
	\return  void
	\sa		 print
*/
    void evaluate();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   DivisionAssignmentStmt
  \brief   Definition of atributes and methods of DivisionAssignmentStmt class
  \note    DivisionAssignmentStmt Class publicly inherits from Assignment class 
		   and adds its own print and evaluate functions
*/
class DivisionAssignmentStmt : public Assignment
{

 public:

/*!		
	\brief Constructor of DivisionAssignmentStmt 
	\param id: string, variable of the DivisionAssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new DivisionAssignmentStmt is created with the parameters
*/
  DivisionAssignmentStmt(std::string id, ExpNode *expression) : Assignment(id, expression)
	{
		//Empty
	}

/*!		
	\brief Constructor of DivisionAssignmentStmt 
	\param id: string, variable of the DivisionAssignmentStmt
	\param asgn: pointer to Assignment
	\post  A new DivisionAssignmentStmt is created with the parameters 
*/

  DivisionAssignmentStmt(std::string id, Assignment *asgn) : Assignment(id, asgn)
	{
		//Empty
	}

	/*!		
	\brief Constructor of DivisionAssignmentStmt 
	\param id: string, variable of the DivisionAssignmentStmt
	\param unaryNode: pointer to UnaryNode
	\post  A new DivisionAssignmentStmt is created with the parameters
*/
  DivisionAssignmentStmt(std::string id, UnaryNode *unaryNode): Assignment(id, unaryNode)
	{
		//Empty
	}

/*!
	\brief   Print the DivisionAssignmentStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the DivisionAssignmentStmt
	\return  void
	\sa		 print
*/
    void evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PrintStmt
  \brief   Definition of atributes and methods of PrintStmt class
  \note    PrintStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
  \warning  In this class, print and evaluate functions have the same meaning.
*/
class PrintStmt: public Statement
{
 private:
  ExpNode *_exp; //!< Expresssion the print statement

 public:
/*!		
	\brief Constructor of PrintStmt 
	\param expression: pointer to ExpNode
	\post  A new PrintStmt is created with the parameter
*/
  PrintStmt(ExpNode *expression)
	{
		this->_exp = expression;
	}

/*!
	\brief   Print the PrintStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the PrintStmt
	\return  double
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ReadStmt
  \brief   Definition of atributes and methods of ReadStmt class
  \note    ReadStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class ReadStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the ReadStmt
	

  public:
/*!		
	\brief Constructor of ReadStmt
	\param id: string, name of the variable of the ReadStmt
	\post  A new ReadStmt is created with the parameter
*/
  ReadStmt(std::string id)
	{
		this->_id = id;
	}

/*!
	\brief   Print the ReadStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the ReadStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ReadStringStmt
  \brief   Definition of atributes and methods of ReadStringStmt class
  \note    ReadStringStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class ReadStringStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the ReadStmt
	

  public:
/*!		
	\brief Constructor of ReadStmt
	\param id: string, name of the variable of the ReadStmt
	\post  A new ReadStmt is created with the parameter
*/
  ReadStringStmt(std::string id)
	{
		this->_id = id;
	}

/*!
	\brief   Print the ReadStringStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the ReadStringStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EraseStmt
  \brief   Definition of atributes and methods of EraseStmt class
  \note    EraseStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class EraseStmt : public Statement 
{	

  public:
/*!		
	\brief Constructor of EraseStmt
	\post  A new EraseStmt is created with the parameter
*/
  EraseStmt()
	{
		//Empty
	}

/*!
	\brief   Print the EraseStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the EraseStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PositionStmt
  \brief   Definition of atributes and methods of PositionStmt class
  \note    PositionStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class PositionStmt : public Statement 
{
  private:
	ExpNode * _x; //!< X coordinate
	ExpNode * _y; //!< Y coordinate

  public:
/*!		
	\brief Constructor of PositionStmt
	\param x: ExpNode*, x coordinate
	\param y: ExpNode*, y coordinate
	\post  A new PositionStmt is created with the parameter
*/
  PositionStmt(ExpNode * x, ExpNode * y)
	{
		this->_x = x;
		this->_y = y;
	}

/*!
	\brief   Print the PositionStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the PositionStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EmptyStmt
  \brief   Definition of atributes and methods of EmptyStmt class
  \note    EmptyStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class EmptyStmt : public Statement
{
  // No attributes

  public:
/*!		
	\brief Constructor of  EmptyStmt
	\post  A new EmptyStmt is created 
*/
  EmptyStmt()
	{
		// Empty
	}


/*!
	\brief   Print the EmptyStmt
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   Evaluate the EmptyStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

/*!	
  \class   IfStmt
  \brief   Definition of atributes and methods of IfStmt class
  \note    IfStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class IfStmt : public Statement 
{
 private:
  ExpNode *_cond; //!< Condicion of the if statement
  StatementList *_consequent; //!< Statements of the consequent
  StatementList *_alternative; //!< Statements of the alternative

  public:
/*!		
	\brief Constructor of Single IfStmt (without alternative)
	\param condition: ExpNode of the condition
	\param consequent: Statements of the consequent
	\post  A new IfStmt is created with the parameters
*/
  IfStmt(ExpNode *condition, StatementList *consequent)
	{
		this->_cond = condition;
		this->_consequent = consequent;
		this->_alternative = NULL;
	}


/*!		
	\brief Constructor of Compound IfStmt (with alternative)
	\param condition: ExpNode of the condition
	\param consequent: Statements of the consequent
	\param alternative: Statements of the alternative
	\post  A new IfStmt is created with the parameters
*/
  IfStmt(ExpNode *condition, StatementList *consequent, StatementList *alternative)
	{
		this->_cond = condition;
		this->_consequent = consequent;
		this->_alternative = alternative;
	}


/*!
	\brief   Print the IfStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the IfStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};





///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17

/*!	
  \class   WhileStmt
  \brief   Definition of atributes and methods of WhileStmt class
  \note    WhileStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/
class WhileStmt : public Statement 
{
 private:
  ExpNode *_cond; //!< Condicion of the while statement
  StatementList *_stmts; //!< Statements of the body of the while loop

  public:
/*!		
	\brief Constructor of  WhileStmt
	\param condition: ExpNode of the condition
	\param statements: Statement of the body of the loop 
	\post  A new WhileStmt is created with the parameters
*/
  WhileStmt(ExpNode *condition, StatementList *statements)
	{
		this->_cond = condition;
		this->_stmts = statements;
	}


/*!
	\brief   Print the WhileStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the WhileStmt
	\return  void
	\sa		 print
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   RepeatUntilStmt
  \brief   Definition of atributes and methods of RepeatUntilStmt class
  \note    RepeatUntilStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/

class RepeatUntilStmt : public Statement {

private:
	ExpNode * _cond; //!< Condicion of the do-until statement
	StatementList * _stmts; //!< Statements of the body of the do-until loop

public:

	/*!		
	\brief Constructor of  RepeatUntilStmt
	\param statements: Statement of the body of the loop 
	\param condition: ExpNode of the condition
	\post  A new RepeatUntilStmt is created with the parameters
*/
  RepeatUntilStmt(StatementList *statements, ExpNode *condition)
	{
		this->_stmts = statements;
		this->_cond = condition;
	}


/*!
	\brief   Print the RepeatUntilStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the RepeatUntilStmt
	\return  void
	\sa		 print
*/
  void evaluate();

};

/*!	
  \class   ForStmt
  \brief   Definition of atributes and methods of ForStmt class
  \note    ForStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
*/

class ForStmt : public Statement {

private:
	std::string _var; //!< Variable for the for loop
	ExpNode * _start; //!< Start value for variable
	ExpNode * _end; //!< End of the for statement
	ExpNode * _inc; //!< Increment value of the for statement
	StatementList * _stmts; //!< Statements of the body of the for loop

public:

	/*!		
	\brief Constructor of  ForStmt
	\param var: string of the variable
	\param start: ExpNode of the start of the loop 
	\param end: ExpNode of the end of the loop
	\param inc: ExpNode of the increment of the loop
	\param statements: StatementList of the body of the loop
	\post  A new ForStmt is created with the parameters
*/
	ForStmt(std::string var, ExpNode * start, ExpNode * end, ExpNode * inc, StatementList * statements)
	{
		this->_var = var;
		this->_start = start;
		this->_end = end;
		this->_inc = inc;
		this->_stmts = statements;
	}

	/*!		
	\brief Constructor of  ForStmt
	\param var: string of the variable
	\param start: ExpNode of the start of the loop 
	\param end: ExpNode of the end of the loop
	\param statements: StatementList of the body of the loop
	\post  A new ForStmt is created with the parameters
*/
	ForStmt(std::string var, ExpNode * start, ExpNode * end, StatementList * statements)
	{
		this->_var = var;
		this->_start = start;
		this->_end = end;
		this->_inc = NULL;
		this->_stmts = statements;
	}


/*!
	\brief   Print the ForStmt
	\return  void
	\sa		 evaluate
*/
  void print();

/*!	
	\brief   Evaluate the ForStmt
	\return  void
	\sa		 print
*/
  void evaluate();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   SwitchStmt
  \brief   Definition of atributes and methods of SwitchStmt class
  \note    SwitchStmt Class publicly inherits from CaseList class 
		   and adds its own print and evaluate functions
*/
class SwitchStmt : public Statement {

private:
	ExpNode * _exp; //!<  Expression to be evaluated
	lp::CaseList * _caseList; //!<  List of cases for the switch statement

public:

	/**
	\brief Constructor of the SwitchStmt class
	\param exp: Expression to be evaluated
	\param caseList: List of cases for the switch statement
	\post A new SwitchStmt is created with the parameters 
	*/
	SwitchStmt(ExpNode * exp, lp::CaseList * caseList) {
		this->_exp = exp;
		this->_caseList = caseList;
	}


	/*!
		\brief   Print the SwitchStmt
		\return  void
		\sa		 evaluate
	*/
	  void print();

	/*!	
		\brief   Evaluate the SwitchStmt
		\return  void
		\sa		 print
	*/
	  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// NEW in example 17
/*

  \class   BlockStmt
  \brief   Definition of atributes and methods of BlockStmt class
  \note    BlockStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions

class BlockStmt : public Statement 
{
 private:
   std::list<Statement *> *_stmts;  //!< List of statements

  public:
	
	\brief Constructor of  WhileStmt
	\param stmtList: list of Statement
	\post  A new BlockStmt is created with the parameters

  BlockStmt(std::list<Statement *> *stmtList): _stmts(stmtList)
	{
		// Empty
	}



	\brief   Print the BlockStmt
	\return  void
	\sa		 evaluate

  void print();


	\brief   Evaluate the BlockStmt
	\return  void
	\sa		 print

  void evaluate();
};
*/

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AST
  \brief   Definition of atributes and methods of AST class
*/
class AST {
 private:
  lp::StatementList *_stmts;  //!< List of statements

 public:

/*!		
	\brief Constructor of PrintStmt 
	\param stmtList: pointer to a list of pointers to Statement
	\post  A new PrintStmt is created with the parameter
*/
  AST(lp::StatementList *stmtList): _stmts(stmtList)
	{
		// Empty
	}

/*!
	\brief   print the AST
	\return  void
	\sa		 evaluate()
*/
  void print();

/*!	
	\brief   evaluate the AST
	\return  double
	\sa		 print
*/
  void evaluate();
};

// End of name space lp
}



// End of _AST_HPP_
#endif




