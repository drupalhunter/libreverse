#ifndef REVERSE_BAD_ASSERT_HPP
#define REVERSE_BAD_ASSERT_HPP

namespace reverse {
  namespace assert {

    class bad_assert : public std::exception {
    public:

      bad_assert ( std::string file,
		      boost::int32_t line,
		      std::string message )
      {
	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::DETAIL,
	    "Entering Bad_Assert constructor" );

	std::stringstream output;
	output << "Assertion failed: file " << file
	       << ", line " << line;

	if ( ! message.empty() )
	  {
	    output << std::endl << message;
	  }

	reverse::trace::Trace::write_Trace
	  ( reverse::api::TraceArea::ERROR_HANDLING,
	    reverse::api::TraceLevel::ERROR,
	    output.str() );

	abort();
      }
    };

  } /* namespace assert */
} /* namespace reverse */

#endif // REVERSE_BAD_ASSERT_HPP
