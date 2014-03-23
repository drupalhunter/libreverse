#ifndef REVERSE_BAD_ASSERT_HPP
#define REVERSE_BAD_ASSERT_HPP

#include <reverse/trace.hpp>
#include <reverse/trace_area.hpp>
#include <reverse/trace_level.hpp>

#include <sstream>
#include <stdexcept>

namespace reverse {

  class bad_assert : public std::runtime_error {
  public:
      
    bad_assert ( std::string file,
		 boost::int32_t line,
		 std::string message )
      : std::runtime_error ( message.c_str() )
    {
      trace::write_trace ( reverse::trace_area::error_handling,
			   reverse::trace_level::detail,
			   "Entering Bad_Assert constructor" );

      std::stringstream output;
      output << "Assertion failed: file " << file
	     << ", line " << line;

      if ( ! message.empty() )
	{
	  output << std::endl << message;
	}

      trace::write_trace ( reverse::trace_area::error_handling,
			   reverse::trace_level::error,
			   output.str().c_str() );

      abort();
    }
  };

} /* namespace reverse */

#endif // REVERSE_BAD_ASSERT_HPP
