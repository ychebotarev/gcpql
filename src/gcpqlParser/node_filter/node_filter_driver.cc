// $Id$
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "node_filter_driver.h"
#include "node_filter_scanner.h"
#include "node_filter_context.h"
#include "node_filter_runner.h"

namespace gcpql_nodefilter {

	Driver::Driver()
		: trace_scanning(false),
		trace_parsing(false)
	{
	}

	Runner* Driver::parse_stream(std::istream& in, const std::string& sname)
	{
		streamname = sname;

		Scanner scanner(&in);
		scanner.set_debug(trace_scanning);
		this->lexer = &scanner;

		std::auto_ptr<Runner> runner(new Runner);

		Parser parser(*this, *runner.get());
#if YYDEBUG
		parser.set_debug_level(trace_parsing);
#endif
		return (parser.parse() == 0) ? runner.release() : NULL;
	}


	Runner* Driver::parse_string(const std::string &input, const std::string& sname)
	{
		std::istringstream iss(input);
		return parse_stream(iss, sname);
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

