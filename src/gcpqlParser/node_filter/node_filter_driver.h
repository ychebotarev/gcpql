// $Id$ 	
/** \file driver.h Declaration of the example::Driver class. */

#ifndef NODE_FILTER_DRIVER_H
#define NODE_FILTER_DRIVER_H

#include <string>
#include <vector>
#include <memory>
#include "NodeFilterExpression\expressions.h"

namespace gcpql_nodefilter {

class Driver
{
public:
    /// construct a new parser driver context
    Driver();

    /// enable debug output in the flex scanner
    bool trace_scanning;

    /// enable debug output in the bison parser
    bool trace_parsing;

    /// stream name (file or input stream) used for error messages.
    std::string streamname;

    /** Invoke the scanner and parser for a stream.
     * @param in	input stream
     * @param sname	stream name for error messages
     * @return		Expression context if successfully parsed, NULL is there was parsing error
     */
	class Runner* parse_stream(std::istream& in,
		      const std::string& sname = "stream input");

    /** Invoke the scanner and parser on an input string.
     * @param input	input string
     * @param sname	stream name for error messages
     * @return		Expression context if successfully parsed, NULL is there was parsing error
     */
	class Runner* parse_string(const std::string& input,
		      const std::string& sname = "string stream");


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
