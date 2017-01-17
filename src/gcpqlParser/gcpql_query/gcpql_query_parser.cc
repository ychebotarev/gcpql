// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <memory>
#include <string>
#include <vector>

#include "graph\graph.h"
#include "filter\expressions.h"



# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "gcpql_query_parser.h"

// User implementation prologue.



#include "gcpql_query_driver.h"
#include "gcpql_query_scanner.h"
#include "gcpql_query_runner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex





#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace gcpql_query {


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg, class Runner& runner_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      runner (runner_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 34: // "string"


        { delete (yysym.value.stringVal); }

        break;

      case 36: // IDENTIFIER


        { delete (yysym.value.stringVal); }

        break;

      case 48: // return_expr


        { delete (yysym.value.graphQuery); }

        break;

      case 49: // filter_expr


        { delete (yysym.value.graphFilterVal); }

        break;

      case 50: // graph_slice


        { delete (yysym.value.sliceVal); }

        break;

      case 51: // return_nodes_list


        { delete (yysym.value.sliceVal); }

        break;

      case 52: // return_node


        { delete (yysym.value.nodeVal); }

        break;

      case 53: // select_expr


        { delete (yysym.value.pathVal); }

        break;

      case 54: // graph_path


        { delete (yysym.value.pathVal); }

        break;

      case 55: // graph_relation


        { delete (yysym.value.relationVal); }

        break;

      case 56: // node_from


        { delete (yysym.value.nodeVal); }

        break;

      case 57: // node_to


        { delete (yysym.value.nodeVal); }

        break;

      case 58: // edge


        { delete (yysym.value.nodeVal); }

        break;

      case 59: // node


        { delete (yysym.value.nodeVal); }

        break;

      case 60: // logical_expr


        { delete (yysym.value.expressionVal); }

        break;

      case 61: // comparation_expr


        { delete (yysym.value.expressionVal); }

        break;

      case 62: // constant_array


        { delete (yysym.value.collectionVal); }

        break;

      case 63: // math_expr


        { delete (yysym.value.expressionVal); }

        break;

      case 64: // constant


        { delete (yysym.value.expressionVal); }

        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yylhs)
  {
    int yyr = yypgoto_[yylhs - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yylhs - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// $$ and @$.
    stack_symbol_type yylhs;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    
{
    // initialize the initial location object
    //@$.begin.filename = @$.end.filename = &driver.streamname;
}



    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULL, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYLHS.VALUE to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yylhs.value = yystack_[yylen - 1].value;
    else
      yylhs.value = yystack_[0].value;

    // Compute the default @$.
    {
      slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
      YYLLOC_DEFAULT (yylhs.location, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    try
      {
        switch (yyn)
          {
  case 2:

    { runner.SetGraphQuery((yystack_[0].value.graphQuery)); }

    break;

  case 3:

    { 
		(yylhs.value.graphQuery) = new GraphQuery();
		(yylhs.value.graphQuery)->SetGraphSlice((yystack_[3].value.sliceVal)); 
		(yylhs.value.graphQuery)->SetGraphPath((yystack_[1].value.pathVal));
		(yylhs.value.graphQuery)->SetFilter((yystack_[0].value.graphFilterVal));
	}

    break;

  case 4:

    {
		(yylhs.value.graphQuery) = new GraphQuery();
		(yylhs.value.graphQuery)->SetGraphSlice((yystack_[1].value.pathVal)); 
		(yylhs.value.graphQuery)->SetGraphPath((yystack_[1].value.pathVal));
		(yylhs.value.graphQuery)->SetFilter((yystack_[0].value.graphFilterVal));
	}

    break;

  case 5:

    { (yylhs.value.graphFilterVal) = new GraphPathFilter(); (yylhs.value.graphFilterVal)->SetRootExpression((yystack_[0].value.expressionVal)); }

    break;

  case 6:

    { (yylhs.value.graphFilterVal) = nullptr; }

    break;

  case 7:

    { (yylhs.value.sliceVal) = new GraphSlice(); (yylhs.value.sliceVal)->Add(new GraphNode()); }

    break;

  case 8:

    { (yylhs.value.sliceVal) = (yystack_[0].value.sliceVal); }

    break;

  case 9:

    { (yylhs.value.sliceVal) = new GraphSlice(); (yylhs.value.sliceVal)->Add((yystack_[0].value.nodeVal)); }

    break;

  case 10:

    { (yylhs.value.sliceVal) = (yystack_[2].value.sliceVal); (yylhs.value.sliceVal)->Add((yystack_[0].value.nodeVal)); }

    break;

  case 11:

    { (yylhs.value.nodeVal) = new GraphNode((yystack_[0].value.stringVal));}

    break;

  case 12:

    { (yylhs.value.nodeVal) = new GraphNode((yystack_[2].value.stringVal), (yystack_[0].value.stringVal));}

    break;

  case 13:

    { (yylhs.value.pathVal) = (yystack_[0].value.pathVal); }

    break;

  case 14:

    { (yylhs.value.pathVal) = (yystack_[0].value.pathVal); }

    break;

  case 15:

    { (yylhs.value.pathVal) = new GraphPath(); (yylhs.value.pathVal)->Add((yystack_[0].value.relationVal)); }

    break;

  case 16:

    { (yylhs.value.pathVal) = (yystack_[2].value.pathVal); (yylhs.value.pathVal)->Add((yystack_[0].value.relationVal)); }

    break;

  case 17:

    { (yylhs.value.relationVal) = new GraphRelation((yystack_[3].value.nodeVal), (yystack_[1].value.nodeVal),  (yystack_[2].value.nodeVal));}

    break;

  case 18:

    { (yylhs.value.relationVal) = new GraphRelation((yystack_[2].value.nodeVal), (yystack_[1].value.nodeVal)); }

    break;

  case 19:

    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }

    break;

  case 20:

    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }

    break;

  case 21:

    { (yylhs.value.nodeVal) = new GraphNode((yystack_[0].value.stringVal)); }

    break;

  case 22:

    { (yylhs.value.nodeVal) = new GraphNode((yystack_[0].value.stringVal));}

    break;

  case 23:

    { (yylhs.value.nodeVal) = new GraphNode((yystack_[2].value.stringVal), (yystack_[0].value.stringVal));}

    break;

  case 24:

    { (yylhs.value.expressionVal) = new LogicalExpressionAnd((yystack_[2].value.expressionVal),(yystack_[0].value.expressionVal)); }

    break;

  case 25:

    { (yylhs.value.expressionVal) = new LogicalExpressionOr((yystack_[2].value.expressionVal),(yystack_[0].value.expressionVal)); }

    break;

  case 26:

    { (yylhs.value.expressionVal) = (yystack_[1].value.expressionVal); }

    break;

  case 27:

    { (yylhs.value.expressionVal) = (yystack_[0].value.expressionVal); }

    break;

  case 28:

    { (yylhs.value.expressionVal) = new ConstantExpressionInteger(1); }

    break;

  case 29:

    { (yylhs.value.expressionVal) = new ConstantExpressionInteger(0); }

    break;

  case 30:

    { (yylhs.value.expressionVal) = new LogicalExpressionNot((yystack_[0].value.expressionVal)); }

    break;

  case 31:

    { (yylhs.value.expressionVal) = new ComparationExpressionGt((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 32:

    { (yylhs.value.expressionVal) = new ComparationExpressionGtEq((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 33:

    { (yylhs.value.expressionVal) = new ComparationExpressionLt((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 34:

    { (yylhs.value.expressionVal) = new ComparationExpressionLtEq((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 35:

    { (yylhs.value.expressionVal) = new ComparationExpressionEq((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 36:

    { (yylhs.value.expressionVal) = new ComparationExpressionNotEq((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 37:

    {
			auto constant_string = new ConstantExpressionIdentifier((yystack_[4].value.stringVal)); 
			(yylhs.value.expressionVal) = new ValueInCollectionFunction(constant_string, (yystack_[1].value.collectionVal)); 
		}

    break;

  case 38:

    { (yylhs.value.collectionVal) = new ConstantsCollection(); (yylhs.value.collectionVal)->Add((yystack_[0].value.expressionVal)); }

    break;

  case 39:

    { (yylhs.value.collectionVal) = (yystack_[0].value.collectionVal); (yylhs.value.collectionVal)->Add((yystack_[2].value.expressionVal)); }

    break;

  case 40:

    { (yylhs.value.expressionVal) = new MathExpressionAdd((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 41:

    { (yylhs.value.expressionVal) = new MathExpressionSub((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 42:

    { (yylhs.value.expressionVal) = new MathExpressionMul((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 43:

    { (yylhs.value.expressionVal) = new MathExpressionDiv((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 44:

    { (yylhs.value.expressionVal) = new MathExpressionDivInt((yystack_[2].value.expressionVal), (yystack_[0].value.expressionVal)); }

    break;

  case 46:

    { (yylhs.value.expressionVal) = new ConstantExpressionString((yystack_[0].value.stringVal)); }

    break;

  case 47:

    { (yylhs.value.expressionVal) = new ConstantExpressionIdentifier((yystack_[0].value.stringVal));}

    break;

  case 48:

    { (yylhs.value.expressionVal) = new ConstantExpressionInteger((yystack_[0].value.integerVal));}

    break;

  case 49:

    { (yylhs.value.expressionVal) = new ConstantExpressionDouble((yystack_[0].value.doubleVal));}

    break;

  case 50:

    { (yylhs.value.expressionVal) = (yystack_[1].value.expressionVal); }

    break;



          default:
            break;
          }
      }
    catch (const syntax_error& yyexc)
      {
        error (yyexc);
        YYERROR;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yylhs);
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    // Shift the result of the reduction.
    yypush_ (YY_NULL, yylhs);
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULL, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULL, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -54;

  const signed char Parser::yytable_ninf_ = -23;

  const signed char
  Parser::yypact_[] =
  {
      28,     0,   -28,    17,    60,   -54,    37,    26,   -54,   -54,
      30,    39,    29,   -54,    26,    44,    38,   -54,   -54,    10,
     -54,   -28,    58,   -25,    59,    61,     7,    51,    17,   -54,
      10,   -54,   -54,   -54,   -54,   -54,    91,    10,    27,   -54,
      69,   -54,   -54,   -54,    37,   -54,   -54,   -54,    54,   -54,
      56,    -4,    -5,    10,    10,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,   -54,   -54,    31,   -54,
     -54,   -54,    72,   -54,    31,    74,    74,    74,    74,    74,
      74,    40,    40,   -54,   -54,   -54,    57,    62,    32,   -54,
      31,   -54
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     6,    14,    15,     7,
      11,     0,     8,     9,    13,    22,     0,    19,     1,     0,
       4,     0,     0,     0,     0,     0,    21,     0,     0,    20,
       0,    28,    29,    48,    49,    46,    47,     0,     5,    27,
       0,    45,    16,    12,     6,    10,    23,    18,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,    17,     0,    26,
      50,    24,    25,    47,     0,    31,    32,    33,    34,    35,
      36,    40,    41,    42,    44,    43,     0,    38,     0,    37,
       0,    39
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -54,   -54,   -54,    63,   -54,   -54,    77,    80,   103,    85,
     -54,    81,   -54,   105,     8,   -54,    20,   -35,   -53
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     4,     5,    20,    11,    12,    13,     6,     7,     8,
      16,    27,    28,    29,    38,    39,    86,    40,    41
  };

  const signed char
  Parser::yytable_[] =
  {
      53,    54,    52,     2,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    87,     3,     9,    30,     3,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    53,    54,    25,    31,    32,    10,    87,    49,    88,
      70,    69,    33,    34,    35,    51,    36,    61,    62,    63,
      64,    65,   -22,    15,    37,     1,     2,    63,    64,    65,
      18,    71,    72,    33,    34,    35,    19,    73,    21,    23,
      25,    24,     3,    22,    26,    74,    53,    70,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    61,
      62,    63,    64,    65,    43,    10,    47,    46,    50,    67,
      68,    45,    89,    44,    90,    14,    42,    66,    17,    48,
      91
  };

  const unsigned char
  Parser::yycheck_[] =
  {
       4,     5,    37,    28,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    68,    44,    17,     8,    44,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     4,     5,    26,    24,    25,    36,    90,    30,    74,
      45,    45,    32,    33,    34,    37,    36,    15,    16,    17,
      18,    19,    45,    36,    44,    27,    28,    17,    18,    19,
       0,    53,    54,    32,    33,    34,    29,    36,    42,    30,
      26,    42,    44,    43,    36,    44,     4,    45,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    15,
      16,    17,    18,    19,    36,    36,    45,    36,     7,    45,
      44,    24,    45,    23,    42,     2,    21,    44,     3,    28,
      90
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    27,    28,    44,    47,    48,    53,    54,    55,    17,
      36,    50,    51,    52,    54,    36,    56,    59,     0,    29,
      49,    42,    43,    30,    42,    26,    36,    57,    58,    59,
       8,    24,    25,    32,    33,    34,    36,    44,    60,    61,
      63,    64,    55,    36,    53,    52,    36,    45,    57,    60,
       7,    60,    63,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    49,    45,    44,    45,
      45,    60,    60,    36,    44,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    62,    64,    63,    45,
      42,    62
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    46,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      57,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    63,    63,    63,    63,    64,    64,    64,    64,
      64
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     5,     2,     2,     0,     1,     1,     1,
       3,     1,     3,     2,     1,     1,     3,     5,     4,     1,
       1,     1,     1,     3,     3,     3,     3,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     3,     5,     1,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "OP_AND",
  "OP_OR", "OP_LIKE", "OP_IN", "OP_NOT", "OP_GT", "OP_GT_EQ", "OP_LT",
  "OP_LT_EQ", "OP_EQ", "OP_NOT_EQ", "OP_PLUS", "OP_MINUS", "OP_MUL",
  "OP_DIVINT", "OP_DIV", "OP_MOD", "OP_POW", "OP_SHIFT_LEFT",
  "OP_SHIFT_RIGHT", "CONSTANT_TRUE", "CONSTANT_FALSE", "OP_AS",
  "OP_RETURN", "OP_SELECT", "OP_WHERE", "OP_FROM", "OP_JOIN",
  "\"integer\"", "\"double\"", "\"string\"", "NAME", "IDENTIFIER", "BOOL",
  "'|'", "'&'", "'^'", "UMINUS", "','", "'.'", "'('", "')'", "$accept",
  "gcpql_body", "return_expr", "filter_expr", "graph_slice",
  "return_nodes_list", "return_node", "select_expr", "graph_path",
  "graph_relation", "node_from", "node_to", "edge", "node", "logical_expr",
  "comparation_expr", "constant_array", "math_expr", "constant", YY_NULL
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   144,   144,   148,   155,   165,   166,   170,   171,   175,
     176,   180,   181,   185,   186,   190,   191,   195,   196,   199,
     200,   201,   204,   205,   209,   210,   211,   212,   213,   214,
     215,   219,   220,   221,   222,   223,   224,   225,   233,   234,
     238,   239,   240,   241,   242,   243,   247,   248,   249,   250,
     251
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,     2,
      44,    45,     2,     2,    42,     2,    43,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    41
    };
    const unsigned int user_token_number_max_ = 293;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // gcpql_query


 

void gcpql_query::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
