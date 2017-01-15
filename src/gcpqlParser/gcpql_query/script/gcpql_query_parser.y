/* $Id$ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <memory>
#include <string>
#include <vector>

#include "graph\graph.h"
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
	class GraphEdge* edgeVal;
	class GraphRelation* relationVal;
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

%type <pathVal> return_expr select_expr graph_path
%type <relationVal> graph_relation
%type <nodeVal> node_from node_to node
%type <edgeVal> edge

%destructor { delete $$; } IDENTIFIER
%destructor { delete $$; } return_expr select_expr graph_path
%destructor { delete $$; } graph_relation 
%destructor { delete $$; } node_from node_to node
%destructor { delete $$; } edge

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

gcpql_body : return_expr { runner.SetGraphPath($1); };


return_expr 
	: select_expr 
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
edge : IDENTIFIER { $$ = new GraphEdge($1); } ;

node 
	: IDENTIFIER { $$ = new GraphNode($1);}
	| IDENTIFIER OP_AS IDENTIFIER { $$ = new GraphNode($1, $3);}
	;

%% 

void gcpql_query::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
