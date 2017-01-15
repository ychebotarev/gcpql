// $Id$
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "gcpql_query_driver.h"
#include "gcpql_query_scanner.h"
#include "gcpql_query_context.h"
#include "gcpql_query_runner.h"

namespace gcpql_query {

	Driver::Driver()
		: trace_scanning(false),
		trace_parsing(false)
	{
	}

	Runner* Driver::parse_stream(std::istream& in)
	{
		Scanner scanner(&in);
		scanner.set_debug(trace_scanning);
		this->lexer = &scanner;

		std::auto_ptr<Runner> runner(new Runner);

		Parser parser(*this, *runner.get());
#if YYDEBUG
		parser.set_debug_level(trace_parsing);
#endif
		return (parser.parse() == 0) ? runner.release() : nullptr;
	}

	Runner* Driver::parse_string(const std::string &input)
	{
		std::istringstream iss(input);
		return parse_stream(iss);
	}

	void Driver::error(const class location& l,
		const std::string& m)
	{
		std::cerr << l << ": " << m << std::endl;
	}

	void Driver::error(const std::string& m)
	{
		std::cerr << m << std::endl;
	}
}

