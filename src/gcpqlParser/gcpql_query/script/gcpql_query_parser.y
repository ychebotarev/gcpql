/* $Id$ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <memory>
#include <string>
#include <vector>

#include "graph\graph.h"
#include "filter\expressions.h"
%}

%require "2.4"
%locations
%defines

%define "parser_class_name" {Parser}
%define api.namespace {gcpql_query}

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* keep track of the current position within the input */
%initial-action
{
    // initialize the initial location object
    //@$.begin.filename = @$.end.filename = &driver.streamname;
};

%parse-param { class Driver& driver }
%parse-param { class Runner& runner }

%error-verbose

%union {
    int integerVal;
    double doubleVal;
    std::string* stringVal;
	class GraphPath* pathVal;
	class GraphNode* nodeVal;
	class GraphRelation* relationVal;
	class GraphPathFilter* graphFilterVal;
	class GraphSlice* sliceVal;
	class GraphQuery* graphQuery;
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
%token OP_AS
%token OP_RETURN
%token OP_SELECT
%token OP_WHERE
%token OP_FROM
%token OP_JOIN

%token <integerVal> INTEGER		"integer"
%token <doubleVal> 	DOUBLE		"double"
%token <stringVal> 	STRING_CONSTANT "string"
%token <stringVal> NAME
%token <stringVal> IDENTIFIER
%token <interegVal> BOOL 

%type <pathVal> select_expr graph_path
%type <relationVal> graph_relation
%type <nodeVal> node_from node_to node edge return_node
%type <graphFilterVal> filter_expr
%type <sliceVal> graph_slice return_nodes_list
%type <graphQuery> return_expr

%type <expressionVal> constant math_expr comparation_expr logical_expr
%type <collectionVal> constant_array

%destructor { delete $$; } IDENTIFIER
%destructor { delete $$; } select_expr graph_path
%destructor { delete $$; } graph_relation 
%destructor { delete $$; } node_from node_to node edge return_node
%destructor { delete $$; } filter_expr
%destructor { delete $$; } graph_slice return_nodes_list
%destructor { delete $$; } return_expr

/* filtering */
%destructor { delete $$; } STRING_CONSTANT 
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

%start gcpql_body

%{

#include "gcpql_query_driver.h"
#include "gcpql_query_scanner.h"
#include "gcpql_query_runner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% 

gcpql_body : return_expr { runner.SetGraphQuery($1); };


return_expr 
	: OP_RETURN graph_slice OP_FROM select_expr filter_expr
	{ 
		$$ = new GraphQuery();
		$$->SetGraphSlice($2); 
		$$->SetGraphPath($4);
		$$->SetFilter($5);
	}
	| select_expr filter_expr
	{
		$$ = new GraphQuery();
		$$->SetGraphSlice($1); 
		$$->SetGraphPath($1);
		$$->SetFilter($2);
	}
	;

filter_expr
	: OP_WHERE logical_expr{ $$ = new GraphPathFilter(); $$->SetRootExpression($2); }
	| { $$ = nullptr; }
	;

graph_slice
	: OP_MUL { $$ = new GraphSlice(); $$->Add(new GraphNode()); }
	| return_nodes_list { $$ = $1; }
	;

return_nodes_list
	: return_node { $$ = new GraphSlice(); $$->Add($1); }
	| return_nodes_list ',' return_node { $$ = $1; $$->Add($3); }
	;
	
return_node
	: IDENTIFIER { $$ = new GraphNode($1);}
	| IDENTIFIER '.' IDENTIFIER { $$ = new GraphNode($1, $3);}
	;

select_expr
	: OP_SELECT graph_path { $$ = $2; }
	| graph_path { $$ = $1; }
	;

graph_path
	: graph_relation { $$ = new GraphPath(); $$->Add($1); }
	| graph_path ',' graph_relation { $$ = $1; $$->Add($3); }
	;

graph_relation
	: '(' node_from edge node_to ')' { $$ = new GraphRelation($2, $4,  $3);}
	| '(' node_from node_to')'{ $$ = new GraphRelation($2, $3); }
	;

node_from : node { $$ = $1; } ;
node_to : node { $$ = $1; } ;
edge : IDENTIFIER { $$ = new GraphNode($1); } ;

node 
	: IDENTIFIER { $$ = new GraphNode($1);}
	| IDENTIFIER OP_AS IDENTIFIER { $$ = new GraphNode($1, $3);}
	;

logical_expr 
	: logical_expr OP_AND logical_expr { $$ = new LogicalExpressionAnd($1,$3); }
	| logical_expr OP_OR logical_expr { $$ = new LogicalExpressionOr($1,$3); }
	| '(' logical_expr ')' { $$ = $2; };
	| comparation_expr { $$ = $1; }
	| CONSTANT_TRUE { $$ = new ConstantExpressionInteger(1); }
	| CONSTANT_FALSE { $$ = new ConstantExpressionInteger(0); }
	| OP_NOT logical_expr { $$ = new LogicalExpressionNot($2); }
	;

comparation_expr 
	: math_expr OP_GT math_expr { $$ = new ComparationExpressionGt($1, $3); }
	| math_expr OP_GT_EQ math_expr { $$ = new ComparationExpressionGtEq($1, $3); }
	| math_expr OP_LT math_expr { $$ = new ComparationExpressionLt($1, $3); }
	| math_expr OP_LT_EQ math_expr { $$ = new ComparationExpressionLtEq($1, $3); }
	| math_expr OP_EQ math_expr { $$ = new ComparationExpressionEq($1, $3); }
	| math_expr OP_NOT_EQ math_expr { $$ = new ComparationExpressionNotEq($1, $3); }
	| IDENTIFIER OP_IN '(' constant_array ')' 
		{
			auto constant_string = new ConstantExpressionIdentifier($1); 
			$$ = new ValueInCollectionFunction(constant_string, $4); 
		}
	;

constant_array
	: constant { $$ = new ConstantsCollection(); $$->Add($1); }
	| constant ',' constant_array { $$ = $3; $$->Add($1); }
	;

math_expr 
	: math_expr OP_PLUS math_expr { $$ = new MathExpressionAdd($1, $3); }
	| math_expr OP_MINUS math_expr { $$ = new MathExpressionSub($1, $3); }
	| math_expr OP_MUL math_expr { $$ = new MathExpressionMul($1, $3); }
	| math_expr OP_DIV math_expr { $$ = new MathExpressionDiv($1, $3); }
    | math_expr OP_DIVINT math_expr { $$ = new MathExpressionDivInt($1, $3); }
	| constant
	;

constant
	: STRING_CONSTANT { $$ = new ConstantExpressionString($1); }
	| IDENTIFIER { $$ = new ConstantExpressionIdentifier($1);}
	| INTEGER { $$ = new ConstantExpressionInteger($1);}
	| DOUBLE { $$ = new ConstantExpressionDouble($1);}
	| '(' math_expr ')' { $$ = $2; };
	;

%% 

void gcpql_query::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
