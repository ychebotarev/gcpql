/* $Id$ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <memory>
#include <string>
#include <vector>

#include "Expression\expressions.h"
%}

%require "2.4"
%locations
%defines

%define "parser_class_name" {Parser}
%define api.namespace {gcpql_nodefilter}

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* keep track of the current position within the input */
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

%parse-param { class Driver& driver }
%parse-param { class Runner& runner }

%error-verbose

%union {
    int integerVal;
    double doubleVal;
    std::string* stringVal;
    class BaseExpression* expressionVal;
	class ConstantsCollection* collectionVal;
}

%token END	     0	"end of file"
%token EOL		"end of line"
%token OP_AND
%token OP_OR
%token OP_LIKE
%token OP_IN
%token OP_NOT
%token OP_GT
%token OP_GT_EQ
%token OP_LT
%token OP_LT_EQ
%token OP_EQ
%token OP_NOT_EQ
%token OP_PLUS
%token OP_MINUS
%token OP_MUL
%token OP_DIVINT
%token OP_DIV
%token OP_MOD
%token OP_POW
%token OP_SHIFT_LEFT 
%token OP_SHIFT_RIGHT
%token CONSTANT_TRUE
%token CONSTANT_FALSE

%token <integerVal> INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING_CONSTANT "string"
%token <stringVal> NAME
%token <stringVal> IDENTIFIER
%token <interegVal> BOOL 

%type <expressionVal> constant math_expr comparation_expr logical_expr
%type <collectionVal> constant_array

%destructor { delete $$; } STRING_CONSTANT IDENTIFIER
%destructor { delete $$; } constant math_expr comparation_expr logical_expr
%destructor { delete $$; } constant_array 

%left OP_OR
%left OP_AND
%nonassoc OP_IN OP_LIKE 
%left OP_NOT 
%left OP_GT OP_GT_EQ OP_LT OP_LT_EQ OP_EQ OP_NOT_EQ
%left '|'
%left '&'
%left OP_SHIFT_LEFT OP_SHIFT_RIGHT
%left OP_PLUS OP_MINUS
%left OP_DIV OP_DIVINT OP_MUL OP_MOD
%left '^'
%nonassoc UMINUS

%start filter_body

%{

#include "node_filter_driver.h"
#include "node_filter_scanner.h"
#include "node_filter_runner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% 

filter_body : logical_expr { runner.SetRootExpression($1); $1 = nullptr; };

logical_expr 
	: logical_expr OP_AND logical_expr { $$ = new LogicalExpressionAnd($1,$3); $1 = NULL; $3 = nullptr; }
	| logical_expr OP_OR logical_expr { $$ = new LogicalExpressionOr($1,$3); $1 = NULL; $3 = nullptr; }
	| '(' logical_expr ')' { $$ = $2; $2 = nullptr; };
	| comparation_expr { $$ = $1; $1 = nullptr; }
	| CONSTANT_TRUE { $$ = new ConstantExpressionInteger(1); }
	| CONSTANT_FALSE { $$ = new ConstantExpressionInteger(0); }
	| OP_NOT logical_expr { $$ = new LogicalExpressionNot($2); $2 = nullptr; }
	;

comparation_expr 
	: math_expr OP_GT math_expr { $$ = new ComparationExpressionGt($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_GT_EQ math_expr { $$ = new ComparationExpressionGtEq($1, $3); $1 = NULL; $3 = nullptr; }
	| math_expr OP_LT math_expr { $$ = new ComparationExpressionLt($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_LT_EQ math_expr { $$ = new ComparationExpressionLtEq($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_EQ math_expr { $$ = new ComparationExpressionEq($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_NOT_EQ math_expr { $$ = new ComparationExpressionNotEq($1, $3); $1 = nullptr; $3 = NULL; }
	| IDENTIFIER OP_IN '(' constant_array ')' 
		{
			auto constant_string = new ConstantExpressionIdentifier(*$1); 
			$$ = new ValueInCollectionFunction(constant_string, $4); 
			$1 = nullptr; $4 = nullptr; 
		}
	;

constant_array
	: constant { $$ = new ConstantsCollection(); $$->Add($1); $1 = nullptr; }
	| constant ',' constant_array { $$ = $3; $$->Add($1); $1 = nullptr; $3 = nullptr; }
	;

math_expr 
	: math_expr OP_PLUS math_expr { $$ = new MathExpressionAdd($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_MINUS math_expr { $$ = new MathExpressionSub($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_MUL math_expr { $$ = new MathExpressionMul($1, $3); $1 = nullptr; $3 = nullptr; }
	| math_expr OP_DIV math_expr { $$ = new MathExpressionDiv($1, $3); $1 = nullptr; $3 = nullptr; }
    | math_expr OP_DIVINT math_expr { $$ = new MathExpressionDivInt($1, $3); $1 = nullptr; $3 = nullptr; }
	| constant
	;

constant
	: STRING_CONSTANT { $$ = new ConstantExpressionString($1); $1 = nullptr; }
	| IDENTIFIER { $$ = new ConstantExpressionIdentifier(*$1);}
	| INTEGER { $$ = new ConstantExpressionInteger($1);}
	| DOUBLE { $$ = new ConstantExpressionDouble($1);}
	| '(' math_expr ')' { $$ = $2; };
	;

%% 

void gcpql_nodefilter::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
