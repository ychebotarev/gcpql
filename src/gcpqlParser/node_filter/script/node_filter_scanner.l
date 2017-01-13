/* $Id$ -*- mode: c++ -*- */
/** \file scanner.ll Define the Node filter Flex lexical scanner */

%top{
#include <stdint.h>
#include <inttypes.h>
}

%{ /*** C/C++ Declarations ***/

#include <string>
#include "node_filter_scanner.h"

/* import the parser's token type into a local typedef */
typedef gcpql_nodefilter::Parser::token token;
typedef gcpql_nodefilter::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

%option prefix="NodeFilter"

/* the manual says "somewhat more optimized" */
%option batch

%option yywrap nounput 

%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}
%% 

%{
    // reset location
    yylloc->step();
%}

  /* keywords */
(?i:AND)	{ return token::OP_AND; }
(?i:OR) { return token::OP_OR; }
(?i:TRUE) { return token::CONSTANT_TRUE; }
(?i:FALSE) { return token::CONSTANT_FALSE; }
(?i:NOT) { return token::OP_NOT; }
(?i:IN) { return token::OP_IN; }
(?i:LIKE) { return token::OP_LIKE; }

  /* simple types */
[0-9]+ {
    yylval->integerVal = atoi(yytext);
    return token::INTEGER;
}

[0-9]+"."[0-9]* {
    yylval->doubleVal = atof(yytext);
    return token::DOUBLE;
}

[A-Za-z][A-Za-z0-9_]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::IDENTIFIER;
}


  /* operators */
"&&"	{ return token::OP_AND; }
"||"    { return token::OP_OR; }

">"		{ return token::OP_GT; }
">="	{ return token::OP_GT_EQ; }
"<"		{ return token::OP_LT; }
"<="	{ return token::OP_LT_EQ; }
"="		{ return token::OP_EQ; }
"!=" 	{ return token::OP_NOT_EQ; }

"+" 	{ return token::OP_PLUS; }
"-" 	{ return token::OP_MINUS; }
"*" 	{ return token::OP_MUL; }
"//" 	{ return token::OP_DIVINT; }
"/" 	{ return token::OP_DIV; }
"%" 	{ return token::OP_MOD; }
"^" 	{ return token::OP_POW; }

  /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

  /* gobble up end-of-lines */
\n {
    yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}

  /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}


%% /*** Additional Code ***/

namespace gcpql_nodefilter {
	Scanner::Scanner(std::istream* in,
			 std::ostream* out)
		: NodeFilterFlexLexer(in, out)
	{
	}

	Scanner::~Scanner()
	{
	}

	void Scanner::set_debug(bool b)
	{
		yy_flex_debug = b;
	}
} // end of namespace

/* This implementation of yyFlexLexer::yylex() is required to fill the
 * vtable of the class yyFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int NodeFilterFlexLexer::yylex()
{
    std::cerr << "in NodeFilterFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int NodeFilterFlexLexer::yywrap()
{
    return 1;
}
