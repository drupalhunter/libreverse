#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "Statistical_Test.h"

using boost::unit_test_framework::test_suite;
using boost::unit_test_framework::test_case;
using namespace reverse::classifier;

class statistical_test_suite : public test_suite
{
public:
  
  statistical_test_suite ()
    : test_suite ( "statistical_test_suite" )
  {
    // create an instance of the test cases class
    boost::shared_ptr<Statistical_Test> instance ( new Statistical_Test() );

    test_case* test_Constructor_test_case = BOOST_CLASS_TEST_CASE( &Statistical_Test::test_Constructor, instance );
    test_case* test_Column_Totals_test_case = BOOST_CLASS_TEST_CASE( &Statistical_Test::test_Column_Totals, instance );
    test_case* test_Column_Averages_test_case = BOOST_CLASS_TEST_CASE( &Statistical_Test::test_Column_Averages, instance );
    test_case* test_Column_Standard_Deviations_test_case = BOOST_CLASS_TEST_CASE( &Statistical_Test::test_Column_Standard_Deviations, instance );

    add ( test_Constructor_test_case );
    add ( test_Column_Totals_test_case );
    add ( test_Column_Averages_test_case );
    add ( test_Column_Standard_Deviations_test_case );
  }

};

bool init_unit_test_suite ()
{
  test_suite* top_test_suite = BOOST_TEST_SUITE("Statistical algorithm test suite");

  // add test suites to the top test suite
  top_test_suite->add ( new statistical_test_suite() );

  boost::unit_test::framework::master_test_suite().add ( top_test_suite );

  return true;
}

int main (int argc, char** argv)
{
  return ::boost::unit_test::unit_test_main ( &init_unit_test_suite, argc, argv );
}
