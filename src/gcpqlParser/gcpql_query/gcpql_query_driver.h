// $Id$ 	
/** \file driver.h Declaration of the example::Driver class. */

#ifndef NODE_FILTER_DRIVER_H
#define NODE_FILTER_DRIVER_H

#include <string>
#include <vector>
#include <memory>

namespace gcpql_query {

class Runner;

class Driver
{
public:
    /// construct a new parser driver context
    Driver();

    /// enable debug output in the flex scanner
    bool trace_scanning;

    /// enable debug output in the bison parser
    bool trace_parsing;

    /** Invoke the scanner and parser for a stream.
     * @param in	input stream
     * @return		Expression context if successfully parsed, NULL is there was parsing error
     */
	class Runner* parse_stream(std::istream& in);

    /** Invoke the scanner and parser on an input string.
     * @param input	input string
     * @return		Expression context if successfully parsed, NULL is there was parsing error
     */
	class Runner* parse_string(const std::string& input);


    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void error(const class location& l, const std::string& m);

    /** General error handling. This can be modified to output the error
     * e.g. to a dialog box. */
    void error(const std::string& m);

    /** Pointer to the current lexer instance, this is used to connect the
     * parser to the scanner. It is used in the yylex macro. */
    class Scanner* lexer;
};

} // namespace nodefilter


#endif // NODE_FILTER_DRIVER_H
